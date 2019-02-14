#include <Wire.h>

//Declare pin numbers
int rLed = 9;     //Red LED pin number
int gLed = 10;    //Green LED pin number
int bLed = 11;    //Blue LED pin number
int button = 2;   //Button pin number

//Internal variables
String received;
int buttonState;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  //Set LED pins to Output mode
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);
}

void loop() {
  buttonState = digitalRead(button);    //Read button state
  if (buttonState == HIGH)  {           //Button is pressed
    received = "";                      //Clear the recieved string to accept a new one
    Wire.requestFrom(8, 11);            // request 11 bytes from slave device #8

    while (Wire.available()) {          // slave may send less than requested
      char c = Wire.read();             // receive a byte as character
      received = received + c;          //Add the character to the received string
    }
  }

  //Split the recieved string
  //String comes in the format of "xxx,xxx,xxx" which is a RGB color
  int firstComma = received.indexOf(',');                             //Find the location of the first comma
  int secondComma = received.indexOf(',', firstComma + 1);            //Find the location of the second comma

  String rString = received.substring(0, firstComma);                 //Get the red part of the string which is the beginning to the first comma
  String gString = received.substring(firstComma + 1, secondComma);   //Get the green part of the string which is between the two commas
  String bString = received.substring(secondComma + 1);               //Get the blue part of the string which is everything after the last comma

  //Convert the strings to ints
  int r = rString.toInt();
  int g = gString.toInt();
  int b = bString.toInt();

  //Write the colors to the LEDs
  analogWrite(rLed, r);
  analogWrite(gLed, g);
  analogWrite(bLed, b);

  //Delay
  delay(500);
}
