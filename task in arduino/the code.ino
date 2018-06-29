int LED =10;
int PushButton =2;
#define TEMP_led 44                  
int tempPin = 1;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(PushButton, INPUT_PULLUP);// define pin two as input for push button
 pinMode(LED, OUTPUT);// defind pin 10 as output
   Serial.begin(9600);
   pinMode(TEMP_led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
   int pusshed = digitalRead(PushButton);// read pin 2 and put the result in the "pusshed" variable
  if(pusshed == LOW){
    Serial.println("pressed");
    while(pusshed)
    {}
    digitalWrite(LED, HIGH);// if pusheed is equal LOW, turn the pin 10 HIGH (give it 5v)
    Serial.println("ON");
  }else{
    digitalWrite(LED, LOW);// else set pin 10 to low or zero volt
    Serial.println("OFF");
  }
    //Rizk start
      int valTEMP=0;
      int TEMP_x = 0 ;
valTEMP = analogRead(tempPin);
// valTEMP = analogRead(A1);
 float mv = ( valTEMP/1024.0)*5000; 
 float cel = mv/10;
 float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
 Serial.print("*C");
 Serial.println();
 delay(1000);
if ( cel >= 40  )
{digitalWrite(TEMP_led, HIGH);
  TEMP_x = 1 ;
 }
else 
{digitalWrite(TEMP_led, LOW);}


}

