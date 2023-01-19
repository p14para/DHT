/***********************************
 First upload the Arduino code to the Arduino and then run this code.
 Make sure that the Port number and baudrate are the same.
***********************************/
import meter.*;
import processing.serial.*;

Serial port;
String[] list;

Meter m, m2;

void setup() {
  size(950, 400);
  background(255, 255, 255);
  
  port = new Serial(this, "COM4", 9600);

  fill(120, 50, 0);
  m = new Meter(this, 25, 100);
  // Adjust font color of meter value  
  m.setTitleFontSize(20);
  m.setTitleFontName("Arial bold");
  m.setTitle("Ρευμα");
  m.setDisplayDigitalMeterValue(true);
  
  // Meter Scale
  String[] scaleLabelsT = {"0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100"};
  m.setScaleLabels(scaleLabelsT);
  m.setScaleFontSize(18);
  m.setScaleFontName("Times New Roman bold");
  m.setScaleFontColor(color(200, 30, 70));
  
  m.setArcColor(color(141, 113, 178));
  m.setArcThickness(10);
  m.setMaxScaleValue(100);
  
  m.setNeedleThickness(3);
  
  m.setMinInputSignal(0);
  m.setMaxInputSignal(100);

  // A second meter for reference
  int mx = m.getMeterX();
  int my = m.getMeterY();
  int mw = m.getMeterWidth();
  
  m2 = new Meter(this, mx + mw + 20, my);
  m2.setTitleFontSize(20);
  m2.setTitleFontName("Arial bold");
  m2.setTitle("Επιπεδο Νερου");
  m2.setDisplayDigitalMeterValue(true);
  
  String[] scaleLabelsH = {"0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200"};
  m2.setScaleLabels(scaleLabelsH);
  m2.setScaleFontSize(18);
  m2.setScaleFontName("Times New Roman bold");
  m2.setScaleFontColor(color(200, 30, 70));
  
  m2.setArcColor(color(141, 113, 178));
  m2.setArcThickness(10);
  m2.setMaxScaleValue(200);
  
  m2.setNeedleThickness(3);
  
  m2.setMinInputSignal(0);
  m2.setMaxInputSignal(200);
  
}

public void draw() {
  
  textSize(30);
  fill(0, 0, 0);
  text("Ρεύμα και Επίπεδο Νερού", 270, 50);
  
  if (port.available() > 0) {
    String val = port.readString();
    list = split(val, ',');
    float reyma = float(list[6]);
    float epNeroy = float(list[7]);
    delay(1000);
    
    println("Ρεύμα: " + reyma  + " Επίπεδα Νερού: " + epNeroy );
    
    m.updateMeter(int(reyma));
    m2.updateMeter(int(epNeroy));
  }
}


/*
// Arduino code

#include <SimpleDHT.h>

// for DHT22, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22 = 2;
SimpleDHT22 dht22;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // start working...
  
  // read without samples.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
    return;
  }
  
  Serial.print((float)temperature);
  Serial.print(",");
  Serial.println((float)humidity);
  
  // DHT22 sampling rate is 0.5HZ.
  delay(2500);
}
*/
