#include <PCA9685.h>
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>

PCA9685 driver;  // Library using default B000000 (A5-A0) i2c address, and default Wire @400kHz
PCA9685_ServoEval pwmServo1;
PCA9685_ServoEval pwmServo2; //Servo functions

//Data 
#define DATA_LENGTH 256;
int data = 0;
int rxData;

void setup() {
  Serial.begin(9600);
  driver.resetDevices(); //Reset drivers in i2c line
  driver.init(); //Initialize module with default settings
  driver.setPWMFreqServo(); //Sets pwm frequency to match servo communication
}
// pwmController.setChannelPWM(0, pwmServo1.pwmForAngle(-90));
void loop() {
  
  //Receive serial data
  rxData = Serial.read();
  if(rxData < 0){
    //Wait if no input
    delay(50);
  } else {
    data = (int)lowByte(rxData);
  }

  driver.setChannelPWM(0, uint16_t pwmAmount)


}
