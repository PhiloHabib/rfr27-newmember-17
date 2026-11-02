#include <Wire.h>
const int S0 =2;
const int S1=3;
const int S2=4;
const int S3=5;
const int LED=6;
const int Sensor=A0;
const int sensorCount=8;
volatile byte tempsSending[sensorCount];
float highest=-10000.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(S0, OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);

  pinMode(Sensor,INPUT);

  pinMode(LED,OUTPUT);
  
  digitalWrite(LED,LOW);
  Serial.begin(9600);

  digitalWrite(S0,LOW);
  digitalWrite(S1,LOW);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  Wire.begin(0x12);
  Wire.onRequest(sendTemps);
}

void loop() {
  // put your main code here, to run repeatedly:
  highest=-100000000.0;
  for(int sensorPicked=0;sensorPicked<sensorCount;sensorPicked++){
    sensorPicker(sensorPicked);
    delay(50);

    int reading=analogRead(Sensor);
    float volts= reading*5.0/1023.0;
    float temp =120.0-reading*160.0/1024.0;
    tempsSending[sensorPicked]=(byte)(temp+40);
    if (temp>highest){
      highest=temp;
    }
  }
  Serial.print("Highest Temp: ");
  Serial.println(highest,2);
  if(highest>60.0){
    ledBlink();
  }else{
    digitalWrite(LED,LOW);
  }
}

void sensorPicker(int sensorPicked){
  digitalWrite(S0,bitRead(sensorPicked,0));
  digitalWrite(S1,bitRead(sensorPicked,1));
  digitalWrite(S2,bitRead(sensorPicked,2));
  digitalWrite(S3,bitRead(sensorPicked,3));
}

void sendTemps(){
  for (int i=0;i<sensorCount;i++){
    Wire.write(tempsSending[i]);
  }
}

void ledBlink(){
  digitalWrite(LED,HIGH);
  delay(250);
  digitalWrite(LED,LOW);
  delay(250);
}
