#include <SoftwareSerial.h>     // 소프트웨어 시리얼 라이브러리 불러옴

int BT_RXD = 12; // 아두이노측 수신부 RXD는 12번핀(HC-06측 송신부 TXD와 연결)
int BT_TXD = 13; // 아두이노측 송신부 TXD는 13번핀(HC-06측 수신부 RXD와 연결)

SoftwareSerial bluetooth(BT_RXD, BT_TXD);   // 소프트웨어 시리얼 bluetooth 객체 선언
//defining the pins used for each drink, you can changes this depending how you connect the pumps and the drinks.

int Whiskey = 2;
int LimeJuice = 3;
int OrangeJuice = 4;
int Sprite = 5;
int state = 0;
// how much time there is between switching to the next pump.
int TimeBetweenPours = 500;


void setup()
{

    Serial.begin(9600);
    bluetooth.begin(9600);
    Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!");
    // Set pin 2-9 to output pins to drive the relay board
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);



    // 

    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);

}

void loop()

{
  if (bluetooth.available()) {
          state = bluetooth.read(); // Reads the data from the serial port
          Serial.println(state);
  }
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }


    // Cocktails:


    //Whiskey sprite
    if (state == 'a')
    {
        Serial.println("Whiskey Sprite in the making");
        Mix(1500, 7000, 0, 0); // Whiskey, Sprite, LimeJuice, OrangeJuice 
    }

    // WhiOLa
    if (state == 'b')
    {
        Serial.println("WhiOLa in the making");
        Mix(2500, 0, 1500, 4000); // Whiskey, Sprite, LimeJuice, OrangeJuice  
    }


    // WhiLaIte
    if (state == 'c')
    {
        Serial.println(" WhiLaIte in the making");
        Mix(2000, 5000, 1500, 0); //Whiskey, Sprite, LimeJuice, OrangeJuice
    }


    // Testin and maintenance options

    // Set-up Whiskey
    if (state == 'm')
    {
        Serial.println("Set-up Whiskey");
        Mix(2100, 0, 0, 0); // Whiskey, Sprite, LimeJuice, OrangeJuice
    }

    // Set-up Sprite
    if (state == 'n')
    {
        Serial.println("Set-up Sprite");
        Mix(0, 2100, 0, 0); //Whiskey, Sprite, LimeJuice, OrangeJuice
    }


    // Set-up LimeJuice
    if (state == 'o')
    {
        Serial.println("Set-up LimeJuice");
        Mix(0, 0, 2100, 0); // Whiskey, Sprite, LimeJuice, OrangeJuice
    }

    // Set-up Orange juice
    if (state == 'p')
    {
        Serial.println("Set-up Orange juice");
        Mix(0, 0, 0, 2100); // Whiskey, Sprite, LimeJuice, OrangeJuice
    }


    // Set-up all (intial first time after cleaning)
    if (state == 'u')
    {
        Serial.println("Set-up All");
        Mix(1100, 1100, 1100, 1100); // Whiskey, Sprite, LimeJuice, OrangeJuice
    }
    // clearing (intial first time after cleaning)
    if (state == 116)
    {
        Serial.println("Set-up All");
        Mix(1100, 1100, 1100, 1100); // Whiskey, Sprite, LimeJuice, OrangeJuice
    }

}

void Mix(int DelayTimeWhiskey, int DelayTimeLimeJuice, int DelayTimeOrangeJuice, int DelayTimeSprite)
{

    state = 0;
    delay(800);
    digitalWrite(Whiskey, LOW);
    delay(DelayTimeWhiskey);
    digitalWrite(Whiskey, HIGH);
    delay(TimeBetweenPours);

    digitalWrite(LimeJuice, LOW);
    delay(DelayTimeLimeJuice);
    digitalWrite(LimeJuice, HIGH);
    delay(TimeBetweenPours);

    digitalWrite(OrangeJuice, LOW);
    delay(DelayTimeOrangeJuice);
    digitalWrite(OrangeJuice, HIGH);
    delay(TimeBetweenPours);

    digitalWrite(Sprite, LOW);
    delay(DelayTimeSprite);
    digitalWrite(Sprite, HIGH);
    delay(TimeBetweenPours);


    Serial.println("완성!");
    state = 0;

}
