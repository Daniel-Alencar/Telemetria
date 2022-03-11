#define tmp 2000

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("111111,111.11,111.11,111.11,1");
  delay(tmp);
  Serial.print("000000,000.00,000.00,000.00,0");
  delay(tmp);
}
