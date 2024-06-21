#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <unistd.h> // usleep
#include <memory>
#include <torch/script.h>
#include <torch/torch.h>
#include <chrono>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/QR>

using namespace Eigen;
using namespace boost::asio;
using namespace boost::system;

std::vector<double> shared_data;
double data[6];
std::mutex data_mutex;

void readFromSerial(boost::asio::serial_port& serial) {
    try {
        while (true) {
            boost::asio::streambuf buf;
            boost::asio::read_until(serial, buf, "\n");

            std::istream input_stream(&buf);
            std::string line;
            std::getline(input_stream, line);

            // Remove leading asterisk and any whitespace
            line.erase(0, line.find_first_not_of("* \t"));

            // Process the received line (assuming CSV format)
            std::stringstream ss(line);
            std::string token;
            std::vector<double> local_data;
            bool all_tokens_valid = true;

            while (std::getline(ss, token, ',')) {
                try {
                    double value = std::stod(token); // Convert token to double
                    local_data.push_back(value);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument in token '" << token << "': " << e.what() << std::endl;
                    all_tokens_valid = false;
                    break;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range in token '" << token << "': " << e.what() << std::endl;
                    all_tokens_valid = false;
                    break;
                }
            }

            // If all tokens are valid and we have exactly 6 data points, update shared_data
            if (all_tokens_valid && local_data.size() == 6) {
                std::lock_guard<std::mutex> lock(data_mutex);
                shared_data = local_data; // Replace with new data
                // std::cout << "Read data: ";
                // for (double value : shared_data) {
                    // std::cout << value << " ";
                // }
                // std::cout << std::endl;
            } else {
                std::cerr << "Invalid data line: '" << line << "'" << std::endl;
            }
        }
    } catch (boost::system::system_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

double lpf(double x_k, double y_km1, double Ts, double tau) 
{
   double y_k;
   y_k = (tau * y_km1 + Ts * x_k) / (Ts + tau);
   return y_k;
   
}


int main() {
    
    torch::jit::script::Module module;
    module = torch::jit::load("/home/dohyeon/UGRP_apply_NN_to_Robot/model/model_dataset4.pt"); // you have to change path to fit your environment
    torch::Tensor state = torch::randn({1, 1, 1});
    torch::Tensor hn = torch::zeros({2, 1, 8});
    double Duration = 0.02; // 50Hz

    boost::asio::io_service io;
    boost::asio::serial_port serial(io);

    std::string comport_num = "/dev/ttyUSB0";
    int comport_baudrate = 115200;

    serial.open(comport_num);
    serial.set_option(boost::asio::serial_port_base::baud_rate(comport_baudrate));

    // Create a thread to read from serial port
    boost::thread serial_thread(boost::bind(readFromSerial, boost::ref(serial)));

    double before_state_theta = 0;
    double before_state_theta_dot = 0; 
    double LQR_vel_U = 0;   
    // Main thread can do other tasks or wait for serial thread
    while (true) {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        
        // reading acceleration from EBIMU
        {
            std::lock_guard<std::mutex> lock(data_mutex);
            if (!shared_data.empty() && shared_data.size() == 6) 
            {                
                data[0] = shared_data[0];
                data[1] = shared_data[1];
                data[2] = shared_data[2];
                data[3] = shared_data[3];
                data[4] = shared_data[4];
                data[5] = shared_data[5];
                shared_data.clear();  // Clear data after processing
            }
        }

        // push input state (acceleration, hidden layer) to Network, and get output state ([theta, thetadot], hidden state)
        
        state[0][0][0] = data[3];
        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(state);
        inputs.push_back(hn);
        auto output = module.forward(inputs).toTuple();
        at::Tensor output_tensor;
        
        output_tensor = output->elements()[0].toTensor();        
        hn = output->elements()[1].toTensor();

        // low pass filtering for network output
        double f_cut = 0.5;
        double tau = 1/(2*M_PI*f_cut);
        double state_theta_lowdata = output_tensor[0][0][0].item<double>();
        double state_theta_dot_lowdata = output_tensor[0][0][1].item<double>();
        double state_theta = lpf(state_theta_lowdata, before_state_theta, Duration, tau);
        double state_theta_dot = lpf(state_theta_dot_lowdata, before_state_theta_dot, Duration, tau);
        before_state_theta = state_theta;
        before_state_theta_dot = state_theta_dot;

        // LQR apply
        double endpoint_Xpos = 0; // get from robot forward kinematics
        double endpoint_Xvel = 0; // get from robot forward kinematics
        VectorXf LQR_state(4);
        VectorXf LQR_K(4);
        LQR_state << endpoint_Xpos, endpoint_Xvel, state_theta, state_theta_dot;
        LQR_K << 10.0000,    4.8634,   -1.7900,   -0.2197;        // K from matlab sim
        double LQR_acc_U = - LQR_K.dot(LQR_state);                // LQR input U  
        LQR_vel_U += LQR_acc_U * Duration;                        // LQR input -> integrator -> LQR_velocity_input
    

        // fix loop Hz
        std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
        if (sec.count() < Duration)
            usleep(int((Duration - sec.count())*1000000));
        else
            std::cout << sec.count() << std::endl;
        
        // print output theta(rad), thetadot(rad/s)
        std::cout << state_theta << ", " << state_theta_dot <<  std::endl;
        // boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    }

    // Wait for serial thread to finish (optional)
    serial_thread.join();

    serial.close();

    return 0;
}