int pump = 3;
int air = 4;
int light = 5;
long time = 0;

void setup() {
  pinMode(air, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(light, OUTPUT);
}



void loop() {
    delay(1000);
    time++;
    Serial.println(time);
}
