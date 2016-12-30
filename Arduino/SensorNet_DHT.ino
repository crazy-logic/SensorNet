//webclient, webclientrepeating and dht from adafruit.


float t = 0;  // TEMPERATURE
float h = 0;  // HUMIDITY
String data;
int interval = 10; //interval in seconds
int sensorid =2; // the sensors id
char server[] = "your.server.dns";
String path = "/folder/folders/";


#include <DHT.h>
DHT dht0(2, DHT11); // remember to set the DHT pin.

#include <Ethernet.h>
#include <SPI.h>
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // change this to your mac address..... 
EthernetClient client;

void setup() {
  dht0.begin();
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop() {
  if (client.available()) {
        char c = client.read();
        Serial.print(c);
        }else
        {
          client.stop();  // DISCONNECT FROM THE SERVER
          Serial.println("disconnecting.");
          delay(1000*interval); //wait interval.
          httprequest();
        }



    h =  dht0.readHumidity();
    t =  dht0.readTemperature();

    //lets build the GET query
    data+="GET ";
    data+=path;
    data+="/reading.php?";
    data+="sensorid=";
    data+=sensorid;
    data+="&value=";
    data+=t;
    data+=" HTTP/1.1";




}

void httprequest(){
  client.stop();

  Serial.println("connecting...");
    // and now we should process the http request
    if (client.connect(server,80))
    {
      //let serial know
      Serial.println("connected");
      client.println(data);
      client.print("Host: ");
      client.println(server);
      client.println("Connection: close");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.println("User-Agent: Arduino/1.0");
      client.print("Content-Length: ");
      client.println(data.length());
      client.println();
      client.print(data);

  } else {
    client.stop();  // DISCONNECT FROM THE SERVER
    Serial.println("disconnecting.");
  }

}
