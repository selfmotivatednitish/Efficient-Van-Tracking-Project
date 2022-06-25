// Include Library
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 7, TXPin = 6;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println("Latitude,Longitude,Date,Time,Alt,Speed,");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
}

void loop() {
  // put your main code here, to run repeatedly:
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  Serial.println();
  smartDelay(2000);
}

static void smartDelay(unsigned long ms){
  unsigned long start = millis();
  do{
    while (ss.available())
      gps.encode(ss.read());
  } 
  while (millis() - start < ms);
}
static void printFloat(float val, bool valid, int len, int prec){
  if (!valid){
    Serial.print("00.00000,");
  }
  else{
    Serial.print(val, prec);
    Serial.print(',');
  }
  smartDelay(0);
}
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t){
  if (!d.isValid()){
    Serial.print("00/00/0000,");
  }
  else{
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d", d.month(), d.day(), d.year());
    Serial.print(sz);
    Serial.print(',');
  }
  
  if (!t.isValid()){
    Serial.print(F("00:00:00,"));
  }
  else{
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d", t.hour(), t.minute(), t.second());
    Serial.print(sz);
    Serial.print(',');
  }
  smartDelay(0);
}