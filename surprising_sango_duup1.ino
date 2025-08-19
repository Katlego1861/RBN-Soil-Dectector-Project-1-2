#include <LiquidCrystal_I2C.h>
#include <math.h>
const int green = 2;
const int orange = 3;
const int red = 4 ;

int moist_value = 0;
int temp_value = 0;
int photo_value = 0;
int light_value = 0 ;
int humid_value = 0;

LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup()
{
  pinMode(green,OUTPUT);
  pinMode(orange,OUTPUT);
  pinMode(red,OUTPUT);
  
  
  //sensor inputs
  pinMode(A0,INPUT);//Soil moisture sensor 
  pinMode(A1, INPUT);// TEMP sensor
  pinMode(A2,INPUT); //PHOTO-RESISTOR SENSOR
  
  
  //Serial/LCD Monitor
  Serial.begin(9600);
lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Soil Detector");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("Initialising");
  indicateGreen();
  delay(500);
  indicateOrange();
  delay(500);
  indicateRed();
  delay(500);
  lcd.clear();
}

void loop()
{
  moist_value = map(analogRead(A0),0,876,0,100);
  Serial.print("moisture: ");
    Serial.println(moist_value);
  
  delay(500);
    
     temp_value = map( analogRead(A1),20,358,-40,125);
  Serial.print("Temperature: ");
    Serial.println(temp_value);
  
    delay(500);
  
   photo_value = analogRead(A2);
  Serial.print("Resistor: ");
    Serial.println(photo_value);
    delay(500);
}
//Functions for indicators


void indicateGreen(){
  digitalWrite(green, HIGH);
   digitalWrite(orange, LOW);
   digitalWrite(red, LOW);
}
void indicateOrange(){
  digitalWrite(green, LOW);
   digitalWrite(orange, HIGH);
  digitalWrite(red, LOW);
}


void indicateRed(){
  digitalWrite(green, LOW);
   digitalWrite(orange, LOW);
   digitalWrite(red, HIGH);
  delay(200);
  digitalWrite(red, LOW);
  delay(200);

}
//Functions for sensors
int read_soil(){
  return map(analogRead(A0),0,876,0,100);
}

int read_temp(){
  return map(analogRead(A1),20,358,-40,125);
}
int read_photo(){
  return analogRead(A2);
}
    
int read_humid(int T, int L){
  if(T > 30 && T < 45){
    if(L>5 && L<450){
      float vapour = 6.1078 * exp((17.269 * T) / (237.3 + T)); //e(millibars) = 6.1078 * exp((17.269 * T) / (237.3 + T)), where T is the temperature in degrees Celsius.
      float relative_humidity = 100*(exp((17.625*vapour)/
                                         (243.04+vapour))/
                                     exp((17.625*T)/(243.04+T))); //RH: =100*(EXP((17.625*TD)/(243.04+TD))/EXP((17.625*T)/(243.04+T)))
      return relative_humidity;
    }
    else{
      return 0;
    }
  }
  else{
    return 0;
    }
  }


void show_monitor(int s, int t, int l, int h){
  moist_value = s;
  Serial.print("Moisture: ");
  Serial.println(moist_value);
    lcd.setCursor(0,0);
  lcd.print("Moisture:");
  lcd.setCursor(9,0);
  lcd.print(moist_value);
  
  
  temp_value = t; // map(reading, min, max ,min, max)
  Serial.print("Temperature: ");
  Serial.println(temp_value);
  lcd.setCursor(0,1);
  lcd.print("Temperature: ");
  lcd.setCursor(12,1);
  lcd.print(temp_value);
  
  delay(2500);
  lcd.clear();
  
  light_value = l;
  Serial.print("Light: ");
  Serial.println(light_value);
  lcd.setCursor(0,0);
  lcd.print("Light: ");
  lcd.setCursor(7,0);
  lcd.print(light_value);
  
  humid_value = h;
  Serial.print("Humidity: ");
  Serial.println(humid_value);
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.setCursor(9,1);
  lcd.print(humid_value);
  
  delay(2500);
  lcd.clear();
}                              