#include<DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
int pos = 20;
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
#define DHTPIN A0     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11  (AM2302)
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
int sensorValue;
int counts = 0;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
int chk;
float hum;  //Stores humidity value
float temp; //Stores
String msg;
void setup()
{
  Serial.begin(9600);
  myservo.attach(11);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{ // myservo.write(0);  // tell servo to go to a particular angle
  msg = "";
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //x=0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sensorValue = analogRead(1);       //   read analog input pin 0

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;
  lcd.setCursor(0, 0);
  lcd.print("Tmp:");
  lcd.print(temp);// display the temperature
  lcd.setCursor(0, 1);
  lcd.print("hum:");
  lcd.print(hum); // display the humidity
  lcd.setCursor(10, 0);
  lcd.print("Air");
  lcd.print(sensorValue, DEC);
  lcd.setCursor(10, 1);
  lcd.print("LvL");
  lcd.print(distanceInch);
  //  Serial.print("Humidity: ");
  //  Serial.println(hum);
  //  Serial.print("Celsius");
  //  Serial.println(temp);
  //  Serial.print("AirQua=");
  //  Serial.println(sensorValue);
  //  //Serial.println(" PPM");
  //  Serial.print("distance:");
  //  Serial.print(distanceInch);
  //  Serial.println("inch");
  //  Serial.println("H: " + String(hum) + " T: " + String(temp) + " A: " + String(sensorValue) + " D: " + String(distanceInch));
  delay(1000); //Del
  //  Serial.println("Value of X: " + String(counts));
  msg = msg + "" + String(hum) + "_" + String(temp) + "_" + String(sensorValue) + "_" + String(distanceInch);
  Serial.print(msg);
  if (temp > 36 || distanceInch < 4 || sensorValue > 400)
  {
    if (counts == 0) 
    {
       myservo.write(pos+160);
      counts = 0;
      //        Serial.println("MOTOR OFF X 0");

      counts = 1;
    }
  }
  if (temp < 35 && distanceInch > 5 && sensorValue < 399 && counts == 1)
  {

    //      Serial.println("Motor ON X 1");
    myservo.write(pos);
    counts = 0;

  }
  Serial.flush();
}
