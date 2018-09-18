
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

#include <ESP8266WiFi.h>
 
const char* ssid = "EEELAB VISUAL";
const char* password = "B2139420";
 
WiFiServer server(80);
int value = LOW;
 
void setup() {

  Serial.begin(9600);
   myservo.attach(D7);  // attaches the servo on GIO2 to the servo object 
   myservo.write(0);
  delay(10);
 

 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

 void servoOn (){
  int pos1;
 
 pos1 = 60;
 myservo.write(pos1); 
 delay(15);
 value = HIGH;
 }
 /*
  void servoBack (){
  int pos3;
 
 pos3 = 20;
 myservo.write(pos3); 
 delay(15);
 value = LOW;
 }*/
 
   void servoOff (){
  int pos2;
 
 pos2 = 0;
 myservo.write(pos2); 
 delay(15);
 value = LOW;
 }
 
void loop() {
  // Check if a client has connected
   
  WiFiClient client = server.available();
  if (!client) {
    return;

     
      
  }
 

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 

  if (request.indexOf("/SERVO=ON") != -1) {
                       // in steps of 1 degree 
   servoOn();
   delay(1500);
   servoOff();
  
    
 
  } 

/*  if (request.indexOf("/SERVO=OFF") != -1){
     servoOff();
  }
 */
 

 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
//  client.print("Servo pin is now: ");
 
/*  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }*/
  client.println("<br><br>");
  client.println("Click <a href=\"/SERVO=ON\">here</a> to Spray <br>");
 // client.println("Click <a href=\"/SERVO=OFF\">here</a> Debug Servo<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
