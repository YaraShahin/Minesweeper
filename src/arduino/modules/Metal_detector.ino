//When the sensor detects metal, the siren and electromagnets open. else, closes.
#define metal_detector_pin  A0
#define electromagnets_pin 6
#define siren_pin 7

void setup() {
  Serial.begin(9600);
  pinMode(metal_detector_pin, INPUT);
  pinMode(electromagnets_pin, OUTPUT);
  pinMode(siren_pin, OUTPUT);
}

void loop() {
  int metal_detection = analogRead(metal_detector_pin);
  Serial.print(metal_detection);
  if (metal_detection>920){
    Serial.print("  >> There is a metal!");
    digitalWrite(electromagnets_pin, HIGH);
    digitalWrite(siren_pin, HIGH);
  }
  else{
      digitalWrite(electromagnets_pin, LOW);
      digitalWrite(siren_pin, LOW);
  }
  Serial.println("")
}
