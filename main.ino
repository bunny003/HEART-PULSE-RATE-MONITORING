#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>//PulseSenor to be search to install this
#include<stdlib.h>
const int PulseWire = A0;       // PulseSensor connected to ANALOG PIN 0
const int LED13 = 13;          // LED close to PIN 13.
int Threshold = 524; //Required Threshold(Determined by several attempts)
PulseSensorPlayground pulseSensor; //instance of this libraryino

#include<SoftwareSerial.h> //for WiFi modeule ESP8266
SoftwareSerial myWifi(9,10); // Tx on 9 & Rx on 10
#define WifiName "alphaxxx"  //Set WiFi Name Here
#define WifiPass "1234567890" //Set WiFi PassWord Here
String msgUpdate= "GET /update?key=M6TCKJVDB14PNO2P"; //API to be set W9QL6DJVGZD8ABBB
#define ThinkspeakIP "184.106.153.149"

#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);//(RS,E,I1,I2,I3,I4) I=Interface Pin

int PushButton=8;

void setup()
{
    Serial.begin(9600);//Serial Moniter to be set at 9600
    lcd.begin(16,2);
    lcd.setCursor(5,0);
    lcd.print("Welcome");
    myWifi.begin(115200);//11520 is baud rate of ESP8266 used by us
    lcd.setCursor(1,1);
    lcd.print("Connecting....");
    hereLabel:
    while(myWifi.available()<0)//wait for wifi
    {
      Serial.println("Waiting For Wifi ^_^ ");
      delay(1000);
    }
    hereIsLabel: //label    
    Serial.println("AT");
    myWifi.println("AT");
    delay(4000);
    if(myWifi.find("OK"))
    {
      boolean connectStatus=connectWifi();
      if(connectStatus==false)
      {
        Serial.println("Error in Connecting\nRetring...\n");
        goto hereIsLabel;
      }
      else
      {
        lcd.clear();
        Serial.println("Connected");
        lcd.setCursor(0,0);
        lcd.println("^_^Connected^_^");
        delay(1000);
      }
    }
    else
    {
      Serial.println("Problem\nCheck Wifi Details");
      goto hereLabel;
    }
     pulseSensor.analogInput(PulseWire);   
     pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
     pulseSensor.setThreshold(Threshold);

     if (pulseSensor.begin())
     {
          Serial.println("We created a pulseSensor Object !");
     }
     pinMode(PushButton,INPUT);
     digitalWrite(PushButton,HIGH);
}

int myBPM=0;
int ifError=0;


void loop()
{
  int c=0;
  lcd.clear();
  while(digitalRead(PushButton))
  {
    if(c<1)
    {
      lcd.setCursor(0,0);
      lcd.print("Press Button To");
      lcd.setCursor(0,1);
      lcd.print("Measure BP <3");
      c++;
    }
    Serial.println("Pushbutton Open");
  }
  c=0;
  lcd.clear();
  Serial.println("ALL VALUES:");
  label:
  myBPM=pulseSensor.getBeatsPerMinute();
  if(myBPM<60 || myBPM>95)
    goto label;
  Serial.println(myBPM);
  lcd.setCursor(6,0);
  Serial.print("Current BPM:");
  Serial.println(myBPM);
  lcd.print("BPM:");
  lcd.setCursor(6,1);
  lcd.print(myBPM);
  delay(1000);
  updateBPM();//upload data on thinkspeak::::::
  while(ifError)
    updateBPM();//if error occured during updating on server/thinkspeak
  delay(1000);
}
boolean connectWifi()
{
  Serial.println("AT+CWMODE=1");
  myWifi.println("AT+CWMODE=1");//client mode
  delay(2000);
  String msg="AT+CWJAP=\"";
  msg+=WifiName;
  msg+="\",\"";
  msg+=WifiPass;
  msg+="\"";
  Serial.println(msg);
  myWifi.println(msg);
  delay(5000);
  if(myWifi.find("OK"))
    return true;
  else
    return false;
}

void updateBPM()
{
  String msg="AT+CIPSTART=\"TCP\",\""; //msg=AT+CIPSTART="TCP","IP","PORT"  //TCP is mode
  msg+=ThinkspeakIP;
  msg+="\"";
  msg+=",80";
  Serial.println(msg);
  myWifi.println(msg);
  if(myWifi.find("Error"))
  {
    Serial.println("Upload Error...No Problem");
    return;
  }
  msg= msgUpdate; //to set "GET /update?key=W9QL6DJVGZD8ABBB&field1=",beat,"\r\n"
  msg+="&field1=";
  msg+=myBPM;
  msg+="\r\n";
  myWifi.print("AT+CIPSEND=");
  Serial.print("AT+CIPSEND=");
  Serial.print(msg.length());
  myWifi.println(msg.length());
  if(myWifi.find(">"))
  {
    ifError=0;
    myWifi.print(msg);
    Serial.print(msg);
  }
  else
  {
    ifError=1;//resending
    myWifi.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }
}
