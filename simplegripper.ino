

//Define Motor control pins and ADC pin
#define M1A 4
#define M1B 5
#define M1C A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  delay(20);
  stop_motor();
}
char data, data2;
unsigned long lastmillis = 0;
unsigned long currentmillis;
unsigned long timeout = 2500;
void loop() {

if (Serial.available() )
  {
    data = Serial.read();
    switch (data)
    {
       case 'o':
        {
        open_gripper(180);
        stop_at_threshold(55);
        }
        break;

        case 'c':
        {
          close_gripper(180);
          stop_at_threshold(55);
        }
        break;

        default:
          break;

    }
    }

  /*
  // put your main code here, to run repeatedly:
  open_gripper(180);
  stop_at_threshold(55);
  delay(2000);
  close_gripper(180);
  stop_at_threshold(55);
  delay(2000);
  */
}

void close_gripper(int pwmvalue)
{
  digitalWrite(M1A, LOW);
  analogWrite(M1B, pwmvalue);
}

void open_gripper(int pwmvalue)
{
  digitalWrite(M1A, HIGH);
  analogWrite(M1B, (255 - pwmvalue));
}

void stop_motor()
{
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, HIGH);
}


void stop_at_threshold(int thres)
// stope when the current feedback reaches the thres value
{
  lastmillis = millis();
  delay(20);
  while (analogRead(M1C) <= thres)
  {
    currentmillis = millis();
  if (currentmillis - lastmillis >= timeout)
  {
    break;
  }
  }
  
  /*delay(10);
  //check once again
  while (analogRead(M1C) <= thres)
  {
    ;
  }
*/
  stop_motor();
}
