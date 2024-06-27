#include <arduinoFFT.h>
#include <LiquidCrystal_I2C.h>

#define samples 128
#define samplingFrequency 1000
 
int sharp = 10;
int tune = 11;
int flat = 12;

LiquidCrystal_I2C lcd(0x27, 16, 2);
arduinoFFT FFT = arduinoFFT();

unsigned int samplingPeriod;
unsigned long microseconds;

double vReal[samples];
double vImag[samples];

// const int buttonPin[6] = {1, 2, 3, 4, 5, 6};

void setup() 
{
  pinMode(12, OUTPUT);
  Serial.begin(115200);
  samplingPeriod = round(1000000*(1.0/samplingFrequency));

  pinMode(sharp, OUTPUT);
  pinMode(tune, OUTPUT);
  pinMode(flat, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  // lcd.print("E A D G B e");
}

void loop() 
{
  double peak = dominantFrequency();
  Serial.println(peak); 
  if((peak >= 62 && peak <= 102)) {
    lcd.clear();
    lcd.print("E A D G B e");
    lcd.setCursor(0, 1);
    lcd.print("E Low");
    eLow(peak);
  } else if(peak >= 100 && peak <= 120) {
    lcd.clear();
    lcd.print("E A D G B e");
    lcd.setCursor(0, 1);
    lcd.print("A");
    aString(peak);
  } else if(peak >= 121 && peak <= 165) {
    lcd.clear();
    lcd.print("E A D G B e");
    lcd.setCursor(0, 1);
    lcd.print("D");
    dString(peak);
  } else if(peak >= 165 && peak <= 210) {
    lcd.clear();
    lcd.print("E A D G B e");
    lcd.setCursor(0, 1);
    lcd.print("G");
    gString(peak);
  } else if(peak >= 210 && peak <= 290) {
    lcd.clear();
    lcd.print("E A D G B e");
    lcd.setCursor(0, 1);
    lcd.print("B");
    bString(peak);
  } else if(peak >= 290 && peak <= 380) {
    lcd.clear();
    lcd.print("E A D G B e");
    lcd.setCursor(0, 1);
    lcd.print("e High");
    eHigh(peak);
  } else {
    lcd.clear();
    lcd.print("E A D G B e");
    lcd.setCursor(0, 1);
    lcd.print("...");
  }
}

// To detect the dominant frequency around and if the guitar is near to us,
// it just detects the frequency of the strings
double dominantFrequency() {
  for(int i = 0; i < samples; i++) {
      microseconds = micros();
      vReal[i] = analogRead(0);
      vImag[i] = 0;
      while(micros() < (microseconds + samplingPeriod));
  }
 
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, samples);
  double peak = FFT.MajorPeak(vReal, samples, samplingFrequency);
  peak *= 0.990;
  return peak;
}

void eLow(double peak) {
  if(peak >= 81 && peak <= 86) {
    digitalWrite(tune, HIGH);
    delay(50);
    digitalWrite(tune, LOW);
  } else if (peak >= 62 && peak < 81) { // checking for a flat note
    digitalWrite(flat, HIGH);
    delay(50);
    digitalWrite(flat, LOW);
  } else if(peak > 86 && peak <= 102) { //checking for a sharp note
    digitalWrite(sharp, HIGH);
    delay(50);
    digitalWrite(sharp, LOW);
  }
}

void aString(double peak) {  
  if(peak >= 109 && peak <= 112) {
    digitalWrite(tune, HIGH);
    delay(50);
    digitalWrite(tune, LOW);
  } else if (peak >= 100 && peak < 109) { // checking for a flat note
    digitalWrite(flat, HIGH);
    delay(50);
    digitalWrite(flat, LOW);
  } else if(peak > 112 && peak <= 120) { //checking for a sharp note
    digitalWrite(sharp, HIGH);
    delay(50);
    digitalWrite(sharp, LOW);
  }
}

void dString(double peak) {
  if(peak >= 145 && peak <= 148) {
    digitalWrite(tune, HIGH);
    delay(50);
    digitalWrite(tune, LOW);
  } else if (peak >= 120 && peak < 145) { // checking for a flat note
      digitalWrite(flat, HIGH);
      delay(50);
      digitalWrite(flat, LOW);
  } else if(peak > 149 && peak <= 165) { //checking for a sharp note
      digitalWrite(sharp, HIGH);
      delay(50);
      digitalWrite(sharp, LOW);
  }
}

void gString(double peak) {
    if(peak >= 195 && peak <= 198) {
      digitalWrite(tune, HIGH);
      delay(50);
      digitalWrite(tune, LOW);
    } else if (peak >= 165 && peak < 195) { // checking for a flat note
      digitalWrite(flat, HIGH);
      delay(50);
      digitalWrite(flat, LOW);
    } else if(peak > 198 && peak <= 210) { //checking for a sharp note
      digitalWrite(sharp, HIGH);
      delay(50);
      digitalWrite(sharp, LOW);
    }
}

void bString(double peak) {
    if(peak >= 245 && peak <= 256) {
      digitalWrite(tune, HIGH);
      delay(50);
      digitalWrite(tune, LOW);
    } else if (peak >= 210 && peak < 245) { // checking for a flat note
      digitalWrite(sharp, HIGH);
      delay(50);
      digitalWrite(sharp, LOW);
    } else if(peak > 256 && peak <= 290) { //checking for a sharp note
      digitalWrite(flat, HIGH);
      delay(50);
      digitalWrite(flat, LOW);
    }
}

void eHigh(double peak) {
  if(peak >= 328 && peak <= 333) {
    digitalWrite(tune, HIGH);
    delay(50);
    digitalWrite(tune, LOW);
  } else if (peak >= 290 && peak < 327) { // checking for a flat note
    digitalWrite(flat, HIGH);
    delay(50);
    digitalWrite(flat, LOW);
  } else if(peak > 333 && peak <= 380) { //checking for a sharp note
    digitalWrite(sharp, HIGH);
    delay(50);
    digitalWrite(sharp, LOW);
  }
}
