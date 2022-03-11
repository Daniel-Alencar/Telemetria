#define led 5

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  if(Serial.available() > 0) {
    String str = Serial.readString();

    Serial.print(str);

    if(str.equals("111111,111.11,111.11,111.11,1")) {
      digitalWrite(led, HIGH);
      Serial.println("Aqui!");
    }
    if(str.equals("000000,000.00,000.00,000.00,0")){
      digitalWrite(led,LOW);
      Serial.println("Aqui embaixo!");
    }
  }
}
