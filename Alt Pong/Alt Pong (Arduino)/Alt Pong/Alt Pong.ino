const int buttonPin = 13;
const int echoPin = 12;
const int triggerPin = 11;

int startTime;

int lastButtonPressed = 0;
int lastSignalOut = 0;

int lastValues[20]; // {3,3,4,4,3} 5 => {5,3,3,4,4} 

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int buttonPressed = digitalRead(buttonPin);
  int signalOut = digitalRead(echoPin);

  // if(buttonPressed && !lastButtonPressed)
  // {
  //   Serial.println("Button Press");
  //   // digitalWrite(triggerPin, HIGH);
  //   // delay(5);
  //   // digitalWrite(triggerPin, LOW);
  // }

  if(signalOut && !lastSignalOut){
    startTime = millis();    
  }

  if(!signalOut && lastSignalOut){
    int deltaTime = millis() - startTime;

    pushValue(deltaTime);

    int average = getAverage();
    // Serial.print("Average: ");
    Serial.println(average);

    delay(5); // is this necessary?
    fireSensor();
  }

  lastSignalOut = signalOut;
  lastButtonPressed = buttonPressed;
}

void pushValue(int newValue) {
  int size = sizeof(lastValues) / sizeof(lastValues[0]);

  // Serial.println(size);

  for (int arrayPos = size - 1; arrayPos > 0; arrayPos--) {
    lastValues[arrayPos] = lastValues[arrayPos - 1];
  }

  lastValues[0] = newValue;

  // Serial.print(lastValues[0]);
  // Serial.print(", ");
  // Serial.print(lastValues[1]);
  // Serial.print(", ");
  // Serial.print(lastValues[2]);
  // Serial.print(", ");
  // Serial.print(lastValues[3]);
  // Serial.print(", ");
  // Serial.println(lastValues[4]);
}

int getAverage() {
  int total = 0;
  int size = sizeof(lastValues) / sizeof(lastValues[0]);

  // Serial.println(size);

  for (int arrayPos = 0; arrayPos < size; arrayPos++) {
    total += lastValues[arrayPos];
  }

  total *= 100;

  int average = total / size;
  return average;
}

void fireSensor() {
  digitalWrite(triggerPin, HIGH);
  delay(10);
  digitalWrite(triggerPin, LOW);
}
