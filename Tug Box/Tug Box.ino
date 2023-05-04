const int redLedPins[5] = {53, 52, 51, 50, 49};

const int scoreBoardPins[2][7] = {
  {45, 44, 43, 42, 41, 40, 39},
  {35, 34, 33, 32, 31, 30, 29}
};

const int greenLeds[2] = {48, 27};

const int playerStart[2] = {4, 2};
const int playerEnd[2] = {5, 3};

// Time
const long oneSecond = 1000;
long randomTime = 0;
long lastMillis = 0;

bool started = false;
int redLedStage = 0;
int playerScores[2] = {0, 0};

int player1In = 0;
int player2In = 0;

void setup() {
  // Set Output Pins
  for(int i = 0; i < 5; i++) {
    pinMode(redLedPins[i], OUTPUT);
  }

  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 7; j++) {
      pinMode(scoreBoardPins[i][j], OUTPUT);
    }
  }

  pinMode(greenLeds[0], OUTPUT);
  pinMode(greenLeds[1], OUTPUT);

  // Set Input Pins
  pinMode(playerStart[0], INPUT);
  pinMode(playerStart[1], INPUT);
  pinMode(playerEnd[0], INPUT);
  pinMode(playerEnd[1], INPUT);

  // Code for testing scoreboards
  // for(int i = 0; i < 2; i++) {
  //   for(int j = 0; j < 7; j++) {
  //     digitalWrite(scoreBoardPins[i][j], LOW);
  //   }
  // }

  drawNum(0, 7);
  drawNum(1, 9);

  for(int i = 0; i < 5; i++) {
    // digitalWrite(redLedPins[i], HIGH);
  }

  randomSeed(analogRead(5)); // Randomize using noise from analog pin 5
  randomTime = random(1000, 3000); // Set random time

  Serial.begin(9600); // Start serial

  setLedsLow();
  lastMillis = millis;  
}

void loop() {
//   // Get player inputs
//   player1In = digitalRead(playerEnd[0]);
//   player2In = digitalRead(playerEnd[1]);

//   // Serial.print("Player One Input: ");
//   // Serial.println(player1In);
//   // Serial.print("Player Two Input: ");
//   // Serial.println(player2In);

//   if (started) {
//     OnStarted();
//   } else {
//     countDown();
//   }
}

void OnStarted(){
  if (player1In && !player2In) {
    PlayerWin(0);
  }
  else if (!player1In && player2In){
    PlayerWin(1);
  }
  else if (player1In && player2In){
    Serial.println("TIE");
  }
  else {

  }
}

void resetGame(){
  started = false;
  redLedStage = 0;
  playerScores[0] = 0;
  playerScores[1] = 0;
  setLedsLow();
}

void drawNum(int player, int number) {
  for(int j = 0; j < 7; j++) {
    digitalWrite(scoreBoardPins[player][j], HIGH);
  }

  if (number == 0) {
    digitalWrite(scoreBoardPins[player][0], LOW);
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
  if (number == 1) {
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
  if (number == 2) {
    digitalWrite(scoreBoardPins[player][0], LOW);
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
  if (number == 3) {
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
  if (number == 4) {
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
  if (number == 5) {
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
  }
  if (number == 6) {
    digitalWrite(scoreBoardPins[player][0], LOW);
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
  }
  if (number == 7) {
    digitalWrite(scoreBoardPins[player][5], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
  if (number == 8) {
    digitalWrite(scoreBoardPins[player][0], LOW);
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
  if (number == 9) {
    digitalWrite(scoreBoardPins[player][1], LOW);
    digitalWrite(scoreBoardPins[player][2], LOW);
    digitalWrite(scoreBoardPins[player][3], LOW);
    digitalWrite(scoreBoardPins[player][4], LOW);
    digitalWrite(scoreBoardPins[player][5], LOW);
    digitalWrite(scoreBoardPins[player][6], LOW);
  }
}

void PlayerWin(int player) {
  digitalWrite(greenLeds[player], HIGH);
  digitalWrite(greenLeds[!player], LOW);

  playerScores[player]++;
  drawNum(player, playerScores[player]);
  
  Serial.print("Win: ");
  Serial.println(player);
  Serial.print("Loose: ");
  Serial.println(!player);

  delay(2000);
  resetGame();
}

void setLedsLow(){
  setRed(LOW);
  digitalWrite(greenLeds[0], LOW);
  digitalWrite(greenLeds[1], LOW);  
}

void countDown(){
  long currentMillis = millis(); // Get current millis

  // Check for premature pulls
  int player1Resting = digitalRead(playerStart[0]);
  int player2Resting = digitalRead(playerStart[1]);
  Serial.println(player2Resting);
  if(!player1Resting && player2Resting){
    PlayerWin(1);
  } else if (player1Resting && !player2Resting){
    PlayerWin(0);
  }

  // If not at last stage of red leds, activate more red leds
  if (redLedStage < 5){
    if (currentMillis - lastMillis > oneSecond){
      lastMillis = currentMillis; // Reset lastMillis
      redLedStage++;
      setRedColumn(redLedStage - 1, HIGH);
    }
  }

  // Once random time is over turn on green leds and set game to start
  else if (currentMillis - lastMillis > randomTime){
    digitalWrite(greenLeds[0], HIGH);
    digitalWrite(greenLeds[1], HIGH);
    setRed(LOW);
    started = true;    
  }
}

void setRedColumn(int col, uint8_t val){
  digitalWrite(redLedPins[col], val);
  digitalWrite(redLedPins[col], val);
}

void setRed(uint8_t val){
  for (int i = 0; i < 5; i++){
    digitalWrite(redLedPins[i], val);
  }
}
