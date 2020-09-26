#define trigPin1 9
#define echoPin1 8
#define buzzer1 2
#define trigPin2 10
#define echoPin2 11
#define buzzer2 4
long duration, distance, UltraSensor1, UltraSensor2;
char data;
String SerialData = "";
void setup()
{
  Serial.begin (9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzzer1, OUTPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer2, OUTPUT);

  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);
}
void loop()
{
  SonarSensor(trigPin1, echoPin1);
  UltraSensor1 = distance;
  SonarSensor(trigPin2, echoPin2);
  UltraSensor2 = distance;

  while (Serial.available())
  {
    delay(10);
    data = Serial.read();
    SerialData += data;
  }

  if (SerialData == "display distance")
  {

    Serial.print("distance measured by the first sensor:");
    Serial.print(UltraSensor1);
    Serial.println("cm");

    Serial.print("distance measured by the second sensor:");
    Serial.print(UltraSensor2);
    Serial.println("cm");
    Serial.println("---------------------------------------------------------------------------------------------------------");
  }

  SerialData = "";
  if (UltraSensor1 <= 10)
  {
    digitalWrite(buzzer1, HIGH);
  }
  else
  {
    digitalWrite(buzzer1, LOW);
  }

  if (UltraSensor2 <= 10)
  {
    digitalWrite(buzzer2, HIGH);
  }
  else
  {
    digitalWrite(buzzer2, LOW);
  }
}

void SonarSensor(int trigPinSensor, int echoPinSensor)
{
  digitalWrite(trigPinSensor, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinSensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinSensor, LOW);
  duration = pulseIn(echoPinSensor, HIGH);
  distance = (duration / 2) / 29.1;
}
