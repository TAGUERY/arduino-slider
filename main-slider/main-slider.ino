#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Initialisation du shield moteur et du moteur pas à pas
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

// Définition des broches et variables pour les boutons
const int speedPin = A0;
const int buttonPins[] = {13, 2};
const int btnNb = sizeof(buttonPins) / sizeof(buttonPins[0]);

int buttonStates[btnNb];
int lastButtonStates[btnNb];
unsigned long lastDebounceTimes[btnNb] = {0};
const unsigned long DEBOUNCE_DELAY = 50; // Temps de filtrage anti-rebond

// Variables de contrôle du moteur
int speedTogglerValue = 0;
int lastSpeedTogglerValue = -1;
bool motorState = false;
bool motorDirection = true;
int motorSpeed = 0;

int tempoRandom = false;

// Capteurs à ultrasons
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

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  // Configuration des boutons
  for (int i = 0; i < btnNb; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonStates[i] = HIGH;
    buttonStates[i] = HIGH;
  }

  // Initialisation du shield moteur
  if (!AFMS.begin())
  {
    Serial.println("Motor Shield not found.");
    while (1)
      ;
  }

  myMotor->setSpeed(10); // Vitesse initiale du moteur

  // Configuration des capteurs à ultrasons
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinBis, OUTPUT);
  pinMode(echoPinBis, INPUT);
}

// Gestion des boutons avec anti-rebond
void button()
{
  for (int i = 0; i < btnNb; i++)
  {
    int currentButtonState = digitalRead(buttonPins[i]);

    if (currentButtonState != lastButtonStates[i])
    {
      lastDebounceTimes[i] = millis();
    }

    if ((millis() - lastDebounceTimes[i]) > DEBOUNCE_DELAY)
    {
      if (currentButtonState != buttonStates[i])
      {
        buttonStates[i] = currentButtonState;
        if (buttonStates[i] == LOW)
        {
          if (i == 0)
            changeDirection(); // Bouton 1 : changement de direction
          if (i == 1)
            onoffMotor(); // Bouton 2 : allumer/éteindre le moteur
        }
      }
    }
    lastButtonStates[i] = currentButtonState;
  }
}

// Lecture et mise à jour de la vitesse via un potentiomètre
void speed()
{
  int newSpeedTogglerValue = analogRead(speedPin);

  if (abs(newSpeedTogglerValue - lastSpeedTogglerValue) > 5)
  {
    speedTogglerValue = newSpeedTogglerValue;
    lastSpeedTogglerValue = newSpeedTogglerValue;

    int newSpeed = map(speedTogglerValue, 0, 1023, 10, 200);
    if (newSpeed != motorSpeed)
    {
      motorSpeed = newSpeed;
      Serial.print("Vitesse : ");
      Serial.println(motorSpeed);
      myMotor->setSpeed(motorSpeed);
    }
  }
}

// Inverse la direction du moteur
void changeDirection()
{
  motorDirection = !motorDirection;
}

// Changement aléatoire de direction après un certain intervalle
void randomDirectionChange()
{
  if ((millis() - lastChangeTime) > 4000)
  {
    if (millis() - lastRandomChange > randomChangeInterval)
    {
      motorDirection = random(0, 2);
      lastRandomChange = millis();
    }
  }
}

// Mesure la distance avec le premier capteur et change la direction si un obstacle est proche
void measureDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance < 10 && (millis() - lastChangeTime) > changeDelay)
  {
    Serial.println(distance);
    changeDirection();
    lastChangeTime = millis();
  }
}

// Mesure la distance avec le deuxième capteur et change la direction si un obstacle est proche
void measureDistanceBis()
{
  digitalWrite(trigPinBis, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinBis, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinBis, LOW);

  durationBis = pulseIn(echoPinBis, HIGH);
  distanceBis = durationBis * 0.034 / 2;

  if (distanceBis < 10 && (millis() - lastChangeTime) > changeDelay)
  {
    Serial.println(distanceBis);
    changeDirection();
    lastChangeTime = millis();
  }
}

// Gère les différentes actions du moteur
void runMotor()
{
  button();
  speed();
  if (!tempoRandom)
  {
    randomDirectionChange();
  }
  measureDistance();
  measureDistanceBis();

  if (motorState)
  {
    int direction = motorDirection ? FORWARD : BACKWARD;
    myMotor->step(10, direction, DOUBLE);
  }
}

// Active ou désactive le moteur
void onoffMotor()
{
  motorState = !motorState;
  Serial.println(motorState ? "Moteur ALLUMÉ" : "Moteur ÉTEINT");
  if (!motorState)
  {
    myMotor->release(); // Libération du moteur quand il est éteint
  }
}

// Boucle principale
void loop()
{
  runMotor();
}
