#define BLYNK_TEMPLATE_ID "TMPL6LgQK4Td4"
#define BLYNK_TEMPLATE_NAME "Fire"
#define BLYNK_AUTH_TOKEN "CeP17Cj9PnhpBjvDzet5dP4NYtIHMrjn"

///These lines define some constants used in the Blynk project. The BLYNK_TEMPLATE_ID and BLYNK_TEMPLATE_NAME are used for Blynk's templating feature, which allows creating multiple projects with the same layout. The BLYNK_AUTH_TOKEN is the authentication token required to connect the hardware to the Blynk cloud.

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

///These lines include the necessary libraries. BLYNK_PRINT is used to enable debug messages on the Serial port. The ESP8266WiFi library provides functions to work with the Wi-Fi module on the ESP8266 board, and BlynkSimpleEsp8266.h is the library that allows the ESP8266 to communicate with the Blynk server.

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "PHONG 401"; 
char pass[] = "20072003"; 
///Here, the authentication token, Wi-Fi SSID, and password are stored in variables. The auth variable will be used to authenticate the hardware with the Blynk server, and the ssid and pass variables contain the Wi-Fi network credentials to connect to the local Wi-Fi network.
BlynkTimer timer;
///A BlynkTimer object is created. This timer is used to schedule periodic events and is particularly useful when you want to run certain functions at specific intervals.
#define fire D2
#define LED D5
#define buzzer  D7
int fire_Val = 0;
///Three constants are defined for the GPIO pins connected to the fire sensor, LED, and buzzer. These constants will make it easier to refer to these pins throughout the code.
WidgetLED led(V1);
///A WidgetLED object is created, which is associated with the Virtual Pin V1. This allows controlling the LED widget in the Blynk app through the code.
void setup() 
{
  Serial.begin(9600); 
  pinMode(LED, OUTPUT);
  pinMode(fire, INPUT);
  pinMode(buzzer, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(500L, mySensor);
}
///The setup() function is where the initial setup is done. It performs the following tasks:

// Initializes the Serial communication for debugging messages.
// Sets the LED and buzzer pins as output, and the fire pin as an input.
// Initiates the Blynk connection by calling Blynk.begin() with the authentication token and Wi-Fi credentials.
// Delays the code for 2000 milliseconds (2 seconds) to allow the Wi-Fi connection to establish.
// Sets the interval for the mySensor() function to be called every 500 milliseconds (0.5 seconds) using the timer.setInterval() function.
void loop() 
{
  Blynk.run();
  timer.run();
}
// In the loop() function, Blynk.run() is called to handle communication between the hardware and the Blynk server. The timer.run() function is called to allow the scheduled tasks (such as mySensor()) to be executed.
void mySensor()
{
  fire_Val = digitalRead(fire);
   
  if (fire_Val == LOW)
  {
    Blynk.logEvent("fire_alert");
    digitalWrite(LED, LOW);
    digitalWrite(buzzer, HIGH);
    Blynk.virtualWrite(V0, 1);
    Serial.print("fIRE Level: ");
    Serial.println(fire_Val);
    led.on();
  }

  else
  {
    digitalWrite(LED, HIGH);
    digitalWrite(buzzer, LOW);
    Blynk.virtualWrite(V0, 0);
    Serial.print("fIRE Level: ");
    Serial.println(fire_Val);
    led.off();
  }    
}
// The mySensor() function is a timer event handler. It is called every 500 milliseconds (as set in the setup() function). This function does the following:

// Reads the value from the fire sensor (D2) and stores it in the fire_Val variable.
// If the fire sensor reads LOW (indicating the presence of fire):
// It logs an event named "fire_alert" to Blynk using Blynk.logEvent().
// Turns on the LED and buzzer by setting the corresponding pins to LOW and HIGH, respectively.
// Sends a virtual write to V0 with the value 1 to update the corresponding widget in the Blynk app.
// Prints the fire level (0) to the Serial monitor.
// Turns on the LED widget in the Blynk app by calling led.on().
// If the fire sensor reads HIGH (indicating no fire):
// Turns off the LED and buzzer by setting the corresponding pins to HIGH and LOW, respectively.
// Sends a virtual write to V0 with the value 0 to update the corresponding widget in the Blynk app.
// Prints the fire level (1) to the Serial monitor.
// Turns off the LED widget in the Blynk app by calling led.off().