//SLAVE

#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>

Servo myservo;
AF_DCMotor right_motor(1, MOTOR12_8KHZ);
AF_DCMotor left_motor(2, MOTOR12_8KHZ);
AF_DCMotor pump_motor(3, MOTOR12_8KHZ);

SoftwareSerial BTSerial(2,3);
String readData="";
boolean stringComplete = false; 
int pos = 0;

void setup() {
  BTSerial.begin(9600);
  
  right_motor.setSpeed(255);
  left_motor.setSpeed(255);
  pump_motor.setSpeed(255);

  myservo.attach(10);
  myservo.write(90);
}

void loop() {
  myservo.write(90);
  
    readBluetooth();

    if (stringComplete){
    if (readData == "DRY1"){
         moveToSensor1();         
   }
    }

  stringComplete = false;
  readData="";
}

void readBluetooth(){
  if(BTSerial.available()){
   readData = BTSerial.readString();
  }
  stringComplete = true;
}

void moveToSensor1(){
  //forward left
  delay(500);
  right_motor.run (FORWARD);
  left_motor.run (FORWARD);
  delay(2000);
   right_motor.run (FORWARD);
   left_motor.run (BACKWARD);
   delay(500);
   right_motor.run (FORWARD);
  left_motor.run (FORWARD);
  delay(2000);
  right_motor.run (RELEASE);
  left_motor.run (RELEASE);
  
  waterOn();
  delay(100);
  
  initialState1();
}

void waterOn(){  
   pump_motor.run (FORWARD); //start water
   
    for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  
  delay(2000);

pump_motor.run (RELEASE);
}

void initialState1(){
  delay(10);
  right_motor.run (BACKWARD);
  left_motor.run (BACKWARD);
  delay(2000);
  right_motor.run(BACKWARD);
  left_motor.run(FORWARD);
   delay(500);
   right_motor.run (BACKWARD);
  left_motor.run (BACKWARD);
  delay(2000);
  right_motor.run (RELEASE);
  left_motor.run (RELEASE);

}
