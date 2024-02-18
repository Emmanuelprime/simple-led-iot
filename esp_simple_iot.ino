#include <WiFi.h>
#include <WebServer.h>
#define redpin 5
#define greenpin 4
#define yellowpin 2
const char* ssid     = "Airtel 4G MiFi_80C1";
const char* password = "03133503";

WebServer server(80);

String led_staus = "off";

void setup() {
  Serial.begin(115200);
  pinMode(yellowpin,OUTPUT);
  pinMode(redpin,OUTPUT);
  pinMode(greenpin,OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  delay(1000);

//  create endpoints
  server.on("/",handle_OnConnect); //index
  server.on("/blink",handle_OnBlink); //blink led
  server.on("/off",handle_OffLED); //off led 
  server.on("/alternate",handle_OnAlternate); // alternate led 
  server.onNotFound(handle_OntFound); //not found
  server.begin();
  Serial.println("HTTP Server Started");
  digitalWrite(greenpin,HIGH);
}

void loop() {
  server.handleClient();

  if(led_staus == "off"){
    digitalWrite(redpin,LOW);
    digitalWrite(yellowpin,LOW);
  }
  else if(led_staus == "blink"){
    digitalWrite(redpin,HIGH);
    digitalWrite(yellowpin,HIGH);
    delay(500);
    digitalWrite(redpin,LOW);
    digitalWrite(yellowpin,LOW);
    delay(500);
  }

  else if(led_staus == "alternate"){
    digitalWrite(redpin,HIGH);
    digitalWrite(yellowpin,LOW);
    delay(500);
    digitalWrite(redpin,LOW);
    digitalWrite(yellowpin,HIGH);
    delay(500);
  }
}
String getHTML(){
  String htmlcode = "<!DOCTYPE html> <html>\n";
  htmlcode += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlcode +="<tittle> LED PLAYGROUND</tittle>\n";
//styles
  htmlcode +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlcode +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  htmlcode +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  htmlcode +=".button-on {background-color: #3498db;}\n";
  htmlcode +=".button-on:active {background-color: #2980b9;}\n";
  htmlcode +=".button-off {background-color: #34495e;}\n";
  htmlcode +=".button-off:active {background-color: #2c3e50;}\n";
  htmlcode +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  htmlcode +="</style>\n";
  
  htmlcode +="</head>\n";
  htmlcode +="<body>\n";
  htmlcode +="<h1>ESP32 Demo WebServer</h1>\n";
  htmlcode +="<h3>This is a simple ESP32 WebServer in STA mode</h3>\n";
  htmlcode +="<a class=\"button button-off\" href=\"/blink\"> Blink</a>\n";
  htmlcode +="<a class=\"button button-off\" href=\"/alternate\"> Alternate</a>\n";
  htmlcode +="<a class=\"button button-off\" href=\"/off\">OFF</a>\n";
  return htmlcode;
}

void handle_OnConnect(){
  led_staus = "off";
  Serial.println("LED Status: OFF");
  server.send(200,"text/html",getHTML());
}

void handle_OnBlink(){
  led_staus = "blink";
  Serial.println("LED Status: BLINK");
  server.send(200,"text/html",getHTML());
}
void handle_OffLED(){
  led_staus = "off";
  Serial.println("LED Status: OFF");
  server.send(200,"text/html",getHTML());
}

void handle_OnAlternate(){
  led_staus = "alternate";
  Serial.println("LED Status: ALTERNATE");
  server.send(200,"text/html",getHTML());
}

void handle_OntFound(){
  server.send(404,"text/html","Page Not Found");
}
