const int redLedPins[2][5] = {
  {53, 52, 51, 50, 49},
  {22, 23, 24, 25, 26}
};

const int scoreBoardPins[2][7] = {
  {46, 45, 44, 43, 42, 41, 40},
  {29, 30, 31, 32, 33, 34, 35}
};

const int greenLeds[2] = {48, 27};

const int playerIn[2] = {47, 28};

// Time
const long oneSecond = 1000;
const long randomTime = 0;

long lastMillis = 0;

bool started = false;
int redLedStage = 0;
int playerScores[2] = {0, 0};

void setup() {
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 5; j++) {
      pinMode(redLedPins[i][j], OUTPUT);
    }
  }

  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 7; j++) {
      pinMode(scoreBoardPins[i][j], OUTPUT);
    }
  }

  pinMode(greenLeds[0], OUTPUT);
  pinMode(greenLeds[1], OUTPUT);

  pinMode(playerIn[0], INPUT);
  pinMode(playerIn[1], INPUT);

  // Code for testing scoreboards
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 7; j++) {
      digitalWrite(scoreBoardPins[i][j], LOW);
    }
  }

  randomSeed(analogRead(5)); // Randomize using noise from analog pin 5
  long randomTime = random(1000, 3000); // Set random time

  Serial.begin(9600); // Start serial

  setLedsLow();
  lastMillis = millis;  
}

void loop() {
  if (started) {
    OnStarted();
  } else {
    CountDown();
  }
}

void OnStarted(){
  int ply1In = digitalRead(playerIn[0]);
  int ply2In = digitalRead(playerIn[1]);
  // Serial.println(ply1In);
  // Serial.println(ply2In);

  if (ply1In && !ply2In) {
    PlayerWin(0);
    PlayerLoose(1);
    delay(2000);
  }
  else if (!ply1In && ply2In){
    PlayerWin(1);
    PlayerLoose(0);
    delay(2000);
  }
  else if (ply1In && ply2In){
    Serial.println("TIE");
  }
  else {

  }
}

void drawNum(int player, int number) {
  for(int j = 0; j < 7; j++) {
    digitalWrite(scoreBoardPins[player][j], HIGH);
  }

  if (number == 1) {
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
  }
  if (number == 2) {
    digitalWrite(scoreBoardPins[player][0], LOW);
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
  }
  if (number == 3) {
    digitalWrite(scoreBoardPins[player][0], LOW);
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
  }
}

void PlayerWin(int player) {
  digitalWrite(greenLeds[player], HIGH);
  digitalWrite(greenLeds[!player], LOW);

  playerScores[player]++;
  drawNum(player, playerScores[player]);
  
  Serial.println("Win: " + player);
  started = false;
}

void PlayerLoose(int player) {
  setRedPlayer(player, HIGH);
  setRedPlayer(!player, LOW);
  Serial.println("Loose: " + player);
}

void setLedsLow(){
  setRedPlayer(0, LOW);
  setRedPlayer(1, LOW);
  digitalWrite(greenLeds[0], LOW);
  digitalWrite(greenLeds[1], LOW);  
}

void CountDown(){
  long currentMillis = millis();
  // Serial.println(currentMillis);

  // If not at last stage of red leds, activate more red leds
  if (redLedStage < 5){
    if (currentMillis - lastMillis > oneSecond){
      lastMillis = currentMillis;
      redLedStage++;
      setRedColumn(redLedStage - 1, HIGH);
      Serial.print("redLedStage: ");
      Serial.println(redLedStage);
    }
  }

  // Once random time is over turn on green leds and set game to start
  else if (currentMillis - lastMillis > randomTime){
    digitalWrite(greenLeds[0], HIGH);
    digitalWrite(greenLeds[1], HIGH);
    setRedPlayer(0, LOW);
    setRedPlayer(1, LOW); 
    started = true;    
  }
}

void setRedColumn(int col, uint8_t val){
  digitalWrite(redLedPins[0][col], val);
  digitalWrite(redLedPins[1][col], val);
}

void setRedPlayer(int row, uint8_t val){
  for (int i = 0; i < 5; i++){
    digitalWrite(redLedPins[row][i], val);
  }
}
