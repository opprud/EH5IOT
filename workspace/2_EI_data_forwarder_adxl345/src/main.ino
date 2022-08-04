/*
 * Project 2_ADXL345_spi
 * Description:
 * Author:
 * Date:
 */

#include "math.h"
#include "ADXL345.h"

ADXL345 Accel;
Timer timer(20, sample_tick);
SYSTEM_THREAD(ENABLED); 

void sample_tick(void)
{ 
  //short acc_data[3];
  double acc_data[3];
  int i;
  //int acc_data_int[3];
  Accel.get_Gxyz(acc_data);
  //Accel.readAccel(acc_data);
  if (Accel.status)
  {
    //Serial.printf("%05i\t%05i\t%05i\n",acc_data[0],acc_data[1],acc_data[2]);

    for(i = 0; i < 3; i++){
      Serial.print(acc_data[i]);
      Serial.print("\t");
    }  
    Serial.print("\n");
  
  }
  else
  {
    Serial.println("ERROR: ADXL345 data read error..");
  }
}

void setup()
{
  Serial.begin(460800);
  delay(5);
  Wire.setSpeed(100000);
  Wire.begin();
  delay(5);
  Accel.powerOn();
  delay(2);
  Accel.setRangeSetting(4);
  delay(2);
  Accel.setFullResBit(1);
  delay(2);
  Accel.setJustifyBit(0);

  Serial.println("Ei Data forwarder");
  Accel.set_bw(ADXL345_BW_100); //(ADXL345_BW_12);
  Serial.print("BW_OK? ");
  Serial.println(Accel.status, DEC);
  delay(500);
  timer.start();

}

void loop()
{
  //do nothing
}

