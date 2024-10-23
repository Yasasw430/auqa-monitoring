#define BLYNK_TEMPLATE_ID "TMPL3js_CAMzQ"
#define BLYNK_TEMPLATE_NAME "turbidity"
#define BLYNK_AUTH_TOKEN "YgOF-KJwjan8EOOhsD7rTJ_feoVtPTnV"
#define BLYNK_PRINT Serial
#define DHTPIN 23
#define DHTTYPE DHT11


#include<WiFi.h>
#include <DHT.h>
#include<ESP32Servo.h>
#include<BlynkSimpleEsp32.h>
const char ssid[] = "Act";
const char password[] = "12345678";
DHT dht(DHTPIN, DHTTYPE);

int turbiditySensor = 34;
int relayPin = 18;
Servo motor;
int turbidityThreshold = 500;


void setup() {
  pinMode(turbiditySensor, INPUT);
  pinMode(relayPin, OUTPUT);
  motor.attach(5);
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  Blynk.run();
float h=dht.readHumidity();
  float t=dht.readTemperature();
  if(isnan(h)||isnan(t))
  return;
  Serial.print("H: ");
  Serial.print(h);
  Serial.println("T: ");
  Serial.print(t);
  
  int turbidityValue = analogRead(turbiditySensor);
  Serial.println(turbidityValue);
  if (turbidityValue > turbidityThreshold) {
    Serial.println("water in bad condition");
    digitalWrite(relayPin,HIGH);
    Blynk.virtualWrite(V0, turbidityValue);
    Blynk.logEvent("bad_water", "water in dirty condition");
} else {
  Serial.println("water in good condition");
  digitalWrite(relayPin,LOW);
}
if(h>30){
  motor.write(90);
}
else{
motor.write(0);
}

}
