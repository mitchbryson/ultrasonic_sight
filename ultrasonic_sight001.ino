/*
Ultrasonice Sight Device: uses an Arduino Uno connected to a Sonar Range Sensor and Buzzer
This code will produce beeps that get faster as an object gets closer.
*/

// Define variables for how the code works
int const max_distance = 100;

// Define pins for ultrasonic and buzzer
#define TRIGGERPIN 10
#define ECHOPIN 9
#define BUZZERPIN 2

void setup() {
  pinMode(TRIGGERPIN, OUTPUT); // Pulses will be sent out of the Arduino
  pinMode(ECHOPIN, INPUT); // Echo pulses will be received in to the Arduino
  pinMode(BUZZERPIN, OUTPUT); // Arduino controls whether the buzzer is on or off
}

// beep_rate: This function controls the rate of beeping based on distance
void beep_rate(int distance) {
  int num_beeps = 1;
  int beep_sep = distance;
  if (distance < 20) {
    beep_sep = 20;
  }
  for (int i = 0; i < num_beeps; i++) {
    digitalWrite(BUZZERPIN, HIGH);
    delay(distance);
    digitalWrite(BUZZERPIN, LOW);
    delay(distance);
  }
}

// This function is called repeated in a loop to control the whole system
void loop() {
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
  
  // Send an output pulse to the sonar sensor (1ms wide)
  digitalWrite(TRIGGERPIN, HIGH);
  delay(1); // wait 1ms
  digitalWrite(TRIGGERPIN, LOW);
  
  // Measure the time taken to receive the pulse back
  // Will be "0" or "-1" if no pulse is received
  int duration = pulseIn(ECHOPIN, HIGH);
  
  // Formula for the distance is half the duration, then divided by 29.1
  // to get distance in cm
  int distance = (duration/2) / 29.1;
  
  // if distance less than 0.5 meter and more than 0 (0 or less means over range)
  if (distance <= max_distance && distance >= 0) {
    digitalWrite(BUZZERPIN, HIGH); // Buzz
    //beep_rate(distance); // Alternative way of beeping
  } else {
    // Don't buzz
    digitalWrite(BUZZERPIN, LOW);
  }
  
  // Wait for 60ms until running the code again in a loop
  delay(60);
  
}
