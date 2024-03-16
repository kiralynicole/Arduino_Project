//MASTER

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2,3);

int sensor_pin1 = A0;
int sensor_data1;

String s ="";



void setup()
{
  BTSerial.begin(9600);
  Serial.begin(9600);

  pinMode(sensor_pin1, INPUT); //Soil moisture sensor1
 
}

void loop()
{
   soilWatering1();
    delay(1000);

   Serial.println(s);
}

void soilWatering1(){
  sensor_data1 = analogRead(sensor_pin1);  
  if(sensor_data1 > 750 )
  {
    BTSerial.write("DRY1"); 
    s="DRY1";
  }
  else if(sensor_data1 <= 600)
  {
    BTSerial.write("MEDIUM1");
s = "MEDIUM1";
   
  }
 
}
