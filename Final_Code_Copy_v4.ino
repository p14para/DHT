// email setting instructions --> https://arduinogetstarted.com/tutorials/arduino-send-email

#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>

#include <SoftwareSerial.h>

#define DHTPIN 14     
#define DHTTYPE DHT22 

int resval = 0;  // holds the value
int respin = A9; // Water Level Sensor Pin 
char tempalert[141]= "Flood Alert"  ; 

int anTherm = 30;
int katTherm = 5;
int anYgr = 90;
int katYgr = 20;

// byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
DHT dht(DHTPIN, DHTTYPE);
// Your threshold value
String request ;
String nom = "";
unsigned long refreshCounter  = 0;
IPAddress ip(192, 168, 1, 12) ; // SOS, HAS TO BE PASSED.
byte mac [6] = {0x54, 0x34, 0x41, 0x30, 0x30, 0x31};
//Objects
EthernetServer server(80);
EthernetClient client;


void setup() {

  Serial.begin(9600);
  //Init W5100
  Ethernet.begin(mac, ip);
  while (!Ethernet.begin(mac)) {
  Serial.println(F("failed. Retrying in 1 seconds."));
  // delay(1000);
  Serial.print(F("Starting W5100..."));
  }
  pinMode(2, OUTPUT);
  server.begin();
  // Serial.println(F("W5100 initialized"));
  // Serial.print(F("IP Address: "));
  // Serial.println(Ethernet.localIP());
  dht.begin();

}

