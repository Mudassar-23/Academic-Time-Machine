#include <WiFi.h>

#define BLYNK_TEMPLATE_ID "TMPL6pwpZTC_4"
#define BLYNK_TEMPLATE_NAME "Air Quality System"
#define BLYNK_AUTH_TOKEN "p4fgpVUSD1Du5V_PyIRUL30hGNjyRWzY"

#include <BlynkSimpleEsp32.h>

// WiFi
char ssid[] = "FYPEEFAST-3"; //TP-LINK_8705FE
char pass[] = "fypeefast";   //78405608

// MQ135
#define MQ135_PIN 34

// Dust Sensor
#define DUST_PIN 35
#define DUST_LED 4

// LEDs
#define RED_LED 12
#define GREEN_LED 27

BlynkTimer timer;

// UPDATED THRESHOLDS (based on your real readings)
int gasThreshold = 800;
int aqiThreshold = 50;

// AQI calculation
int calculateAQI(float dustDensity) {
  if (dustDensity <= 50) {
    return map(dustDensity, 0, 50, 0, 50);
  } 
  else if (dustDensity <= 100) {
    return map(dustDensity, 51, 100, 51, 100);
  } 
  else if (dustDensity <= 250) {
    return map(dustDensity, 101, 250, 101, 200);
  } 
  else {
    return 300;
  }
}

void sendData() {

  // ===== GAS SENSOR =====
  int gasValue = analogRead(MQ135_PIN);

  // ===== DUST SENSOR =====
  digitalWrite(DUST_LED, LOW);
  delayMicroseconds(280);

  int voMeasured = analogRead(DUST_PIN);

  delayMicroseconds(40);
  digitalWrite(DUST_LED, HIGH);
  delayMicroseconds(9680);

  float voltage = voMeasured * (3.3 / 4095.0);
  float dustDensity = 170 * voltage - 0.1;

  //  Prevent negative values
  if (dustDensity < 0) dustDensity = 0;

  // ===== AQI =====
  int AQI = calculateAQI(dustDensity);

  // ===== SERIAL OUTPUT =====
  Serial.println("----- Air Quality Data -----");
  Serial.print("Gas Value      : ");
  Serial.println(gasValue);

  Serial.print("Dust Density   : ");
  Serial.print(dustDensity);
  Serial.println(" ug/m3");

  Serial.print("AQI            : ");
  Serial.println(AQI);

  Serial.println("----------------------------\n");

  // ===== BLYNK =====
  if (Blynk.connected()) {
    Blynk.virtualWrite(V1, gasValue);
    Blynk.virtualWrite(V2, dustDensity);
    Blynk.virtualWrite(V3, AQI);
  } else {
    Serial.println(" Blynk Not Connected");
  }

  // ===== ALERT LEDs =====
  if (AQI > aqiThreshold || gasValue > gasThreshold) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(MQ135_PIN, INPUT);
  pinMode(DUST_PIN, INPUT);
  pinMode(DUST_LED, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(DUST_LED, HIGH);

  //  Blynk connection
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}