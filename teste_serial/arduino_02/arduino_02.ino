#define led 13

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  if(Serial.available() > 0) {
    char c = Serial.read();
    if(c=='A') {
      digitalWrite(led,HIGH);
    }
    if(c=='a'){
      digitalWrite(led,LOW);
    }
  }
}