void loop() {

  resval = analogRead(respin); 
  int sensorValue = analogRead(A5); // ΕΔΩ ΠΡΕΠΕΙ ΝΑ ΜΠΕΙ ΤΟ Α^ ΠΟΥ ΘΑ ΠΡΕΠΕΙ ΝΑ ΕΛΕΧΓΕΙ ΤΟ ΡΕΥΜΑ
  float voltage = sensorValue * (5.0 / 1023.0);
  

  if(resval > 200 ){   // ΔΟΚΙΜΕΣ ΓΙΑ ΝΑ ΒΑΛΩ ΤΟ ΣΩΣΤΟ LEVEL ΑΝΑΛΟΓΑ ΓΙΑ ΠΟΣΟ ΝΕΡΟ ΕΠΙΤΡΕΠΕΤΑΙ ΝΑ ΕΧΕΙ ΤΟ ΠΑΤΩΜΑ  
    int    HTTP_PORT   = 80;
    String HTTP_METHOD = "GET";
    char   HOST_NAME[] = "maker.ifttt.com";
    String PATH_NAME   = "/trigger/send_email/with/key/bOhD8hX8D8M-W0HBzqQuJqKmUx8Ko1CJrnTvNAItVUs"; // SOS!!! --> change accordingly the PATH_NAME
    String queryString = "?value1=27"; // the supposed temperature value is 27°C
        // initialize the Ethernet shield using DHCP:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to obtaining an IP address using DHCP");
      while (true);
    }
    // connect to web server on port 80:
    if (client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      Serial.println("Connected to server");
      // make a HTTP request:
      // send HTTP header
      client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println(); // end HTTP header
      while (client.connected()) {
        if (client.available()) {
          // read an incoming byte from the server and print it to serial monitor:
          char c = client.read();
          Serial.print(c);
        }
      }
      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } else {// if not connected:
      Serial.println("connection failed");
    }
    // Serial.println("Flood Alert");  
  }

  client = server.available();
  // Wait a few seconds between measurements.
  delay(1000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;

  }
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);



  if (t > anTherm) {
    
    int    HTTP_PORT   = 80;
    String HTTP_METHOD = "GET";
    char   HOST_NAME[] = "maker.ifttt.com";
    String PATH_NAME   = "/trigger/send_email/with/key/bOhD8hX8D8M-W0HBzqQuJqKmUx8Ko1CJrnTvNAItVUs"; // SOS!!! --> change accordingly the PATH_NAME
    String queryString = "?value1=27"; // the supposed temperature value is 27°C
        // initialize the Ethernet shield using DHCP:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to obtaining an IP address using DHCP");
      while (true);
    }
    // connect to web server on port 80:
    if (client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      Serial.println("Connected to server");
      // make a HTTP request:
      // send HTTP header
      client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println(); // end HTTP header
      while (client.connected()) {
        if (client.available()) {
          // read an incoming byte from the server and print it to serial monitor:
          char c = client.read();
          Serial.print(c);
        }
      }
      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } else {// if not connected:
      Serial.println("connection failed");
    }

  }
  if (t <= katTherm) {


    int    HTTP_PORT   = 80;
    String HTTP_METHOD = "GET";
    char   HOST_NAME[] = "maker.ifttt.com";
    String PATH_NAME   = "/trigger/send_email/with/key/bOhD8hX8D8M-W0HBzqQuJqKmUx8Ko1CJrnTvNAItVUs"; // SOS!!! --> change accordingly the PATH_NAME
    String queryString = "?value1=27"; // the supposed temperature value is 27°C
        // initialize the Ethernet shield using DHCP:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to obtaining an IP address using DHCP");
      while (true);
    }
    // connect to web server on port 80:
    if (client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      Serial.println("Connected to server");
      // make a HTTP request:
      // send HTTP header
      client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println(); // end HTTP header
      while (client.connected()) {
        if (client.available()) {
          // read an incoming byte from the server and print it to serial monitor:
          char c = client.read();
          Serial.print(c);
        }
      }
      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } else {// if not connected:
      Serial.println("connection failed");
    }


  }
  if (h > anYgr) {
    int    HTTP_PORT   = 80;
    String HTTP_METHOD = "GET";
    char   HOST_NAME[] = "maker.ifttt.com";
    String PATH_NAME   = "/trigger/send_email/with/key/bOhD8hX8D8M-W0HBzqQuJqKmUx8Ko1CJrnTvNAItVUs"; // SOS!!! --> change accordingly the PATH_NAME
    String queryString = "?value1=27"; // the supposed temperature value is 27°C
        // initialize the Ethernet shield using DHCP:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to obtaining an IP address using DHCP");
      while (true);
    }
    // connect to web server on port 80:
    if (client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      Serial.println("Connected to server");
      // make a HTTP request:
      // send HTTP header
      client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println(); // end HTTP header
      while (client.connected()) {
        if (client.available()) {
          // read an incoming byte from the server and print it to serial monitor:
          char c = client.read();
          Serial.print(c);
        }
      }
      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } else {// if not connected:
      Serial.println("connection failed");
    }
  }
  if (h <= katYgr) {


    int    HTTP_PORT   = 80;
    String HTTP_METHOD = "GET";
    char   HOST_NAME[] = "maker.ifttt.com";
    String PATH_NAME   = "/trigger/send_email/with/key/bOhD8hX8D8M-W0HBzqQuJqKmUx8Ko1CJrnTvNAItVUs"; // SOS!!! --> change accordingly the PATH_NAME
    String queryString = "?value1=27"; // the supposed temperature value is 27°C
        // initialize the Ethernet shield using DHCP:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to obtaining an IP address using DHCP");
      while (true);
    }
    // connect to web server on port 80:
    if (client.connect(HOST_NAME, HTTP_PORT)) {
      // if connected:
      Serial.println("Connected to server");
      // make a HTTP request:
      // send HTTP header
      client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println(); // end HTTP header
      while (client.connected()) {
        if (client.available()) {
          // read an incoming byte from the server and print it to serial monitor:
          char c = client.read();
          Serial.print(c);
        }
      }
      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
    } else {// if not connected:
      Serial.println("connection failed");
    }


  }

 
  Serial.print(t);
  Serial.print(",");
  Serial.print(h);
  Serial.print(",");
  Serial.print(anTherm);
  Serial.print(",");
  Serial.print(katTherm);
  Serial.print(",");
  Serial.print(anYgr);
  Serial.print(",");
  Serial.print(katYgr);
  Serial.print(",");
  Serial.print(voltage * 10);
  Serial.print(",");
  Serial.println(resval);

  

}
