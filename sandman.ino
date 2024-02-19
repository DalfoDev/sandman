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
... (70 lines left)
