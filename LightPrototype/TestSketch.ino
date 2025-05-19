constexpr int b {11};
constexpr int g {10};
constexpr int r {9};

constexpr int happy {A0};
constexpr int bored {A1};
constexpr int sad {A2};

int previousEmotion {happy};
int currentEmotion {happy};
int threshold { 50 }; // value required to change the light preventing natural missvalues.
bool isChanged {true}; // this value is set so it turns on the lights only the first time of changes.

double v_happy {};
double v_bored {};
double v_sad {};

void setup() { 
  pinMode(b, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(happy, INPUT);
  pinMode(bored, INPUT);
  pinMode(sad, INPUT);
  Serial.begin(9600);
}


void loop() {
  handleLastInput();
  turnOnCurrentLight();
}

void turnOnCurrentLight(){
  if(isChanged){
    switch(currentEmotion){
        case happy:
          happyLight();
          isChanged = false;
          break;
        case bored:
          boredLight();
          isChanged = false;
          break;
        case sad:
          sadLight();
          isChanged = false;
          break;
        default:
          happyLight();
          isChanged = false;
          break;
      }
  } 
}

void updateIsChanged(){
  if(currentEmotion != previousEmotion){
    isChanged = true;
  }
}

void handleLastInput(){
  v_happy = analogRead(happy);
  v_sad = analogRead(sad);
  v_bored = analogRead(bored);

  // this changes if a bottom is pressed 
  if(v_happy > threshold){
    currentEmotion = happy;
    updateIsChanged();
    previousEmotion = currentEmotion;
    return;
  } else if (v_sad > threshold){
    currentEmotion = sad;
    updateIsChanged();
    previousEmotion = currentEmotion;
    return;
  } else if (v_bored > threshold){
    currentEmotion = bored;
    updateIsChanged();
    previousEmotion = currentEmotion;
    return;
  }

  // otherwise nothing happens
  return;
}

void happyLight(){
  for(int i = 0; i <= 255; i++){
    analogWrite(b, i);
    analogWrite(g, i);
    analogWrite(r, 0);
    delay(5);
  }
}

void sadLight(){
  for(int i = 0; i <= 255; i++){
    analogWrite(b, i);
    analogWrite(g, 0);
    analogWrite(r, i);
    delay(5);
  }
}

void boredLight(){
  for(int i = 0; i <= 255; i++){
    analogWrite(b, i);
    analogWrite(g, i);
    analogWrite(r, i);
    delay(5);
  }
}



void handleInput(){
  v_happy = analogRead(happy);
  v_bored = analogRead(bored);
  v_sad = analogRead(sad);
}
