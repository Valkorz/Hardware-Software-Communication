/* HAND DETECTION WITH INMOOV + MEDIAPIPE */
#include <PCA9685.h>
PCA9685 driver;  // Library using default B000000 (A5-A0) i2c address, and default Wire @400kHz
PCA9685_ServoEval pwmServo1; //Servo functions

//Define servo pins for each finger

const int range[] = {180,180,180,180,180};

////////////////////////////////////////////

//Define data array
#define DATA_LENGTH 256
#define QUIT '#'

bool receiving = false, cleared = false;
int rxData;
char data[DATA_LENGTH];
int nextIndex = 0;
int elapsedTime;


//Define data array methods
void clearData(){
  for(int i = 0; i < DATA_LENGTH; i++){
    nextIndex = 0;
  	data[i] = 0;
  }
  cleared = true;
}

//Read data and choose action
void readData(){
  for(int i = 0; i < DATA_LENGTH; i++){
    doAction(data[i]);   
  }
}

//Check if data buffer is a specified string
bool isDataString(char* target){
  bool val = false;
  int len = strLen(target);
  for(int i = 0; i < len; i++){
    if(data[i] == target[i]) val = true;
    else if(data[i] != target[i]){
      val = false;
      break;
    }
  } 
  return val;
}

//Get string length
int strLen(char* str){
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  
  return length;
}

//Add different actions for different character readings
bool blink = false;

void doAction(char c){
  switch(c){
   	case QUIT:
    	clearData();
    	break;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  driver.resetDevices(); //Reset drivers in i2c line
  driver.init(); //Initialize module with default settings
  driver.setPWMFreqServo(); //Sets pwm frequency to match servo communication
}

//Read serial if any input is found, store on the data array
void loop()
{
  elapsedTime = millis();

  //Get received data, check if input is detected
  rxData = Serial.read();
  if(rxData < 0){
    delay(50);
  }
  else{
    //Pass to data array, move index if full
    if(data[nextIndex] > 0) nextIndex++;
    data[nextIndex] = (char)lowByte(rxData);
  }
  readData();
  Serial.println(data);
  
  for(int i = 0; i < 5; i++){
    driver.setChannelPWM(i, pwmServo1.pwmForAngle(((int)data[i] - 48) * range[i]));
  }
}