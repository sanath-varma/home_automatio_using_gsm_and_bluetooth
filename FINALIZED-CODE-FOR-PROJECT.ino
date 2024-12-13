#include<String.h>
#include<DHT.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);

bool waterTankFull = false;
bool doorOpen = false;

int dhtpin=8;
int dhttype=DHT11;
DHT dht(dhtpin, dhttype);
int in3=A3;
int in4=A4;
int en=9;
int relaypin=5;
int irroom=6;
int pir=7;
int count=0;
int led=3;
int ledstatus=0,fanstatus=0,motorstatus=0;
int ldr_value=0;
int fanSpeed=0;
int ldr=A1;
int pushbutton=13;
const int irtank=A2;
int in1=4;
int in2=A5;
int gas=A0;
int buzz=2;
int doorlock=12;
String data;
String voice;
String inputString = "";
bool stringComplete = false;
String incomingString ="";
String smsmessage;
int startIndex = 0;
int endIndex = 0;
float tempC=0;
int temp=0;
float tempf=0;
int gasLevel=0;
void fanStatus( float temp);
int value=0;
bool ledstate;
int d=0,x=0,y=0,p=0;
int ispersoninroom=0;
int ispersontouch=0; 
int count1=0;
void motoron();
void motoroff();
void buzzeron();
void smssending(String phoneNumber,String message) ;
void toggle();
void fanOn();
void fanOff();
void buzzeroff();
void makeCall();

  void handleGasSensor();
  void checktemperature();
  void serialEvent();
  void handlegsm();
 void  handleBluetooth();
  void handleIRSensor();
  void handleDoorIRSensor();
 void  handleldr();
  void touchSensor();
  void handleWaterTankIRSensor();


