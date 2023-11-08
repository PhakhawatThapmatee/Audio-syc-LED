#include <WiFi.h>
#include <WiFiManager.h>
#include <Adafruit_NeoPixel.h>
#include <arduinoFFT.h>
#include <PubSubClient.h>
#include <iostream>
#include <string>
#include <sstream>

#define matrixpin 13
#define sensorPin 36
#define sensorPin2 39
#define LEDPIN 14
#define NUM_LEDS 60
#define SAMPLES 128
#define SAMPLING_FREQUENCY 1200
#define NUM_BANDS
#define NOISE 3000
#define LED_WIDTH 16
#define LED_HEIGHT 8
#define MIC_THRESHOLD 4000

#define LED_G 25
#define LED_Y 33
#define LED_R 32
#define LED 2

#define neo12_PIN 12
#define neo12_num 12

Adafruit_NeoPixel Matrix(128, matrixpin, NEO_GRB + NEO_KHZ800); // Matrix
Adafruit_NeoPixel Strip(60, LEDPIN, NEO_GRB + NEO_KHZ800); // Strip
Adafruit_NeoPixel neo12(neo12_num, neo12_PIN, NEO_GRB + NEO_KHZ800);  // neo 12

arduinoFFT FFT = arduinoFFT(); // FFT

WiFiManager wm; // configWifi

// MQTT
const char* mqtt_server = "YOUR_SERVER";
const char* topic = "YOUR_TOPIC";
const char* client_id = "displayled";
WiFiClient espClient;
PubSubClient client(espClient);

String pattern_color_data;
int function_strip;
int function_matrix;
int functions;
int volume1[3];
int volume2[3];
int volume3[3];
int volume4[3];
int volume5[3];
int volume6[3];
int volume7[3];
int volume8[3];

unsigned int sampling_period_us;
unsigned long microseconds;
int ledBrightness = 10;
int ledDelay = 20;
int ledDelayset = 60;
int ledState = LOW;

double vReal[SAMPLES];
double vImag[SAMPLES];

int VolumeMatrix = 0;
int VolumeStrip = 0;
int levelMatrix = 0;
int levelStrip = 0;

int delayVolume;
int delayVolume2;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED, OUTPUT);

  Matrix.begin();
  Matrix.setBrightness(ledBrightness);
  Matrix.show();
  
  Strip.begin();
  Strip.setBrightness(ledBrightness);
  Strip.show();

  neo12.begin();  
  neo12.setBrightness(100);
  
  neo12.setPixelColor(0, neo12.Color(255, 0, 0));
  neo12.show();
  delay(300);
  neo12.setPixelColor(1, neo12.Color(255, 100, 0));
  neo12.show();
  delay(300);
  neo12.setPixelColor(2, neo12.Color(255, 150, 0));
  neo12.show();
  delay(300);
  neo12.setPixelColor(3, neo12.Color(255, 255, 0));
  neo12.show();
  delay(300);
  neo12.setPixelColor(4, neo12.Color(120, 255, 0));
  neo12.show();
  delay(300);
  neo12.setPixelColor(5, neo12.Color(0, 255, 0));
  neo12.show();
  delay(300);
  neo12.setPixelColor(6, neo12.Color(0, 255, 255));
  neo12.show();
  delay(300);
  neo12.setPixelColor(7, neo12.Color(0, 0, 255));
  neo12.show();
  delay(300);
  neo12.setPixelColor(8, neo12.Color(120, 0, 255));
  neo12.show();
  delay(300);
  neo12.setPixelColor(9, neo12.Color(255, 0, 255));
  neo12.show();
  delay(300);
  neo12.setPixelColor(10, neo12.Color(255, 0, 100));
  neo12.show();
  delay(300);
  neo12.setPixelColor(11, neo12.Color(255, 0, 0));
  neo12.show();
  delay(300);

  digitalWrite(LED_R, HIGH);
  delay(20);
  
  WiFiConnection(); // connected WiFi
  
  digitalWrite(LED_R, LOW);
  delay(10);
  digitalWrite(LED_Y, HIGH);

  client.setServer(mqtt_server, 1883); // mqtt
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect(client_id)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(topic);
    } else {
      Serial.println("Failed to connect to MQTT broker");
      delay(2000);
    }
  }
  client.setCallback(callback);

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  
  Serial.println("start...");
  
  digitalWrite(LED_Y, LOW);
  delay(10);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED, HIGH);
  neo12.clear();
}

