#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Stepper.h>
#include <Servo.h>

// Define the DHT11 pin and type
#define DHTPIN 2
#define DHTTYPE DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 4, 5, 3, 6);

// Define LED pins
#define Led_Red 9
#define Led_Green 10
#define Led_Blue 11

// Define Alarm pin
#define buzzerPin 8

// Initialize Servo Motor
Servo myservo;
int pos = 0; // Store the servo position

void setup() {
  // Start the serial communication for debugging purposes
  Serial.begin(9600);
  
  // Initialize the DHT sensor
  dht.begin();
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Initialize LED pins
  pinMode (Led_Red, OUTPUT); 
  pinMode (Led_Green, OUTPUT);
  pinMode (Led_Blue, OUTPUT); 

  // Initialize the BUZZ-er (alarm)
  pinMode(buzzerPin, OUTPUT);

  // Ring the BUZZ-er when the system starts
  tone(buzzerPin, 1000, 500);
  
  // Initialize Servo pin
  myservo.attach(7);
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Start with Green LED on
  digitalWrite (Led_Green, 10); //set a lower LED intensity 

  // Read humidity and temperature from DHT11
  int h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");

    // Display the results on the LCD    
    lcd.clear();

    lcd.setCursor(0, 0); // First line
    lcd.print("Sensor Error");

    // Run Alarm for 24 hours
    tone(buzzerPin, 1000, 86400000)

    // Turn on blue LED to indicate sensor error
    digitalWrite (Led_Red, LOW);
    digitalWrite (Led_Green, LOW);
    digitalWrite (Led_Blue, 10);

    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
  
  // Display the results on the LCD
  lcd.clear();

  lcd.setCursor(0, 0); // First line
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" *C");
  
  lcd.setCursor(0, 1); // Second line
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  if (t > 25) { // temperature exceeded 25*C (condition imposed for simulation)
    // Turn on red LED
    digitalWrite (Led_Red, 10);
    digitalWrite (Led_Green, LOW);
    digitalWrite (Led_Blue, LOW);

    // Run Alarm for 5 seconds
    tone(buzzerPin, 1000, 5000);
  
    // Initialize timer 1 for temperature control (60 seconds)
    int timer1t = 60;

    while (timer1t != 0) {
      // Turn AC ON for ~ 1 minute (simulated with a 28BYJ-48-5VDC Step Motor)
      myStepper.setSpeed(10);
      myStepper.step(stepsPerRevolution);
      timer1t -= 5; 

      // Display the results on the LCD
      lcd.clear();

      lcd.setCursor(0, 0); // First line
      lcd.print("Temp=");
      lcd.print(t);
      lcd.print(">25*C");

      lcd.setCursor(0, 1); // Second line
      lcd.print("AC-ON (");
      lcd.print(timer1t);
      lcd.print("s)left");
    }

    // Wait 2 seconds
    delay(2000); 
    t = dht.readTemperature();

    // Display the results on the LCD
    lcd.clear();
    lcd.setCursor(0, 0); // First line
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" *C");

    // Run AC again if temperature didn't drop enough
    if (t > 25) {
      lcd.clear();

      lcd.setCursor(0, 0); // First line
      lcd.print("Temp: ");
      lcd.print(t);
      lcd.print(" *C");   

      lcd.setCursor(0, 1); // Second line
      lcd.print("AC - ON +1 min"); 

      timer1t = 60;
    } else {
      // Display the results on the LCD
      lcd.clear();

      lcd.setCursor(0, 0); // First line
      lcd.print("Temp: ");
      lcd.print(t);
      lcd.print(" *C"); 

      lcd.setCursor(0, 1); // Second line
      lcd.print("AC - OFF");

      delay(3000); // Keep "AC - OFF" more time on screen in order to be seen
    }
  } else {
    // Turn on green LED (temperature dropped below 25*C)
    digitalWrite (Led_Red, LOW);
    digitalWrite (Led_Green, 10);
    digitalWrite (Led_Blue, LOW);
  } 

  if (h>70 && t<25) { // humidity exceeded 70% and temperature under 25*c 
    // (for this experiment we don't want to open the window if the temperature is over 25*c)
    // (imposed: the temperature has a higher grade of importance than humidity)
    delay(1000);

    // Run alarm for 5 seconds
    tone(buzzerPin, 1000, 5000);

    // Turn on red LED
    digitalWrite (Led_Red, 10);
    digitalWrite (Led_Green, LOW);
    digitalWrite (Led_Blue, LOW);

    // Initialize timer 2 for humidity control (60 seconds)
    int timer2h = 60;

    while (timer2h != 0) {
      // Open the window for ~ 1 minute (simulated with a Micro Servo SG90)
      if (pos == 0) { // Will run the "for" just 1 time
                      // after that will just keep the window open if needed
        for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 90 degrees (open window)
          myservo.write(pos);                 // tell servo to go to position in variable 'pos'
          delay(25);                          // waits 25ms for the servo to reach the position
        }   
      }
   
      timer2h -= 5; 

      // Display the results on the LCD
      lcd.clear();

      lcd.setCursor(0, 0); // First line
      lcd.print("Humidity=");
      lcd.print(h);
      lcd.print("%>70%");

      lcd.setCursor(0, 1); // Second line
      lcd.print("Open Window ");
      lcd.print(timer2h);
      lcd.print("s");

      delay(5000);
    } 

    // Wait 2 seconds
    delay(2000); 

    h = dht.readHumidity();

    // Display the results on the LCD
    lcd.clear();

    lcd.setCursor(0, 0); // First line
    lcd.print("Humidity=");
    lcd.print(h);
    lcd.print("%>70%");  

    // Open Window again if humidity didn't drop enough
    if (h > 70) {
      lcd.clear();

      lcd.setCursor(0, 0); // First line
      lcd.print("Humidity=");
      lcd.print(h);
      lcd.print("%>70%");  

      lcd.setCursor(0, 1); // Second line
      lcd.print("Open Wndw +1 min"); 

      timer2h = 60;
  
    } else {
      // Display the results on the LCD
      lcd.clear();

      lcd.setCursor(0, 0); // First line
      lcd.print("Humidity=");
      lcd.print(h);
      lcd.print("%>70%"); 

      lcd.setCursor(0, 1); // Second line
      lcd.print("Closing Window");

      if (pos = 90) { // Will run the "for" just 1 time
        for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees (closed window)
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
      }

      delay(3000); // Keep "Closing Window" more time on screen in order to be seen
    }
  } else {
    // Turn on green LED (humidity dropped below 70%)
    digitalWrite (Led_Red, LOW);
    digitalWrite (Led_Green, 10);
    digitalWrite (Led_Blue, LOW);
  }
}