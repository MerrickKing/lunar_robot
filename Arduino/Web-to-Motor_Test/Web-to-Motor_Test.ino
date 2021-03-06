#include <Wire.h>

#define addrArduino 0x60
#define PIN_DIR 4
#define PIN_STEP 5
#define STEP_ANGLE 0.9
#define MICROSTEP_SETTING 32

const double MICROSTEP_RATIO = 1.0 / MICROSTEP_SETTING;

float rpm = 0;

int receiveBuffer[5] = {0, 0, 0, 0, 0};

void setup()
{
  Wire.begin(addrArduino);  // join I2C bus with address 0x60
  Wire.onReceive(eOnReceive);
  Serial.begin(115200);

  //Serial.println("IT IS BEGUN");

  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_STEP, OUTPUT);
  digitalWrite(PIN_DIR, LOW);
  digitalWrite(PIN_STEP, LOW);
}

void loop()
{
  if (rpm < 0) digitalWrite(PIN_DIR, HIGH);
  else digitalWrite(PIN_DIR, LOW);
  
  if (rpm != 0)
  {
    digitalWrite(PIN_STEP, HIGH);
    delayMicroseconds(rpm2delayms(rpm) / 2);
    digitalWrite(PIN_STEP, LOW);
    delayMicroseconds(rpm2delayms(rpm) / 2);
  }
}

void eOnReceive(int numBytes)
{
  Serial.print("\n[Receiving Command]\nNumber of bytes received: "); Serial.println(numBytes);
  int count = 0;

  while(Wire.available() )
  {
    receiveBuffer[count] = Wire.read();
    Serial.print("  =>"); Serial.println(receiveBuffer[count++]);
  }
  rpm = receiveBuffer[1];
  if (rpm > 127) rpm -= 256;
  
  if(receiveBuffer[0] == 1) Serial.println("  Using the drill!");
  else Serial.println("  Moving!");
}

int rpm2delayms(float rpm)
{
  return abs(MICROSTEP_RATIO * STEP_ANGLE * 60 * 1000000 / (rpm * 360) );
}