void WiFiConnection(){
  if(wm.autoConnect("@Audio-Syc-LED")) {
    Serial.println("");
    Serial.println("Connected already WiFi :) ");
    Serial.println("IP Address : ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_R, LOW);
    delay(10);
    digitalWrite(LED_Y, HIGH);
    delay(10);
  } else {
    digitalWrite(LED_R, HIGH);
    Serial.println("failed to connect and hit timeout");
    delay(1000);
    ESP.restart();
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String num;
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    pattern_color_data += (char)payload[i];
  }
  Serial.println();
  Serial.println(pattern_color_data);
  colorData();
}

void colorData() {
  std::string str = pattern_color_data.c_str();
  char delimiter = ',';
  std::string value[25];  // ใช้ std::string แทน char arrays
  int count = 0;
    
  std::istringstream iss(str);
  std::string token;

  while (std::getline(iss, token, delimiter)) {
    value[count++] = token;
  }
  functions = stoi(value[0]);
  int num = 1;
  for(int i = 0; i < 3; i++) {
    volume1[i] = stoi(value[num]);
    num++;
  }
  for(int i = 0; i < 3; i++) {
    volume2[i] = stoi(value[num]);
    num++; 
  }
  for(int i = 0; i < 3; i++) {
    volume3[i] = stoi(value[num]);
    num++; 
  }
  for(int i = 0; i < 3; i++) {
    volume4[i] = stoi(value[num]);
    num++; 
  }
  for(int i = 0; i < 3; i++) {
    volume5[i] = stoi(value[num]);
    num++; 
  }
  for(int i = 0; i < 3; i++) { 
    volume6[i] = stoi(value[num]);
    num++; 
  }
  for(int i = 0; i < 3; i++) { 
    volume7[i] = stoi(value[num]);
    num++; 
  }
  for(int i = 0; i < 3; i++) { 
    volume8[i] = stoi(value[num]);
    num++; 
  }
  pattern_color_data = "";
  
}

int count = 0;
int state = 1;

void loop() {
   client.loop();
   double volume = 0;

   for (int i = 0; i < SAMPLES; i++) {
     if (functions == 1) {
      vReal[i] = analogRead(sensorPin);
    } else if (functions == 2) {
      vReal[i] = analogRead(sensorPin2);
    } else if (functions == 3) {
      vReal[i] = analogRead(sensorPin2);
    }
     vImag[i] = 0;
     volume += vReal[i];
  }
  
  // คำนวณ FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  
  // คำนวณระดับความเสียงโดยใช้ค่ารวมของ FFT
  for (int i = 0; i < SAMPLES / 2; i++) {
    volume += vReal[i];
  }
  volume /= (SAMPLES / 2);
  int redValue, greenValue, blueValue;
  if (volume > NOISE) {
    // คำนวณสี LED RGB ตามระดับความเสียง
    ledBrightness = map(volume, 0, 1023, 0, 255);
    delayVolume = map(volume, 0, 17050, 10, 40);
    delayVolume2 = map(volume, 0, 16590, 10, 50);

    if (volume <= 7950 ) {
      redValue = 0;
      greenValue = 0;
      blueValue = 0;
    }
    else if (volume > 7950   && volume <= 9250) { // volume 1
      levelMatrix = 1;
      levelStrip = 7;
      VolumeMatrix = 5;
      VolumeStrip = 15;
      redValue = volume1[0];
      greenValue = volume1[1];
      blueValue = volume1[2];
    }
    else if (volume > 9250   && volume <= 10550) { //volume 2
      levelMatrix = 2;
      levelStrip = 14;
      VolumeMatrix = 10;
      VolumeStrip = 25;
      redValue = volume2[0];
      greenValue = volume2[1];
      blueValue = volume2[2];
    }
    else if (volume > 10550  && volume <= 11850) { //volume 3
      levelMatrix = 3;
      levelStrip = 21;
      VolumeMatrix = 15;
      VolumeStrip = 30;
      redValue = volume3[0];
      greenValue = volume3[1];
      blueValue = volume3[2];
    }
    else if (volume > 11850   && volume <= 13150) { //volume 4
      levelMatrix = 4;
      levelStrip = 28;
      VolumeMatrix = 30;
      VolumeStrip = 35;
      redValue = volume4[0];
      greenValue = volume4[1];
      blueValue = volume4[2];
    }
    else if (volume > 13150   && volume <= 14450) { //volume 5
      levelMatrix = 5;
      levelStrip = 35;
      VolumeMatrix = 50;
      VolumeStrip = 40;
      redValue = volume5[0];
      greenValue = volume5[1];
      blueValue = volume5[2];
    }
    else if (volume > 14450   && volume <= 15750) { //volume 6
      levelMatrix = 6;
      levelStrip = 42;
      VolumeMatrix = 70;
      VolumeStrip = 45;
      redValue = volume6[0];
      greenValue = volume6[1];
      blueValue = volume6[2];
    }
    else if (volume > 15750 && volume <= 17050) { //volume 7
      levelMatrix = 7;
      levelStrip = 50;
      VolumeMatrix = 90;
      VolumeStrip = 50;
      redValue = volume7[0];
      greenValue = volume7[1];
      blueValue = volume7[2];
    }
    else if (volume > 17050) { //volume 8
      levelMatrix = 8;
      levelStrip = 60;
      VolumeMatrix = 110;
      VolumeStrip = 55;
      redValue = volume8[0];
      greenValue = volume8[1];
      blueValue = volume8[2];
    }
  }

  // funcion
  if (functions == 1) {
    functions1(VolumeMatrix, VolumeStrip, ledBrightness, redValue, greenValue, blueValue);
  }
  else if (functions == 2) {
    functions2(levelMatrix, levelStrip, delayVolume, ledBrightness, redValue, greenValue, blueValue);
  }
  else if (functions == 3) {
    functions3(levelMatrix, delayVolume2, ledBrightness, redValue, greenValue, blueValue);
  }
} // loop

// function 1
void functions1(int VolumeMatrix, int VolumeStrip, int ledBrightness, int redValue, int greenValue, int blueValue) {
  int light_matrix[128];
  int light_strip[60];
   for(int i = 0; i < VolumeMatrix; i++) {
    light_matrix[i] = random(128);    
    Matrix.setBrightness(ledBrightness);
    Matrix.setPixelColor(light_matrix[i], Matrix.Color(redValue,greenValue,blueValue));
  }
  for(int i = 0; i < VolumeStrip; i++) {
    light_strip[i] = random(60);
    Strip.setBrightness(ledBrightness);
    Strip.setPixelColor(light_strip[i], Matrix.Color(redValue,greenValue,blueValue));
  }
    int r1 = random(12);
    int r2 = random(12);
    int r3 = random(12);
    int r4 = random(12);
    neo12.setBrightness(ledBrightness);
    neo12.setPixelColor(r1, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r2, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r3, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r4, neo12.Color(redValue, greenValue, blueValue));
    
  Matrix.show();
  Strip.show();
  neo12.show();
  delay(delayVolume);
  Matrix.clear();
  Strip.clear();
  neo12.clear();
}

void functions2(int levelMatrix, int levelStrip, double delayVolume, int ledBrightness, int redValue, int greenValue, int blueValue) {
  Matrix.setBrightness(ledBrightness);
  Strip.setBrightness(ledBrightness);
  int C1[] = {56,48,40,32,24,16,8,0};
  int C2[] = {57,49,41,33,25,17,9,1};
  int C3[] = {58,50,42,34,26,18,10,2};
  int C4[] = {59,51,43,35,27,19,11,3};
  int C5[] = {60,52,44,36,28,20,12,4};
  int C6[] = {61,53,45,37,29,21,13,5};
  int C7[] = {62,54,46,38,30,22,14,6};
  int C8[] = {63,55,47,39,31,23,15,7};
  int C9[] = {120,112,104,96,88,80,72,64};
  int C10[] = {121,113,105,97,89,81,73,65};
  int C11[] = {122,114,106,98,90,82,74,66};
  int C12[] = {123,115,107,99,91,83,75,67};
  int C13[] = {124,116,108,100,92,84,76,68};
  int C14[] = {125,117,109,101,93,85,77,69};
  int C15[] = {126,118,110,102,94,86,78,70};
  int C16[] = {127,119,111,103,95,87,79,71};
int level[] = { volume1[0],volume1[1],volume1[2],
                  volume2[0],volume2[1],volume2[2],
                  volume3[0],volume3[1],volume3[2],
                  volume4[0],volume4[1],volume4[2],
                  volume5[0],volume5[1],volume5[2],
                  volume6[0],volume6[1],volume6[2],
                  volume7[0],volume7[1],volume7[2],
                  volume8[0],volume8[1],volume8[2]};
      int num = 0;
      int levelRandom01 = random(levelMatrix);
      for (int i = 0; i < levelRandom01; i++) {
        Matrix.setPixelColor(C1[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
      num = 0;
      int levelRandom02 = random(levelMatrix);
      for (int i = 0; i < levelRandom02; i++) {
        Matrix.setPixelColor(C2[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
      num = 0;
      int levelRandom03 = random(levelMatrix);
      for (int i = 0; i < levelRandom03; i++) {
        Matrix.setPixelColor(C3[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom04 = random(levelMatrix);
      for (int i = 0; i < levelRandom04; i++) {
        Matrix.setPixelColor(C4[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom05 = random(levelMatrix);
      for (int i = 0; i < levelRandom05; i++) {
        Matrix.setPixelColor(C5[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom06 = random(levelMatrix);
      for (int i = 0; i < levelRandom06; i++) {
        Matrix.setPixelColor(C6[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom07 = random(levelMatrix);
      for (int i = 0; i < levelRandom07; i++) {
        Matrix.setPixelColor(C7[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom08 = random(levelMatrix);
      for (int i = 0; i < levelRandom08; i++) {
        Matrix.setPixelColor(C8[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom09 = random(levelMatrix);
      for (int i = 0; i < levelRandom09; i++) {
        Matrix.setPixelColor(C9[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom10 = random(levelMatrix);
      for (int i = 0; i < levelRandom10; i++) {
        Matrix.setPixelColor(C10[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom11 = random(levelMatrix);
      for (int i = 0; i < levelRandom11; i++) {
        Matrix.setPixelColor(C11[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom12 = random(levelMatrix);
      for (int i = 0; i < levelRandom12; i++) {
        Matrix.setPixelColor(C12[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom13 = random(levelMatrix);
      for (int i = 0; i < levelRandom13; i++) {
        Matrix.setPixelColor(C13[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom14 = random(levelMatrix);
      for (int i = 0; i < levelRandom14; i++) {
        Matrix.setPixelColor(C14[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
       num = 0;
      int levelRandom15 = random(levelMatrix);
      for (int i = 0; i < levelRandom15; i++) {
        Matrix.setPixelColor(C15[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }
      num = 0;
      int levelRandom16 = random(levelMatrix);
      for (int i = 0; i < levelRandom16; i++) {
        Matrix.setPixelColor(C16[i], Matrix.Color(level[num],level[num+1],level[num+2]));
        num+=3;
      }

  // Strip
  if (levelStrip == 7) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
  } else if (levelStrip == 14) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 7; i < 14; i++) {
      Strip.setPixelColor(i, Strip.Color(level[3],level[4],level[5]));
    }
  } else if (levelStrip == 21) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 7; i < 14; i++) {
      Strip.setPixelColor(i, Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 14; i < 21; i++) {
      Strip.setPixelColor(i, Strip.Color(level[6],level[7],level[8]));
    }
  } else if (levelStrip == 28) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 7; i < 14; i++) {
      Strip.setPixelColor(i, Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 14; i < 21; i++) {
      Strip.setPixelColor(i, Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 21; i < 28; i++) {
      Strip.setPixelColor(i, Strip.Color(level[9],level[10],level[11]));
    }
  } else if (levelStrip == 35) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 7; i < 14; i++) {
      Strip.setPixelColor(i, Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 14; i < 21; i++) {
      Strip.setPixelColor(i, Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 21; i < 28; i++) {
      Strip.setPixelColor(i, Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 28; i < 35; i++) {
      Strip.setPixelColor(i, Strip.Color(level[12],level[13],level[14]));
    }
  } else if (levelStrip == 42) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 7; i < 14; i++) {
      Strip.setPixelColor(i, Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 14; i < 21; i++) {
      Strip.setPixelColor(i, Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 21; i < 28; i++) {
      Strip.setPixelColor(i, Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 28; i < 35; i++) {
      Strip.setPixelColor(i, Strip.Color(level[12],level[13],level[14]));
    }
    for (int i = 35; i < 42; i++) {
      Strip.setPixelColor(i, Strip.Color(level[15],level[16],level[17]));
    }
  } else if (levelStrip == 50) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 7; i < 14; i++) {
      Strip.setPixelColor(i, Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 14; i < 21; i++) {
      Strip.setPixelColor(i, Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 21; i < 28; i++) {
      Strip.setPixelColor(i, Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 28; i < 35; i++) {
      Strip.setPixelColor(i, Strip.Color(level[12],level[13],level[14]));
    }
    for (int i = 35; i < 42; i++) {
      Strip.setPixelColor(i, Strip.Color(level[15],level[16],level[17]));
    }
    for (int i = 42; i < 50; i++) {
      Strip.setPixelColor(i, Strip.Color(level[18],level[19],level[20]));
    }
  } else if (levelStrip == 60) {
    for (int i = 0; i < 7; i++) {
      Strip.setPixelColor(i, Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 7; i < 14; i++) {
      Strip.setPixelColor(i, Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 14; i < 21; i++) {
      Strip.setPixelColor(i, Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 21; i < 28; i++) {
      Strip.setPixelColor(i, Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 28; i < 35; i++) {
      Strip.setPixelColor(i, Strip.Color(level[12],level[13],level[14]));
    }
    for (int i = 35; i < 42; i++) {
      Strip.setPixelColor(i, Strip.Color(level[15],level[16],level[17]));
    }
    for (int i = 42; i < 50; i++) {
      Strip.setPixelColor(i, Strip.Color(level[18],level[19],level[20]));
    }
    for (int i = 50; i < 60; i++) {
      Strip.setPixelColor(i, Strip.Color(level[21],level[22],level[23]));
    }
  }
  int r1 = random(12);
    int r2 = random(12);
    int r3 = random(12);
    int r4 = random(12);
    neo12.setBrightness(ledBrightness);
    neo12.setPixelColor(r1, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r2, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r3, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r4, neo12.Color(redValue, greenValue, blueValue));
    
  Matrix.show();
  Strip.show();
  neo12.show();
  delay(delayVolume);
  Matrix.clear();
  Strip.clear();
  neo12.clear();
}

void functions3(int levelMatrix, double delayVolume, int ledBrightness, int redValue, int greenValue, int blueValue) {
  Matrix.setBrightness(ledBrightness);
  int C1[] = {31,88,39,96}; 
  int C2[] = {30,38,89,97,22,23,80,81,46,47,104,105}; 
  int C3[] = {29,37,90,98,21,13,14,15,72,73,74,82,45,53,54,55,112,113,114,106};
  int C4[] = {28,36,91,99,20,44,27,35,83,107,92,100}; 
  int C5[] = {18,19,26,34,42,43,84,85,93,101,109,108}; 
  int C6[] = {9,10,11,17,25,33,41,49,50,51,76,77,78,86,94,102,110,118,117,116,12,75,52,115};
  int C7[] = {4,5,6,7,4,65,66,67,60,61,62,63,64,120,121,122,123}; 
  int C8[] = {0,1,2,3,8,16,24,32,40,48,56,57,58,59,68,69,70,71,79,87,95,103,111,119,127,126,125,124};

  int s1[] = {28,29,30,31}; 
  int s2[] = {25,26,27,34,33,32}; 
  int s3[] = {22,23,24,37,36,35}; 
  int s4[] = {19,20,21,40,39,38}; 
  int s5[] = {15,16,17,18,41,42,43,44}; 
  int s6[] = {11,12,13,14,45,46,47,48}; 
  int s7[] = {6,7,8,9,10,49,50,51,52,53}; 
  int s8[] = {0,1,2,3,4,5,54,55,56,57,58,59}; 
              
  int level[] = { volume1[0],volume1[1],volume1[2],
                  volume2[0],volume2[1],volume2[2],
                  volume3[0],volume3[1],volume3[2],
                  volume4[0],volume4[1],volume4[2],
                  volume5[0],volume5[1],volume5[2],
                  volume6[0],volume6[1],volume6[2],
                  volume7[0],volume7[1],volume7[2],
                  volume8[0],volume8[1],volume8[2]};
  
  if (levelMatrix == 1) {
    for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
  } 
  else if (levelMatrix == 2 ) {
    for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C2[i], Matrix.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s2[i], Strip.Color(level[3],level[4],level[5]));
    }
  } 
  else if (levelMatrix == 3 ) {
    for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C2[i], Matrix.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 20; i++) {
      Matrix.setPixelColor(C3[i], Matrix.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s2[i], Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s3[i], Strip.Color(level[6],level[7],level[8]));
    }
    
  }
  else if (levelMatrix == 4) {
    for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C2[i], Matrix.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 20; i++) {
      Matrix.setPixelColor(C3[i], Matrix.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C4[i], Matrix.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s2[i], Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s3[i], Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s4[i], Strip.Color(level[9],level[10],level[11]));
    }
    
  }
  else if (levelMatrix == 5) {
    for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C2[i], Matrix.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 20; i++) {
      Matrix.setPixelColor(C3[i], Matrix.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C4[i], Matrix.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C5[i], Matrix.Color(level[12],level[13],level[14]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s2[i], Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s3[i], Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s4[i], Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 8; i++) {
      Strip.setPixelColor(s5[i], Strip.Color(level[12],level[13],level[14]));
    }
    
  }
  else if (levelMatrix == 6) {
    for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C2[i], Matrix.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 20; i++) {
      Matrix.setPixelColor(C3[i], Matrix.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C4[i], Matrix.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C5[i], Matrix.Color(level[12],level[13],level[14]));
    }
    for (int i = 0; i < 24; i++) {
      Matrix.setPixelColor(C6[i], Matrix.Color(level[15],level[16],level[17]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s2[i], Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s3[i], Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s4[i], Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 8; i++) {
      Strip.setPixelColor(s5[i], Strip.Color(level[12],level[13],level[14]));
    }
    for (int i = 0; i < 8; i++) {
      Strip.setPixelColor(s6[i], Strip.Color(level[15],level[16],level[17]));
    }
    
  }
  else if (levelMatrix == 7) {
     for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C2[i], Matrix.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 20; i++) {
      Matrix.setPixelColor(C3[i], Matrix.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C4[i], Matrix.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C5[i], Matrix.Color(level[12],level[13],level[14]));
    }
    for (int i = 0; i < 24; i++) {
      Matrix.setPixelColor(C6[i], Matrix.Color(level[15],level[16],level[17]));
    }
    for (int i = 0; i < 17; i++) {
      Matrix.setPixelColor(C7[i], Matrix.Color(level[18],level[19],level[20]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s2[i], Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s3[i], Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s4[i], Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 8; i++) {
      Strip.setPixelColor(s5[i], Strip.Color(level[12],level[13],level[14]));
    }
    for (int i = 0; i < 8; i++) {
      Strip.setPixelColor(s6[i], Strip.Color(level[15],level[16],level[17]));
    }
    for (int i = 0; i < 10; i++) {
      Strip.setPixelColor(s7[i], Strip.Color(level[18],level[19],level[20]));
    }
    
  }
  else if (levelMatrix == 8 ) {
    for (int i = 0; i < 4; i++) {
      Matrix.setPixelColor(C1[i], Matrix.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C2[i], Matrix.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 20; i++) {
      Matrix.setPixelColor(C3[i], Matrix.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C4[i], Matrix.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 12; i++) {
      Matrix.setPixelColor(C5[i], Matrix.Color(level[12],level[13],level[14]));
    }
    for (int i = 0; i < 24; i++) {
      Matrix.setPixelColor(C6[i], Matrix.Color(level[15],level[16],level[17]));
    }
    for (int i = 0; i < 17; i++) {
      Matrix.setPixelColor(C7[i], Matrix.Color(level[18],level[19],level[20]));
    }
    for (int i = 0; i < 28; i++) {
      Matrix.setPixelColor(C8[i], Matrix.Color(level[21],level[22],level[23]));
    }
    for (int i = 0; i < 4; i++) {
      Strip.setPixelColor(s1[i], Strip.Color(level[0],level[1],level[2]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s2[i], Strip.Color(level[3],level[4],level[5]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s3[i], Strip.Color(level[6],level[7],level[8]));
    }
    for (int i = 0; i < 6; i++) {
      Strip.setPixelColor(s4[i], Strip.Color(level[9],level[10],level[11]));
    }
    for (int i = 0; i < 8; i++) {
      Strip.setPixelColor(s5[i], Strip.Color(level[12],level[13],level[14]));
    }
    for (int i = 0; i < 8; i++) {
      Strip.setPixelColor(s6[i], Strip.Color(level[15],level[16],level[17]));
    }
    for (int i = 0; i < 10; i++) {
      Strip.setPixelColor(s7[i], Strip.Color(level[18],level[19],level[20]));
    }
    for (int i = 0; i < 12; i++) {
      Strip.setPixelColor(s8[i], Strip.Color(level[21],level[22],level[23]));
    }
  } 
  int r1 = random(12);
    int r2 = random(12);
    int r3 = random(12);
    int r4 = random(12);
    neo12.setBrightness(ledBrightness);
    neo12.setPixelColor(r1, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r2, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r3, neo12.Color(redValue, greenValue, blueValue));
    neo12.setPixelColor(r4, neo12.Color(redValue, greenValue, blueValue));
    
  Matrix.show();
  Strip.show();
  neo12.show();
  delay(delayVolume);
  Matrix.clear();
  Strip.clear();
  neo12.clear();
}
