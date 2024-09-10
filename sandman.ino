Yellow_Dom
yellow_dom
Idle

markypoo — 10/09/2023 10:21 AM
heya tech e's (cecsy people)

u wanna meet over discord and discuss what approaches would be best (programming language, base station?, telemetry, etc?)
bao — 10/09/2023 10:57 AM
yes we should
cole — 10/09/2023 11:05 AM
If {sand} move {forward};
If {not} move {any}, then {cry};
If {sand} scoop {yes};

Guys it's not that hard
markypoo — 10/09/2023 11:48 AM
shut up mechy
but yeah that’s basically it
kaiya — 10/09/2023 1:10 PM
this looks ab right
cole — 10/09/2023 1:10 PM
I deserve all the credit for the coding of Sandman guys
markypoo — 11/22/2023 1:18 PM
temp:

int leftPin = 4;
int back = 4;

int rightPin = 5;
int forward = 5;

int forwardPin = 6;
int up = 6;

int backPin = 7;
int down = 7;

int rearLeft = 8;
int rearRight = 9;
int armServo = 10;

void setup() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(forwardPin, INPUT);
  pinMode(backPin, INPUT);
  
  pinMode(rearLeft, OUTPUT);
  pinMode(rearRight, OUTPUT);
  pinMode(armServo, OUTPUT);

  Serial.begin(9600);


}

void loop() {
  // Forward will set both rear wheels to high
  while (digitalRead(forward) == HIGH) {
    Serial.println("Forward pin active");
    delay(1000);
  }


}
markypoo
 started a thread: 
Servo doesnt work
. See all 
threads
.
 — 11/22/2023 5:56 PM
Thread
Servo doesnt work
2 Messages ›
There are no recent messages in this thread.
markypoo — 12/01/2023 12:15 PM
#include <LSS.h>

LSS myLSS;

// Input pins
int leftPin = 4;
Expand
message.ino
4 KB
gisselle — 12/01/2023 12:33 PM
let’s put a ss of it on the slides
?
markypoo — 12/01/2023 12:57 PM
of the code?
okay, but its not done yet
gisselle — 12/01/2023 2:00 PM
okay yeah whenever it is done we can add it in
﻿
#include <LSS.h>

LSS myLSS;

// Input pins
int leftPin = 4;
int rightPin = 5;
int forwardPin = 6;
int backPin = 7;

// Output pins
int rearRight = 9;
int rearLeft = 10;

// Analog joystick pins
#define VRX_PIN  A0
#define VRY_PIN  A1
int joystickPress = 2;


// Initialize global variables for controller tracking
bool forward;
bool left;
bool right;
bool backward;
bool servoControl;
bool servoReady = 1;

int joyXValue = 0; // To store value of the X axis
int joyYValue = 0; // To store value of the Y axis

void setup() {
  // Set pin modes
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(forwardPin, INPUT);
  pinMode(backPin, INPUT);

  pinMode(rearLeft, OUTPUT);
  pinMode(rearRight, OUTPUT);

  // Start the Serial monitor (printing/console.logging)
  Serial.begin(115200);

  myLSS.initBus(Serial, LSS_DefaultBaud);  // Use the default baud rate defined in LSS library

  myLSS.setMode(LSS_ModeSerial);
  myLSS.reset();
}

void loop() {
  // Update joystick positions
  joyXValue = analogRead(VRX_PIN);
  joyYValue = analogRead(VRY_PIN);

  char buffer[50]; // Adjust the size as needed
  snprintf(buffer, sizeof(buffer), "x: %d y: %d", joyXValue, joyYValue);
  Serial.println(buffer);


  // Define control bindings
  //   '0' can be replaced with redundancy control
  left = (!digitalRead(rightPin) && digitalRead(leftPin)) || joyXValue > 923;
  right = (!digitalRead(leftPin) && digitalRead(rightPin)) || joyXValue < 100;
  forward = (!digitalRead(backPin) && digitalRead(forwardPin)) || joyYValue < 350;
  servoControl = (!digitalRead(forwardPin) && digitalRead(backPin)) || joyYValue > 950; // || digitalRead(joystickPress);
  backward = (!digitalRead(rightPin) && !digitalRead(leftPin)) || 0; // Backward circuitry not set up. Does not do anything.

  // Prioritize forward control
  if (forward) {
    Serial.println("Onward!");
    goForward();
  } else {
    if (left) {
      Serial.println("PORT!");
      goLeft();
    } else {
      digitalWrite(rearRight, LOW); // Disable rear right wheel if no 
    }

    if (right) {
      Serial.println("STARBOARD!");
      goRight();
    } else {
      digitalWrite(rearLeft, LOW); // Disable rear left wheel if no 
    }
  }


  // Only run servo if it's ready for input
  if (servoControl && servoReady) {
    Serial.println("\t\tLAND HO!");
    runServo();
    delay(400);
  }

  // Set all motors to 0 
  //clearLocomotion();

  // // No backwards functionality on circuit
  // if (backward && 0) {
  //   Serial.println("Backwards attempted (lol)");
  //   goBackward();
  // }

  // Delay before continuing loop (polling rate)
  delay(50);
}

void runServo() {
  if (!servoReady) { return; }

  servoReady = 0;
  Serial.println("Servo booked.");

  clearLocomotion();
  delay(250);

  myLSS.move(200);
  // go forward
  delay(1000);  // to scoop
  // stop going forward
  myLSS.move(-950);
  // go backwards
  delay(1500);  // to jolt sand out of arm


  // arm back to normal position
  myLSS.move(0);
  delay(1000);  // to scoop

  servoReady = 1;

  Serial.println("Servo ready for input!");
}

void goForward() {
      Serial.println("Sandman -- Locomotion");
      Serial.println("\t Forward");

      digitalWrite(rearLeft, HIGH);
      digitalWrite(rearRight, HIGH);
}

void goBackward() {
      Serial.println("Sandman -- Locomotion");
      Serial.println("\t Backward");
}

void goLeft() {
      Serial.println("Sandman -- Locomotion");
      Serial.println("\t Left");
      digitalWrite(rearRight, HIGH);
}

void goRight() {
      Serial.println("Sandman -- Locomotion");
      Serial.println("\t Right");
      digitalWrite(rearLeft, HIGH);
}

void clearLocomotion() {
  digitalWrite(rearLeft, LOW);
  digitalWrite(rearRight, LOW);
  delay(250);
}

void demoMode() {

}
