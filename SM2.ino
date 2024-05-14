/*Libraries */

#include <dht.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

/*macros*/
#define DHT_PIN              11 //works pwm  and non pwm 
#define IR1                  2
#define IR2                  3
#define Door                 1 //  disconnect it before burnning code
#define Buzz1                9
#define RedLed               10
#define GreenLed             8
#define TempThreshold       25.0  // Temperature threshold for fan activation
#define HighTempThreshold   35.0 // Temperature threshold for high-temperature alarm
#define LDR                  A0
#define LED1                 12
#define Fan                  A3       //DC motor
#define buttonPin            A2      // Pin connected to push button (for high temp alarm)


const byte ROWS = 2;   // Keypad rows
const byte COLS = 2;   // Keypad columns
char keys[ROWS][COLS] = {
  {'1', '2'},
  {'4', '5'}
};
byte rowPins[ROWS] = {4, 5};    // Pins connected to keypad rows (adjustable)
byte colPins[COLS] = {6, 7};    // Pins connected to keypad columns (adjustable)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char i=0;
bool flag=0;
String PassWord = "1111";
String ReadingPass = "";

Servo doorServo;                  // Create a servo object
  
// I2C LCD configuration (adjust I2C address if needed)
const int lcd_address = 0x27; // Replace with your LCD I2C address
LiquidCrystal_I2C lcd(lcd_address, 16, 2);  // Create I2C LiquidCrystal object //A4 ,A5
dht DHT; 

/*Function declaration*/
void openDoor(int direction);
float ReadTemp();
void turnOnFan();
void turnOffFan();
void turnOnAlarm();
void turnOffAlarm();
void Brightness();
void ReadingPassWord();
int checkPassword(String str) ;


void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);           // Initialize serial communication for debugging (optional)
  pinMode(IR1, INPUT);     // Set IR sensor pins as inputs
  pinMode(IR2, INPUT);
  doorServo.attach(Door);   // Attach servo motor to its control pin
  pinMode(Buzz1 , OUTPUT); // Set buzzer pins as outputs
 // pinMode(Buzz2 , OUTPUT);
  pinMode(GreenLed, OUTPUT); // Set LED pin as output

//  pinMode(TEMP_SENSOR, INPUT); // Set temperature sensor pin as input
  pinMode(LDR, INPUT);       // Set LDR pin as input
  pinMode(LED1, OUTPUT);     // Set LED pins as outputs
  pinMode(buttonPin, INPUT);

  lcd.init();                      // initialize the lcd  SDA->A4,SCL->A5 for I2C Communication
  lcd.backlight();

 if (digitalRead(IR1) == LOW) {
    
    openDoor(1); // Open door to the right
    delay(3000);
  } else if (digitalRead(IR2) == LOW)
  //detected 
  {
    openDoor(0); // Open door to the left
  }
  while(i<3){
     lcd.setCursor(0, 0);
       lcd.print("Enter the Pass");
       delay(2000);
       lcd.setCursor(0, 1);
       
       ReadingPassWord();
       
   if (checkPassword(ReadingPass) == 1) {
        //flag=1;
        lcd.setCursor(0, 0);
         lcd.print("Correct !     ");
         delay(2000);
         lcd.setCursor(0,1);
         lcd.print("Welcome Home!");
         delay(2000);
         lcd.clear();
         digitalWrite(GreenLed,HIGH);
         digitalWrite(RedLed,LOW);
         flag=1;
         break;
    }
    else
    {
      lcd.clear();
      lcd.print("Wrong          ");
      turnOnAlarm();
      delay(2000);
     turnOffAlarm();
     digitalWrite(RedLed,HIGH);
     digitalWrite(GreenLed,LOW);
     i++;
      }
}
   
}

