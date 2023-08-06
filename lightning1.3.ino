
#include <TM1638plus.h>

// GPIO I/O pins on the Arduino connected to strobe, clock, data,
//pick on any I/O you want.
#define  STROBE_TM 4 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 6  // clock = GPIO connected to clock line of module
#define  DIO_TM 7 // data = GPIO connected to data line of module
bool high_freq = false; //default false,, If using a high freq CPU > ~100 MHZ set to true.

//Constructor object (GPIO STB , GPIO CLOCK , GPIO DIO, use high freq MCU)
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM, high_freq);


int shutterPin = 2;  //Define the camera pin
int cadSensor = A0;  //Define the LDR pin
int triggerPointPin = A1; //Define the "light level pot" pin
int delayPin = A2; //delay for lightning to get bright (need to be kinda low eg. 50ms)
int exposePin = A3; //how long to have shutter open each pic (eg. 3-8 secs)

word triggered =0; //Define the variables globally 
word triggerPoint = 0;
word delayTime = 0;
word exposeTime = 0;

word delayTimeDiff = 0;
word exposeTimeDiff = 0;
word delayTimeOld = 0;
word exposeTimeOld = 0;


// the setup routine runs once when you press reset:
void setup() {
  Serialinit();
  tm.displayBegin();

  //these lines need changing for connecting to camera
  
  pinMode(shutterPin,OUTPUT);    //Define the shutter pin as an output 
  digitalWrite(shutterPin,LOW);  //Set the shutter pin to low / off / no voltage
}

// the loop routine runs over and over again forever:
void loop() 
{
  
  triggerPoint = analogRead(triggerPointPin); //Read the output from the potentiometer
  triggered = analogRead(cadSensor);  //Read the output from the LDR
  delayTime = analogRead(delayPin) / 10;
  exposeTime = analogRead(exposePin) *10 + 500;
  delayTimeDiff = abs(delayTime - delayTimeOld);
  exposeTimeDiff = abs(exposeTime - exposeTimeOld);

  if (delayTimeDiff >= 10)
  {
    //print value to 8seg and serial
    Serial.println("Delay Time Change(ms)");
    Serial.println(delayTime);
    
    tm.reset();
    tm.brightness(0);
    tm.displayIntNum(delayTime); //send value to 8seg
    delay(1000);
  }

  if (exposeTimeDiff >= 100)
  {
    //print value to 8seg and serial
    Serial.println("Expose Time Change(sec)");
    Serial.println(exposeTime);
    
    tm.reset();
    tm.brightness(0);
    tm.displayIntNum(exposeTime /1000); //send value to 8seg
    delay(1000);
  }

  delayTimeOld = delayTime;
  exposeTimeOld = exposeTime;
  

  
  if (triggered >= triggerPoint)  //If light is higher than trigger point, trigger the camera
  {
    delay(delayTime);    //Wait for lightning to be the brightest (0- 100ms)
    digitalWrite(shutterPin,HIGH);  //Trigger camera
    Serial.println("Triggered");
    Serial.println("Delay Time(ms)");
    Serial.println(delayTime);
    Serial.println("Expose Time(sec)");
    Serial.println(exposeTime);
    delay(exposeTime);      //Delay before "closing shutter" or exposure time (0 - 10 seconds)
    digitalWrite(shutterPin,LOW);   //Reset camera trigger output for next photo
    triggered = 0;         //"un-trigger camera" ie. Let go of button
    Serial.println("Trigger Off");
  }
  else 
  {
    //print value to 8seg and serial
    Serial.println("Cadmium Sensor");
    Serial.println(cadSensor);
    
    tm.brightness(0);
    tm.displayIntNum(triggered); //send value to 8seg
    delay(500);
  }
  
}



//Function to setup serial called from setup FOR debug

void Serialinit()
{
  Serial.begin(9600);
  delay(100);
  Serial.println("--Comms UP--xxxxxxxxxx--");
}
