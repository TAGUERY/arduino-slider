#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

const int speedPin = A0;
const int buttonPins[] = { 13, 2 };
const int btnNb = sizeof(buttonPins) / sizeof(buttonPins[0]);

int buttonStates[btnNb];
int lastButtonStates[btnNb];
unsigned long lastDebounceTimes[btnNb] = { 0 };
const unsigned long DEBOUNCE_DELAY = 50;

int speedTogglerValue = 0;
int lastSpeedTogglerValue = -1;
bool motorState = false;
bool motorDirection = true;
int motorSpeed = 0;

int tempoRandom = false;

const int trigPinBis = 3;
const int echoPinBis = 4;
const int trigPin = 5;
const int echoPin = 6;

long duration, durationBis;
int distance, distanceBis;
unsigned long lastChangeTime = 0;
const unsigned long changeDelay = 1000;

unsigned long lastRandomChange = 0;
const unsigned long randomChangeInterval = 800;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  for (int i = 0; i < btnNb; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonStates[i] = HIGH;
    buttonStates[i] = HIGH;
  }

  if (!AFMS.begin()) {
    Serial.println("Motor Shield not found.");
    while (1)
      ;
  }

  myMotor->setSpeed(10);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinBis, OUTPUT);
  pinMode(echoPinBis, INPUT);
}

void button() {
  for (int i = 0; i < btnNb; i++) {
    int currentButtonState = digitalRead(buttonPins[i]);

    if (currentButtonState != lastButtonStates[i]) {
      lastDebounceTimes[i] = millis();
    }

    if ((millis() - lastDebounceTimes[i]) > DEBOUNCE_DELAY) {
      if (currentButtonState != buttonStates[i]) {
        buttonStates[i] = currentButtonState;
        if (buttonStates[i] == LOW) {
          if (i == 0) changeDirection();
          if (i == 1) onoffMotor();
        }
      }
    }
    lastButtonStates[i] = currentButtonState;
  }
}

void speed() {
  int newSpeedTogglerValue = analogRead(speedPin);

  if (abs(newSpeedTogglerValue - lastSpeedTogglerValue) > 5) {
    speedTogglerValue = newSpeedTogglerValue;
    lastSpeedTogglerValue = newSpeedTogglerValue;

    int newSpeed = map(speedTogglerValue, 0, 1023, 10, 200);
    if (newSpeed != motorSpeed) {
      motorSpeed = newSpeed;
      Serial.print("Vitesse : ");
      Serial.println(motorSpeed);
      myMotor->setSpeed(motorSpeed);
    }
  }
}

void changeDirection() {
  motorDirection = !motorDirection;
  //Serial.println(motorDirection ? "Avant" : "Arrière");
}

void randomDirectionChange() {
  if ((millis() - lastChangeTime) > 4000) {
    if (millis() - lastRandomChange > randomChangeInterval) {
      motorDirection = random(0, 2);
      //Serial.println(motorDirection ? "Changement sens : Avant" : "Changement sens : Arrière");
      lastRandomChange = millis();
    }
  }
}

void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance < 10 && (millis() - lastChangeTime) > changeDelay) {
    Serial.println(distance);
    changeDirection();
    lastChangeTime = millis();
  }
}

void measureDistanceBis() {
  digitalWrite(trigPinBis, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinBis, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinBis, LOW);

  durationBis = pulseIn(echoPinBis, HIGH);
  distanceBis = durationBis * 0.034 / 2;

  if (distanceBis < 10 && (millis() - lastChangeTime) > changeDelay) {
    Serial.println(distanceBis);
    changeDirection();
    lastChangeTime = millis();
  }
}

void runMotor() {
  button();
  speed();
  if (!tempoRandom) {
    randomDirectionChange();
  }
  measureDistance();
  measureDistanceBis();

  if (motorState) {
    int direction = motorDirection ? FORWARD : BACKWARD;
    myMotor->step(10, direction, DOUBLE);
  }
}

void onoffMotor() {
  motorState = !motorState;
  Serial.println(motorState ? "Moteur ALLUMÉ" : "Moteur ÉTEINT");
  if (!motorState) {
    myMotor->release();
  }
}

void loop() {
  runMotor();
}
