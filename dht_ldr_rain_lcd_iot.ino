#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);
int sensepin = A2;

#include <stdlib.h>
#include <dht.h>
#define dht_dpin A1 
int rain;
int i, j;
dht DHT;
  #include<SoftwareSerial.h>

long t5=0;
long t4=0;
long t3=0;
int m=0;
int n=0;
int o=0;
int p;
int a;
char buf1[16];
char buf2[16];
char buf3[16];
char buf4[16];
char buf5[16];
int s=0;
int s1=0;
long t=0;
long t1=0;
long t2=0;
int x=0;
String strm;
String strn;

String strp;
String stra;
// replace with your channel's thingspeak API key

String apiKey = "YG3JYMLL6O44D84M";

SoftwareSerial ser(5, 6); // RX, TX

 
void setup()
{
pinMode(2, OUTPUT);        //buzzer
      digitalWrite(2, LOW);
       analogReference(DEFAULT);
 lcd.begin(16,2);
 lcd.setCursor(0,0);
      lcd.print("Weather Monitor");
      
      delay(2000);
      lcd.clear();
    Serial.begin(9600);
  // enable software serial
  ser.begin(115200);
  // reset ESP8266
  ser.println("AT+RST");
   delay(500);
  ser.println("AT+CWMODE=3");
   delay(500);
  
 ser.println("AT+CWJAP=\"project\",\"12345678\"");
  delay(500);
 
 
}
 
void loop()
{
    DHT.read11(dht_dpin);
      

 i=DHT.humidity;
      j =DHT.temperature;


m = map(analogRead(A2), 0, 1023, 100, 0); //rain

n=analogRead(A3); //ldr

a= i; 
p= j;
if(i>60 || j>40 || m>40 || n>500)
{
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
}


lcd.setCursor(0, 0);
    lcd.print("R:");
 lcd.print(m);

  lcd.print(" ");
  lcd.setCursor(8, 0);
    lcd.print("LDR:");
 lcd.print(n);
 lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("H:");
 lcd.print(i);
  lcd.print(" ");
  lcd.setCursor(8, 1);
    lcd.print("T:");
 lcd.print(j);
 lcd.print(" ");

strm = dtostrf(analogRead(A2), 4, 1, buf1);
strn = dtostrf(n, 4, 1, buf2);

stra = dtostrf(a, 4, 1, buf4);
strp = dtostrf(p, 4, 1, buf5);
Serial.print(strm);
Serial.print(" ");
Serial.print(strn);
Serial.print(" ");
Serial.print(stra);
Serial.print(" ");
Serial.print(strp);
Serial.println(" ");

       if(millis() - t>6000 && x==0)
  {
    Serial.println("x is 1 ");
    x=1;
    t=millis();
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);

  if(ser.find("Error")){
   // Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field2=";
  getStr += String(strn);
  getStr += "\r\n\r\n";



  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

   

  if(ser.find(">")){
    ser.print(getStr);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE 1");
  }
  // thingspeak needs 15 sec delay between updates
 // delay(6000);
  }
    if(millis() - t1>12000 && x==1)
  {
         Serial.println("x is 2 ");
    x=2;
    t1=millis();
  // TCP connection
  String cmd1 = "AT+CIPSTART=\"TCP\",\"";
  cmd1 += "184.106.153.149"; // api.thingspeak.com
  cmd1 += "\",80";
  ser.println(cmd1);

  if(ser.find("Error")){
   // Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr1 = "GET /update?api_key=";
  getStr1 += apiKey;
  getStr1 +="&field1=";
  getStr1 += String(strm);
  getStr1 += "\r\n\r\n";



  // send data length
  cmd1 = "AT+CIPSEND=";
  cmd1 += String(getStr1.length());
  ser.println(cmd1);

   

  if(ser.find(">")){
    ser.print(getStr1);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
 Serial.println("AT+CIPCLOSE 2");
  }
  // thingspeak needs 15 sec delay between updates
 // delay(6000);
  }
    if(millis() - t2>24000 && x==2)
  {
       Serial.println("x is 3 ");
    x=4;
    t2=millis();
  // TCP connection
  String cmd2 = "AT+CIPSTART=\"TCP\",\"";
  cmd2 += "184.106.153.149"; // api.thingspeak.com
  cmd2 += "\",80";
  ser.println(cmd2);

  if(ser.find("Error")){
 //   Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr2 = "GET /update?api_key=";
  getStr2 += apiKey;
  getStr2 +="&field4=";
  getStr2 += String(stra);
  getStr2 += "\r\n\r\n";



  // send data length
  cmd2 = "AT+CIPSEND=";
  cmd2 += String(getStr2.length());
  ser.println(cmd2);

   

  if(ser.find(">")){
    ser.print(getStr2);
  }
   else{
    ser.println("AT+CIPCLOSE");
     Serial.println("AT+CIPCLOSE 3");
  }
  
  }
   
 if(millis() - t5>42000 && x==4)
  {
        Serial.println("x is 5 to 0 ");
  x=0;
    t5=millis();
 // TCP connection
  String cmd4 = "AT+CIPSTART=\"TCP\",\"";
  cmd4 += "184.106.153.149"; // api.thingspeak.com
  cmd4 += "\",80";
  ser.println(cmd4);

  if(ser.find("Error")){
 //   Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr4 = "GET /update?api_key=";
  getStr4 += apiKey;
  getStr4 +="&field3=";
  getStr4 += String(strp);
  getStr4 += "\r\n\r\n";



  // send data length
  cmd4 = "AT+CIPSEND=";
  cmd4 += String(getStr4.length());
  ser.println(cmd4);

   

  if(ser.find(">")){
    ser.print(getStr4);
  }
   else{
    ser.println("AT+CIPCLOSE");
     Serial.println("AT+CIPCLOSE 5");
  }
  }
    
    delay(300);  
}
