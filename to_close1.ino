// C++ code
#define TRIGPIN 2
#define ECHOPIN 3
#define buzzer 5
float duration,distance;
void setup()
{
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2); 
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGPIN, LOW);
  
duration=pulseIn(ECHOPIN,HIGH);
distance = (duration*.0343)/2;
Serial.print("Distance: ");
Serial.println(distance);
delay(100);
  if ((distance>150)&&(distance<=250)){
     digitalWrite(12, HIGH);
     tone(buzzer, 1000); // Low frequency tone
     delay(500);         // Slow buzz interval
     noTone(buzzer);
     delay(500);
  }
  else if((distance>100)&&(distance<150)){
     digitalWrite(12, HIGH);
     digitalWrite(11, HIGH);
     tone(buzzer, 1500); // medium frequency tone
     delay(300);         // medium buzz interval
     noTone(buzzer);
     delay(300);
  }
  else if(distance<100){
     digitalWrite(12, HIGH);
     digitalWrite(11, HIGH);  
     digitalWrite(10, HIGH);   
     tone(buzzer, 2000); // high frequency tone
     delay(100);         // fast buzz interval
     noTone(buzzer);
     delay(100);
  }
  else{
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);  
    digitalWrite(10, LOW);
    noTone(buzzer);
  }
}