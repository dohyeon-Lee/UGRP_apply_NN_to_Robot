double roll_offset = 0;   //1;
double pitch_offset = 0;  //-2.5;
int EBIMU_getdata(double *item, int number_of_item);
void EBIMU_setup();
void EBIMU_calibration();
void EBIMU_custom_calibration(double *Data, double *Cal_GyX, double *Cal_GyY, double *Cal_GyZ);
double Data[6];   // 3-axis angle, 3-axis acceleration

void setup()
{
  Serial.begin(9600);
  EBIMU_setup();
  EBIMU_calibration();
}
void loop()
{
  EBIMU_getdata(Data, 6);
  Serial.print((String) Data[0] + ", " + Data[1] + ", " + Data[2] + ", " + Data[3] + ", " + Data[4] + ", " + Data[5] + "\n");
}