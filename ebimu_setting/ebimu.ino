#define SBUF_SIZE 64*2
 
char sbuf[SBUF_SIZE];
signed int sbuf_cnt=0;

int EBIMU_getdata(double *item, int number_of_item)
{
  int n,i;
  int rbytes;
  char *addr; 
  int result = 0;
  
  rbytes = Serial1.available();
  // Serial.println(rbytes);
  for(n=0;n<rbytes;n++)
  {
    sbuf[sbuf_cnt] = Serial1.read();
    if(sbuf[sbuf_cnt]==0x0a)
    {
      // Serial.println(sbuf);
      addr = strtok(sbuf,",");
      for(i=0;i<number_of_item;i++)
      {
        item[i] = atof(addr);
        addr = strtok(NULL,",");
      }

      result = 1;
    }
    else if(sbuf[sbuf_cnt]=='*')
    {
      sbuf_cnt=-1;
    }
 
    sbuf_cnt++;
    if(sbuf_cnt>=SBUF_SIZE) sbuf_cnt=0;
  }
  
  return result;
}
void EBIMU_setup()
{
  Serial1.begin(115200);
  // Serial1.write("<sor2>"); // hz 설정
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<avcg_e0>"); //  gyro AVC off
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<avca_e0>"); //  acc AVC off
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<sem2>"); //  magnetometer on
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<som0>"); //  magnetometer data
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<sog1>"); // gyro data
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<soa1>"); // acc data 
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<raa_t0>"); //  RAA timeout
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<raa_l0.01>"); //  RAA level
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<rha_t0>"); //  RHA timeout
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<sog1>"); // gyro data
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<soa1>"); // acc data 
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<ssa4>"); // acc sens ssa1:2g ssa2:4g ssa3:8g ssa4:16g
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<lpfg7>"); // gyro LPF
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<lpfa7>"); // acc no LPF
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<avcg_e1>"); //  gyro AVC on
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<avca_e1>"); //  acc AVC on
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<cg>"); // gyro calibration 
  // delay(3000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  Serial1.write("<cas>"); // acc calibration 
  delay(3000);
  while(Serial1.available())
  {
    char c = Serial1.read();
    Serial.print(c);
  }
}


void EBIMU_calibration()
{
  Serial.println("EBIMU calibration start");
  Serial1.write("<lf>"); // initalization
  delay(1000);
  while(Serial1.available())
  {
    char c = Serial1.read();
    Serial.print(c);
  }
  Serial1.write("<sor10>"); // hz 설정, (10: 10ms,100Hz)
  delay(1000);
  while(Serial1.available())
  {
    char c = Serial1.read();
    Serial.print(c);
  }
  // Serial1.write("<sog1>"); // gyro data
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  Serial1.write("<soa2>"); // acc data (soa1:default,local / soa2:local, delete gravity / soa3:global, delete gravity)
  delay(1000);
  while(Serial1.available())
  {
    char c = Serial1.read();
    Serial.print(c);
  }
  Serial1.write("<ssa4>"); // acc sens ssa1:2g ssa2:4g ssa3:8g ssa4:16g
  delay(1000);
  while(Serial1.available())
  {
    char c = Serial1.read();
    Serial.print(c);
  }
  // Serial1.write("<lpfg7>"); // gyro LPF
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  Serial1.write("<lpfa4>"); // acc LPF (default 4)
  delay(1000);
  while(Serial1.available())
  {
    char c = Serial1.read();
    Serial.print(c);
  }
  // Serial1.write("<avcg_e0>"); //  gyro AVC off
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<avca_e0>"); //  acc AVC off
  // delay(1000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // digitalWrite(LEDR, LOW);
  // digitalWrite(LEDB, HIGH);
  // delay(3000);
  // Serial1.write("<cg>"); // gyro calibration 
  // delay(3000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
  // Serial1.write("<cas>"); // acc calibration 
  // delay(3000);
  // while(Serial1.available())
  // {
  //   char c = Serial1.read();
  //   Serial.print(c);
  // }
}
void EBIMU_custom_calibration(double *Data, double *Cal_GyX, double *Cal_GyY, double *Cal_GyZ)
{
  int CAL_STEP = 2000;
  *Cal_GyX = 0;
  *Cal_GyY = 0;
  *Cal_GyZ = 0;

  for(int i = 0 ; i < CAL_STEP; i++) 
  {
    if(i % 200 == 0) Serial.println("Calculating ..... ");
    EBIMU_getdata(Data, 9);
    delay(1);

    // Sum data
    *Cal_GyX += Data[3];
    *Cal_GyY += Data[4];
    *Cal_GyZ += Data[5];
  }

  // Average Data
  *Cal_GyX /= double(CAL_STEP);
  *Cal_GyY /= double(CAL_STEP);
  *Cal_GyZ /= double(CAL_STEP);

  Serial.println("Calibration finished!!!");
  Serial.println(*Cal_GyX);
  Serial.println(*Cal_GyY);
  Serial.println(*Cal_GyZ);
  delay(100);  
}