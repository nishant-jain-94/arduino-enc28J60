
#include <UIPEthernet.h>
#include <SPI.h>

EthernetClient client;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.0.103";
int temp = 100;

IPAddress ip(192, 168, 0, 105);

void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to Ethernet");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet");
    Ethernet.begin(mac, ip);
  }
  // put your setup code here, to run once:
  delay(1000);
  Serial.println("connecting...");

  if(client.connect(server, 9098)) {
    Serial.println("Connected");
    client.println("GET /trigger/hi HTTP/1.1");
    client.println("Connection: keep-alive");
  } else {
    Serial.println("Connection Failed");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  if (client.connect(server, 9098) && client.connected()) {
    Serial.println("Inside Loop");
    Serial.println("Sending Request");
    client.println("GET /trigger/hi HTTP/1.1");
    client.println();
  }
}