void loop() {
   
 if (digitalRead(IR1) == LOW) {
    
    openDoor(1); // Open door to the right
    delay(2000);
  } else if (digitalRead(IR2) == LOW)
  //detected 
  {
    openDoor(0); // Open door to the left
  }
  
 if(flag==1){
     Brightness();
  // Temperature control and high temperature alarm based on password
 {
   // First Door control based on IR sensors
  
         lcd.setCursor(0, 0);
         float temp=ReadTemp();
         lcd.print("Temp:");
         lcd.print(temp);
         lcd.print("°C");
         delay(4000);
         //lcd.clear();
         lcd.setCursor(0, 1);

     if (temp > TempThreshold && temp < HighTempThreshold) {
        turnOnFan();
        lcd.print("Fan ON ");
       }
      else if (temp > HighTempThreshold) {
       turnOnAlarm();
       //try high temp
       lcd.print("HIGH TEMP! Press K ");
       delay(3000);
         lcd.print("                 ");
       while (digitalRead(buttonPin) == HIGH);                // Wait for button press to turn off alarm
       turnOffAlarm();
      } 
      else
      {
       lcd.print("Fan off");
       delay(3000);
       turnOffFan();
       lcd.print("          "); // Clear previous
       delay(1000);
      }
  }
      
  }

}


void openDoor(int direction) {
  int angle;
  if (direction) {
    angle = 0; // Open door to the right (adjust angle as needed) //suggest 0
  } else {
    angle = 180; // Open door to the left (adjust angle as needed)//check this suggest 180
  }
  doorServo.write(angle);  // Move servo to open position
  delay(2000);             // Hold door open for 2 seconds
  doorServo.write(90);       // Move servo back to closed position  //suggest  90
  delay(20);
}



// Function to turn on the fan
void turnOnFan() {
  digitalWrite(Fan, HIGH); // Set fan speed to maximum (adjust as needed)
}

// Function to turn off the fan
void turnOffFan() {
  digitalWrite(Fan, LOW); // Stop the fan
}

// Function to turn on the alarm buzzer (e.g., for wrong password)
void turnOnAlarm() {
  tone(Buzz1, 1000); // Play a tone at 1 kHz
}

// Function to turn on the alarm buzzer (e.g., for high temperature)

// Function to turn off the alarm buzzer (for high temperature)
void turnOffAlarm() {
  noTone(Buzz1);
}


void  Brightness(){

  int ldrValue = analogRead(LDR);
  int led1Brightness = map(ldrValue, 1023, 0, 255, 0); 
  lcd.setCursor(7, 1);
  analogWrite(LED1, led1Brightness);
  lcd.print("LED: ");
  lcd.print(led1Brightness);

  delay(3000);
}
  
  
float ReadTemp()
{ 
  float Read= DHT.read22(DHT_PIN);
  float Temp=DHT.temperature;
  return Temp;
}
  

void ReadingPassWord() {
  //lcd.clear();
  //lcd.print("Enter Password");
  //Serial.flush();
  String password = "";
  while (password.length() < 4) { // Read 4 characters
    char key = keypad.getKey();
    if (key != NO_KEY) 
     {
      password += key;
      lcd.setCursor(password.length(), 1); // Move the cursor to the right for each character
      lcd.print("*"); // Print an asterisk to mask the character
      delay(70);
      // lcd.print("*");
     }
  }
  ReadingPass = password;
}


int checkPassword(String str) {
  if (strcmp(str.c_str(), PassWord.c_str())==0) {
    return 1;
  } else {
    return 0;
  }
}
// Function to read temperature from different Temp sensor
/* float ReadTemperature() {
  float voltage = analogRead(TEMP_SENSOR) * 5.0 / 1023.0;
  float temp = (voltage - 0.5) * 100;   //converting from 10 mv per degree wit 500 mV offset TMP36 
  //try this also  int temp = analogRead(pinTemp);    //Read the analog pin
  //temp = temp * 0.48828125;   // convert output (mv) to readable celcius
  return temp;
} */
