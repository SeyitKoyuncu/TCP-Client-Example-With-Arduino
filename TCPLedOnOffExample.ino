#include <Ethernet.h> // library for ethernet shield
#include <SPI.h>
#include <Adafruit_NeoPixel.h> // library for leds getting light

// Network variables
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE }; //default mac adress for ethernet shield.
byte ip[] = { ***, ***, *, *** }; //give arduino ethernet shield to ip adress (do not write same with your server ip they have to different).
byte serverIP[] = { ***, ***, *, ***}; //server ip adress which you want to connect.
int port = ****; //server port number, wrtie to your own server port. 
EthernetClient client;


#define PIN 4 //pin number for give energy and signal to leds.
#define NUMPIXELS  50 //max led number (for my project this is 50, it can ve changeable)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // create neopixel variable, with pin and max led number.


void setup() {
  Ethernet.begin(mac, ip);  //start to ethernet connection.
  delay(100);
  pixels.begin(); //start to nopixels.
  
  while (!Serial && (millis() < 300));
  Serial.begin(9600);
  Serial.println("Connecting to server...");
  client.connect(serverIP, port);
}


//VARIABLES
byte controlMsg; //for check to the first message if it is 0x86 this meaning we can start to the proccess.
byte recMsg; // for chechk to the second message. It is for to make decision which led test we want to use
// 1 for ligts on just one led, 2 for lights all leds, 3 for off all leds.
byte ledData; // for light one led, take to this data which led number we want to light on.
int i;

  // i use client.stop() after every reading message from server 
  // because if i dont use it, variables cant be reading.
  
  void loop() {
    client.flush(); // clear the buffer.
    if (client.available() > 0) // check to the client. 
   {  
      controlMsg = client.read();
      client.stop();      
      if(controlMsg == 0x86)
      {
        recMsg = client.read();
        client.stop();
        
        if(recMsg == 1)
        {
          ledData = client.read();
          client.stop();;
          
          for(i = 0; i < 2; i++)
          {
            pixels.setPixelColor(ledData, pixels.Color(255,0,0)); //light on to the ledData led.
            pixels.show();   
            delay(100);         
          } 
        }

        else if(recMsg == 2)
        {
          for(i = 0; i < NUMPIXELS; i++)
          {
            pixels.setPixelColor(ledData, pixels.Color(255,0,0)); //light on to all leds.
            pixels.show();   
            delay(100);         
          }           
        }

        else if(recMsg == 3)
        {
          for(i = 0; i < NUMPIXELS; i++)
          {
            pixels.setPixelColor(ledData, pixels.Color(0,0,0)); //light of to the all leds.
            pixels.show();   
            delay(100);         
          }             
        }
       }
     }
   }
