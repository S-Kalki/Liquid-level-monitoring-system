// Pin connections
const int trigPin = 9;
const int echoPin = 8;

const int pumpPin = 7; // Connect to IN1 or ENA of L298N

const int tankHeight = 30; // cm (adjust to your tank height)
const int setPoint = 20;   // Desired minimum level in cm

long duration;
int distance;
int level;

void setup() {
  Serial.begin(9600); // For Bluetooth
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  level = tankHeight - distance;

  // Send only the water level value to Bluetooth
  Serial.println(level); // e.g., just "23"

  // Pump control logic
  if (level < setPoint) {
    digitalWrite(pumpPin, HIGH); // Turn ON pump
  } else {
    digitalWrite(pumpPin, LOW);  // Turn OFF pump
  }

  delay(1000); // Wait for 1 second before next reading
}
