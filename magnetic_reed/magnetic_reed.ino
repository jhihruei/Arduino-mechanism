#define debug_mode true

#define sensor_PIN A3 
#define buzzer_PIN 7
#define switch_PIN 6
bool doorOpen = false;
int sensor;
void setup() {
  Serial.begin(9600);
  pinMode(buzzer_PIN,OUTPUT);
  pinMode(switch_PIN,OUTPUT);
  digitalWrite(buzzer_PIN,LOW);
  digitalWrite(switch_PIN,LOW);
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor = analogRead(sensor_PIN);
  if(debug_mode)
    Serial.println(sensor);
  if(!doorOpen and sensor<500){
    delay(1000); //wait for a while
    if(sensor<500){
      doorOpen = true;
      digitalWrite(switch_PIN,HIGH);
      buzz(100);
      delay(100);
      buzz(100);
    }
  }
  if(debug_mode){
    Serial.print("door control:");
    Serial.println(doorOpen);
  }
  delay(2000);
}

//buzzer buzz one time
void buzz(int ms){
  digitalWrite(buzzer_PIN,HIGH);
  delay(ms);
  digitalWrite(buzzer_PIN,LOW);
}
