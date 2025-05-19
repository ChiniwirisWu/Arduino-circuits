constexpr int b {11};
constexpr int g {10};
constexpr int r {9};

constexpr int happy {A0};
constexpr int bored {A1};
constexpr int sad {A2};

int lastEmotion {happy}; // initialized with happy.
int threshold { 50 }; // value required to change the light preventing natural missvalues.

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
  switch(lastEmotion){
    case happy:
      happyLight();
      break;
    case bored:
      boredLight();
      break;
    case sad:
      sadLight();
      break;
    default:
      happyLight();
      break;
  }
}

void handleLastInput(){
  v_happy = analogRead(happy);
  v_sad = analogRead(sad);
  v_bored = analogRead(bored);

  // this changes if a bottom is pressed 
  if(v_happy > threshold){
    lastEmotion = happy;
    return;
  } else if (v_sad > threshold){
    lastEmotion = sad;
    return;
  } else if (v_bored > threshold){
    lastEmotion = bored;
    return;
  }

  // otherwise nothing happens
  return;
}

void happyLight(){
  analogWrite(b, 255);
  analogWrite(g, 255);
  analogWrite(r, 0);
}

void sadLight(){
  analogWrite(b, 250);
  analogWrite(g, 0);
  analogWrite(r, 255);
}

void boredLight(){
  analogWrite(b, 255);
  analogWrite(g, 255);
  analogWrite(r, 255);
}



void handleInput(){
  v_happy = analogRead(happy);
  v_bored = analogRead(bored);
  v_sad = analogRead(sad);
}
