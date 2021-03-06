#define NUM_SENSORS 4

#define I_FL 0
#define PIN_TRIG_FL 10
#define PIN_ECHO_FL 18

#define I_FR 1
#define PIN_TRIG_FR 13
#define PIN_ECHO_FR 3

#define I_BL 2
#define PIN_TRIG_BL 9
#define PIN_ECHO_BL 19

#define I_BR 3
#define PIN_TRIG_BR 11
#define PIN_ECHO_BR 2

const int PIN_TRIG[4] = { PIN_TRIG_FL, PIN_TRIG_FR, PIN_TRIG_BR, PIN_TRIG_BL };
const int PIN_ECHO[4] = { PIN_ECHO_FL, PIN_ECHO_FR, PIN_ECHO_BR, PIN_ECHO_BL };
const String names[4] = { "Front Left", "Front Right", "Back Left", "Back Right" };

#define US2CM(x) 0.343*x/2

long timeOfLastTrig = 0;
const int INTERVAL = 800;

long timer[6] = {0, 0, 0, 0, 0, 0};
long duration[6] = {0, 0, 0, 0, 0, 0};
int distance[6] = {0, 0, 0, 0, 0, 0};

void setup()
{
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    pinMode(PIN_TRIG[i], OUTPUT);
    pinMode(PIN_ECHO[i], INPUT);
    digitalWrite(PIN_TRIG[i], LOW);
  }
  attachInterrupt(digitalPinToInterrupt(PIN_ECHO[I_FL]), timeEcho<I_FL>, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ECHO[I_FR]), timeEcho<I_FR>, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(PIN_ECHO[I_R]), timeEcho<I_R>, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ECHO[I_BR]), timeEcho<I_BR>, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ECHO[I_BL]), timeEcho<I_BL>, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(PIN_ECHO[I_L]), timeEcho<I_L>, CHANGE);

  Serial.begin(115200);
  Serial.println("Starting...");
}

void loop()
{
  if (millis() - timeOfLastTrig > INTERVAL)
  {
    for (int i = 0; i < NUM_SENSORS; i++)  // putting the prints here causes a second of delay between a change and seeing it but it means they print nicer
    {
      Serial.print("-- Sensor at "); Serial.print(names[i]); Serial.println(" --");
      Serial.print("\tDuration: "); Serial.print(duration[i]); Serial.println("us.");
      Serial.print("\tDistance: "); Serial.print(distance[i]); Serial.println("mm.");
    }
    Serial.println();
    trigger();
  }
}

void trigger()
{
  for (int i = 0; i < NUM_SENSORS; i++) {
    digitalWrite(PIN_TRIG[i], HIGH);
  }
  
  delayMicroseconds(10);
  
  for (int i = 0; i < NUM_SENSORS; i++) {
    digitalWrite(PIN_TRIG[i], LOW);
  }
  
  timeOfLastTrig = millis();
}

template<int I>
void timeEcho()
{
  if (digitalRead(PIN_ECHO[I]) == HIGH) {
    timer[I] = micros();
  } else {
    duration[I] = micros() - timer[I];
    distance[I] = US2CM(duration[I]);
  }
}
