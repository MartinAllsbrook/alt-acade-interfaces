int inputPin = A0;
int indicatorLEDPin = 13;

const int highThreshold = 400;
const int lowThreshold = 100;

bool sent;

void setup() {
  // put your setup code here, to run once:

  pinMode(inputPin, INPUT);
  pinMode(indicatorLEDPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int reading = analogRead(inputPin);

  int value = 0;

  if (reading > highThreshold && !sent) 
  {
    sent = true;
  } 
  else if (reading < lowThreshold && sent)
  {
    sent = false;
    value = 1;
  } 

  delay(20);

  Serial.println(value);
}
