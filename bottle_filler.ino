// Pin Assignments
#define RELAY1 12   // Pump
#define RELAY2 6    // Lock
#define RELAY3 3    // Catch
#define RELAY4 9    // Actuator
#define BUZZER 7
#define IR_PIN 11   // IR sensor (Active HIGH)

int bottleCount = 0;
bool lastIRState = LOW;
bool sequenceRunning = false;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(IR_PIN, INPUT);

  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);
  digitalWrite(BUZZER, LOW);

  // ✅ Beep 2 times at startup
  Serial.println("System Starting...");
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(200);
  }
  Serial.println("System Ready");
}

void loop() {
  if (!sequenceRunning) {
    bool currentIRState = digitalRead(IR_PIN);
    delay(120);
    if (currentIRState == HIGH && lastIRState == LOW) {
      bottleCount++;
      Serial.print("Bottle Count: ");
      Serial.println(bottleCount);
    }
    lastIRState = currentIRState;

    if (bottleCount >= 4) {
      sequenceRunning = true;
      Serial.println("4 Bottles Detected - Starting Relay Sequence");

      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);

      Serial.println("Relay2 (Lock) ON");
      Serial.println("Relay3 (Catch) ON");
      digitalWrite(RELAY2, LOW);
      delay(10);
      digitalWrite(RELAY3, HIGH);


      Serial.println("Relay4 (Actuator) ON");
      digitalWrite(RELAY4, HIGH);
      delay(1400);

      Serial.println("Relay1 (Pump) ON");
      digitalWrite(RELAY1, HIGH);

      delay(8000);

      Serial.println("Relay1 (Pump) OFF");
      digitalWrite(RELAY1, LOW);

      delay(500);

      Serial.println("Relay4 (Actuator) OFF");
      digitalWrite(RELAY4, LOW);

      delay(1500);

      Serial.println("Relay3 (Catch) OFF");
      Serial.println("Relay2 (Lock) OFF");
      digitalWrite(RELAY3, LOW);
      delay(1000);
      digitalWrite(RELAY2, HIGH);

      delay(3500);
      digitalWrite(RELAY2, LOW);

      Serial.println("Cycle Complete. Resetting...");
      bottleCount = 0;
      sequenceRunning = false;
    }
  }
}