void setup() {
  Serial.begin(9600);
   BTSerial.begin(9600);
   dht.begin();
  pinMode(irroom,INPUT);
  pinMode(ldr,INPUT);
  pinMode(gas,INPUT);
  pinMode(pushbutton,INPUT);
  pinMode(irtank,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(doorlock,INPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(buzz,OUTPUT);
 pinMode(led,OUTPUT);
  pinMode(pir,INPUT);
  pinMode(relaypin,OUTPUT);
  inputString.reserve(200);
  Serial.print("AT+CNMI=2,2,0,0,0\r\n");
  delay(200);
  Serial.print("AT\r\n");
  delay(200);
  Serial.print("ATE0\r\n");
  delay(100);

}

void loop() {
  handleIRSensor();
  serialEvent();
  handlegsm();
  
  delay(100); // Reduced delay
  float humi=dht.readHumidity();
  tempC = dht.readTemperature();
 tempf=dht.readTemperature(1);
  

  Serial.println(d);
  Serial.println(y);
   delay(20);
 handleIRSensor();
  serialEvent();
  handlegsm();
  delay(100);

  BTSerial.print(humi);
  //Serial.print(humi);
  BTSerial.print("%");
  BTSerial.print(",");
  BTSerial.print(tempC);
  BTSerial.print(" C");
  BTSerial.print(",");
  BTSerial.print(tempf);
  BTSerial.print(" F");
  BTSerial.print(",");
  BTSerial.print(ledstatus);
  BTSerial.print(",");
  BTSerial.print(fanstatus);
  BTSerial.print(",");
  BTSerial.print(motorstatus);
  BTSerial.print(";");
  delay(20);
  handleIRSensor();
  touchSensor();
  serialEvent();
  handlegsm();
  delay(200);
  
  handleGasSensor();
  touchSensor();
  if(fanstatus==1){
  checktemperature();
  }

  handleBluetooth();
  handleIRSensor();
  touchSensor();
  handleDoorIRSensor();
  handleldr();
  handleWaterTankIRSensor();
  serialEvent();
  handlegsm();
  touchSensor();
}


void checktemperature(){
  Serial.println("inside the checktemp");
  temp=dht.readTemperature();
  if(fanstatus==1){
    fanStatus(temp);
  }

}

void pirsensor(){
  y=digitalRead(pir);
  if(y==1){
    digitalWrite(buzz,1);
  }
}

void handleBluetooth() {
 if (BTSerial.available()) {
    while (BTSerial.available() > 0) {
      data = BTSerial.readString();
      voice = data;
      BTSerial.print(data);
      if (voice.length() > 0) {
        if (voice == "light on") {
          digitalWrite(relaypin, 0); // Turn on the light
        } else if (voice == "light off") {
          digitalWrite(relaypin, 1); // Turn off the light
        } else if (voice == "fan on") {
          fanOn();
        } else if (voice == "fan of") {
          fanOff();
        } else if (voice == "motor on") {
          motoron();
        } else if (voice == "motor of") {
          motoroff();
        }
        else if (voice == "buzzer of") {
          buzzeroff();
        }
      }
      voice = "";
    }
  }
}

void serialEvent() {
  if(stringComplete == false) {
    incomingString = Serial.readString();
    if(incomingString.length()>0){
      if(incomingString.indexOf("RING") !=-1){
        toggle();
        delay(500);
        Serial.write("ATH\r\n");
        delay(1000);
      }
      startIndex = incomingString.indexOf("@");
      endIndex = incomingString.indexOf("#");
      if(startIndex >= 0 && endIndex > 0){
        inputString = incomingString.substring(startIndex,endIndex+1);
        stringComplete = true;
      }
    }
  }
}

void toggle() {
  static bool ledstate=false;
  ledstate=!ledstate;
  digitalWrite(relaypin, ledstate ? LOW : HIGH);

  //SEND SMS
  if(ledstate==true){
    smssending("+919398462583","ledon");
  }
  if(ledstate==false){
    smssending("+919398462583","ledoff");
  }
}


void smssending(String phoneNumber,String message) {
  Serial.println("AT+CMGF=1\r"); // Set SMS mode to text
  delay(600); // wait for a second
  Serial.println("AT+CMGS=\"" + phoneNumber + "\"");
  delay(800); // wait for a second
  Serial.println(message);
  delay(100);
  Serial.println((char)26); // Send Ctrl+Z to end the message
  delay(750); // wait for a second
}

// Function to make a call through GSM module
void makeCall() {
    Serial.println("ATD+919398462583;"); // Replace with your phone number
    delay(500);
    Serial.println("ATH");
}

void handlegsm(){
    if (stringComplete && inputString!="") {
     inputString.toLowerCase();
    if(inputString=="@off#"){
      digitalWrite(relaypin, 1);
      ledstatus=0;
      //delay(200);
      smssending("+919398462583","led off");
    }
     if(inputString=="@on#"){
      digitalWrite(relaypin, 0);
      ledstatus=1;
      //delay(200);
      smssending("+919398462583","led on");
    }
    if(inputString=="@motor off#"){
      motoroff();
      //delay(200);
      smssending("+919398462583","motor off");
    }
     if(inputString=="@fan off#"){
      fanOff();
      //delay(200);
      smssending("+919398462583","fan off");
    }

   if(inputString=="@fan on#"){
      fanOn();
      //delay(200);
      smssending("+919398462583","fan on");
    }
    if(inputString=="@buzzer off#"){
      buzzeroff();
      //delay(200);
      smssending("+919398462583","buzzer off");
    }

   if(inputString=="@motor on#"){
      motoron();
      //delay(200);
      smssending("+919398462583","motor on");
    }
    Serial.print("AT+CMGDA=\"");
    Serial.print("DEL ALL\"\r\n");
    //delay(100);
    inputString = "";
    stringComplete = false;
  }
} 




// Function to handle the IR sensor logic
 void handleIRSensor(){
    x=digitalRead(irroom);
    if (x == 1 && ispersoninroom== 0) { 
    count++; 
    if (count == 1) { 
        digitalWrite(relaypin,0); //active low relay
        ledstatus=1;    
    }
    if (count >= 2 ) { 
       count = 0; 
       digitalWrite(relaypin,1);
       ledstatus=0;  
    }
      
    }
  
  ispersoninroom=x;
 }

 void handleGasSensor() {
    gasLevel = analogRead(gas); // Read the gas level
    if (gasLevel > 1000) { 
        smssending("+919398462583","Gas leakage detected!");
        makeCall();
    }
}

void handleDoorIRSensor() {
    if (digitalRead(doorlock) == HIGH ) { 
        doorOpen = true;
         buzzeron();
         smssending("+919398462583","Door is open!!");
          makeCall();
    } else {
        doorOpen = false;
    }
}



void handleWaterTankIRSensor() {
    if (digitalRead(irtank) == LOW ) { 
        waterTankFull = true;
        smssending("+919398462583","Water tank is full.!!");
        motoroff();
    } else {
        waterTankFull = false;
    }
}


void handleldr(){
    ldr_value=analogRead(ldr);
     if (ldr_value < 100) {
    analogWrite(led, 0);
    delay(200);

  } 
  else if (ldr_value < 200) {
    
    analogWrite(led, 6);
    delay(200);
  } 
  else if (ldr_value < 500) {
    
    analogWrite(led, 50);
    delay(200);
  } else if(ldr_value < 600) {
    
    analogWrite(led, 150);
    delay(200);
  }
  else if(ldr_value < 700) {
    // Low light, turn on LED
    analogWrite(led, 200);
    delay(200);

  }
  else{
    analogWrite(led, 250);
    delay(200);
  }


}


 void motoroff(){
  digitalWrite(in3,0);
  digitalWrite(in4,0);
  motorstatus=0;
  delay(200);
}


void motoron(){
  digitalWrite(in3,0);
  digitalWrite(in4,1);
  motorstatus=1;
  delay(200);

}
void buzzeron(){
  digitalWrite(buzz,1);
  delay(20);

}
void buzzeroff(){
  digitalWrite(buzz,0);
  delay(20);

}

void fanOn() {
  Serial.println("fan turning on ");
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  fanstatus=1;
  //checktemperature();
 

}

void fanOff() {
  Serial.println(" fan turning off");
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  analogWrite(en, 0);
  fanstatus=0;
}


void fanStatus( float temp) {
   if( temp<33){
    Serial.println("100rpm");
    fanSpeed = 100;
    analogWrite(en, fanSpeed);
  }
   else if( temp <36){
    Serial.println("200rpm");
    fanSpeed = 200;
    analogWrite(en, fanSpeed);
  }
   else  if(temp <38){
    Serial.println("255rpm");
    fanSpeed = 255;
    analogWrite(en, fanSpeed);
  }else{
    Serial.println("normal speed rpm");
    fanSpeed = 200;
    analogWrite(en,fanSpeed);
  }
}


 void touchSensor(){
   p= digitalRead(pushbutton);
   Serial.println(p);
    if ( p==1 && ispersontouch==0) { 
    count1++; 
    if (count1 == 1) { 
        digitalWrite(relaypin,0);
        ledstatus=1;    
    }
    else if (count1 >= 2 ) { 
       count1 = 0; 
       digitalWrite(relaypin,1);
       ledstatus=0;  
    }
      
    }
  
  ispersontouch=p;
 }