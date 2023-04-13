const int redLedPins[2][5] = {
  {50, 49, 46, 45, 42},
  {24, 27, 28, 31, 32}
};

const int greenLeds[2] = {41, 35};

const int playerIn[2] = {53, 23};

bool started = false;

void setup() {
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 5; j++) {
      pinMode(redLedPins[i][j], OUTPUT);
    }
  }

  pinMode(greenLeds[0], OUTPUT);
  pinMode(greenLeds[1], OUTPUT);

  pinMode(playerIn[0], INPUT);
  pinMode(playerIn[1], INPUT);

  randomSeed(analogRead(5)); // Randomize using noise from analog pin 5

  Serial.begin(9600); // Start serial

  CountDown();
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
  Serial.println("1: " + ply1In);
  Serial.println("2: " + ply2In);

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

void PlayerWin(int player) {
  digitalWrite(greenLeds[player], HIGH);
  digitalWrite(greenLeds[!player], HIGH);
  Serial.println("Win: " + player);
  started = false;
}

void PlayerLoose(int player) {
  SetRow(player, HIGH);
  SetRow(!player, LOW);
  Serial.println("Loose: " + player);
}

void CountDown(){
  SetRow(0, LOW);
  SetRow(1, LOW);
  digitalWrite(greenLeds[0], LOW);
  digitalWrite(greenLeds[1], LOW);

  for(int i = 0; i < 5; i++){
    delay(1000);
    SetColumn(i, HIGH);
  }

  long randomTime = random(1000, 3000);
  delay(randomTime);
  digitalWrite(greenLeds[0], HIGH);
  digitalWrite(greenLeds[1], HIGH);
  SetRow(0, LOW);
  SetRow(1, LOW); 
  started = true;
}

void SetColumn(int col, uint8_t val){
  digitalWrite(redLedPins[0][col], val);
  digitalWrite(redLedPins[1][col], val);
}

void SetRow(int row, uint8_t val){
  for (int i = 0; i < 5; i++){
    digitalWrite(redLedPins[row][i], val);
  }
}
