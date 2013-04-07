int button = 2;
int pump = 3;
int air = 4;
int light = 5;
int pumpRunningTime = 0;

unsigned long time = 0;
unsigned long oldtime = 0;

// time of the day when you're starting the program (in minutes)
unsigned long minutes = 0;

// real time simulation at the SPEED value 60000
int SPEED = 60000;

void setup() {
  Serial.begin(9600);
  pinMode(air, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(button, INPUT);
}

void runPump() {
  Serial.println("Starting pump");
  digitalWrite(pump, HIGH);
}

void stopPump() {
  Serial.println("Stopping pump");
  digitalWrite(pump, LOW);
}

void runAir() {
  Serial.println("Starting air");
  digitalWrite(air, HIGH);
}

void stopAir() {
  Serial.println("Stopping air");
  digitalWrite(air, LOW);
}

void runLight() {
  Serial.println("Starting light");
  digitalWrite(light, HIGH);
}

void stopLight() {
  Serial.println("Stopping light");
  digitalWrite(light, LOW);
}

void loop() {
  int pumpState = bitRead(PORTD, pump); 
  int airState = bitRead(PORTD, air);
  int lightState = bitRead(PORTD, light);
  int switchState = digitalRead(button);
  time = millis();
 
  if (switchState == HIGH && pumpState == 0)
    runPump();
  

  if (switchState == LOW && pumpState == 1) 
    stopPump();
    
  if ((time % SPEED) == 0 && oldtime != time) {
    Serial.print("Minutes: ");
    Serial.println(minutes);
    oldtime = time;
    minutes++;
    
    if (minutes >= 120 && minutes <= 360) {
      if (airState == 0)
        runAir();
    }
    else if (airState == 1)
      stopAir();
    
    if (minutes >= 360 && minutes <= 1080) {
      if (lightState == 0)
        runLight();
    }
    else if (lightState == 1)
      stopLight();
    
    int shouldRunPump = (minutes % (180));
    Serial.println(shouldRunPump);
    
    if (shouldRunPump == 0)
      runPump();
    
    if (pumpRunningTime > 3 && pumpState == 1) {
      stopPump();
      pumpRunningTime = 0;
    }
    
    pumpRunningTime++;
    
    if (minutes > 1440)
      minutes = 0;
  } 
}
