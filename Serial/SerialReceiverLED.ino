/* HAND DETECTION WITH INMOOV + MEDIAPIPE */
/*Prototype COPY using LEDs in case of Servo or driver failure*/

//Define servo pins for each finger

const int fingerPins[] = {2,3,4,5,6};
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

char targetMessage[] = "pisca";

//Define data array methods
void clearData(){
  for(int i = 0; i < DATA_LENGTH; i++){
    nextIndex = 0;
  	data[i] = 0;
  }
  lcd.clear();
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

 
  //Initialize LEDs
  for(int i = 0; i < 5; i++){
    pinMode(fingerPins[i], OUTPUT);
  }
  
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
  
  for(int i = 0; i < 5; i++){
    writePin(fingerPins[i],((int)data[i] - 48));
  }

  delay(100);
}

void writePin(int pin, int state){
  digitalWrite(pin, state > 0? HIGH : LOW);
}