#include <Servo.h>

//Pin definitions on the Arduino Nano for the joysticks analog values
#define joy2X A0
#define joy2Y A1
#define joy1X A2
#define joy1Y A3

//Pin definitions on the Arduino Nano for the joysticks digital values (joystick pressed)
int joy2SW = 2;
int joy1SW = 3;

//Pin definitions on the Arduino Nano for the PWM signals of the servomotors
int servoPin1 = 8;
int servoPin2 = 9;
int servoPin3 = 10;
int servoPin4 = 11;
int servoPin5 = 12;

//Creation of Servo type objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

//Variables definition
int xValue1, yValue1;
int xValue2, yValue2;

unsigned long previousMillis = 0;
const long interval = 20; //Update interval in milliseconds
const int speed = 3; //Speed definition for the movement (try to change it)

//setup function (called once at the beginning of the program)
void setup() {
  //Attach each pin to the respective object
  servo1.attach(servoPin1); 
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);

  //Define the type of circuit for the buttons
  pinMode(joy1SW, INPUT_PULLUP);
  pinMode(joy2SW, INPUT_PULLUP);

  //Serial communication initialization with a baud rate of 9600 bps (bits/second)
  Serial.begin(9600);
}

void loop() {
  //Read joystick values
  xValue1 = analogRead(joy1X);
  yValue1 = analogRead(joy1Y);
  xValue2 = analogRead(joy2X);
  yValue2 = analogRead(joy2Y);

  //Map joystick values to servo angles
  xValue1 = map(xValue1, 0, 1023, 0, 180);
  yValue1 = map(yValue1, 0, 1023, 0, 180);
  xValue2 = map(xValue2, 0, 1023, 0, 180);
  yValue2 = map(yValue2, 0, 1023, 0, 180);

  //Map joystick values to speed factors
  int speed1x = abs(map(xValue1, 0, 180, -speed, speed));
  int speed1y = abs(map(yValue1, 0, 180, -speed, speed));
  int speed2x = abs(map(xValue2, 0, 180, -speed, speed));
  int speed2y = abs(map(yValue2, 0, 180, -speed, speed));

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    //Read current servo positions
    int newPos1 = servo1.read();
    int newPos2 = servo2.read();
    int newPos3 = servo3.read();
    int newPos4 = servo4.read();

    //Update servo1 position
    if (yValue1 < 80) {
      newPos1 = constrain(newPos1 - speed1y, 0, 180);
    } else if (yValue1 > 100) {
      newPos1 = constrain(newPos1 + speed1y, 0, 180);
    }
    servo1.write(newPos1);

    //Update servo2 position
    if (xValue1 < 80) {
      newPos2 = constrain(newPos2 - speed1x, 0, 180);
    } else if (xValue1 > 100) {
      newPos2 = constrain(newPos2 + speed1x, 0, 180);
    }
    servo2.write(newPos2);

    //Update servo3 position
    if (xValue2 < 80) {
      newPos3 = constrain(newPos3 - speed2x, 0, 180);
    } else if (xValue2 > 100) {
      newPos3 = constrain(newPos3 + speed2x, 0, 180);
    }
    servo3.write(newPos3);

    //Update servo4 position
    if (yValue2 < 80) {
      newPos4 = constrain(newPos4 - speed2y, 0, 180);
    } else if (yValue2 > 100) {
      newPos4 = constrain(newPos4 + speed2y, 0, 180);
    }
    servo4.write(newPos4);

    //Button handling for servo5
    int etatBouton = digitalRead(joy1SW);
    if (etatBouton == LOW) {
      int positionActuelle = servo5.read();
      if (positionActuelle == 0) {
        servo5.write(180);
      } else {
        servo5.write(0);
      }
      delay(500);  //Small delay to debounce the button press
    }
  }
  
}
