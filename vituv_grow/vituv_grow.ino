//nastaveni promenne

int pump = 3;
int air = 4;
int light = 5;
int button = 2;
int switchState = 0;
int pumpRunningTime = 0;
int pumpRunning = 0;
int manualPump = 0;
unsigned long minutes = 0;
unsigned long MINUTE = 60000;
unsigned long HOUR = 60 * MINUTE;
unsigned long THREE_HOURS = 3 * HOUR;
unsigned long DAY = 24 * HOUR;


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
  pumpRunning = 1;
}

void stopPump() {
  Serial.println("Stopping pump");
  digitalWrite(pump, LOW);
  pumpRunning = 0;
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
  switchState = digitalRead(button);
  
  if (switchState == HIGH) {
    manualPump = 1;
    digitalWrite (pump, HIGH);
  }
  else {
    manualPump = 0;
    digitalWrite(pump, LOW);
  }
  
  
  if ((millis() % 60000) == 0) {
    minutes++;
    
    Serial.println(minutes);
    
    if (minutes == 2 * HOUR)
      runAir();
    
    if (minutes == 6 * HOUR) {
      stopAir();
      runLight();
    }
    
    if (minutes == 18 * HOUR)
      stopLight();
    
    int shouldRunPump = (minutes % (3 * HOUR));
    
    if (!manualPump && shouldRunPump == 0) {
      runPump();
    }
    
    if (!manualPump && pumpRunning && pumpRunningTime > 3) {
      stopPump();
      pumpRunningTime = 0;
    }
    
    pumpRunningTime++;
    
    if (minutes > DAY)
      minutes = 0;
  }
}
