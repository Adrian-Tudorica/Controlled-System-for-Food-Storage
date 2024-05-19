# Controlled-System-for-Food-Storage

1.	Describing the project:

This is a personal project that designs a Controlled System designed for food storage, ensuring optimal conditions for fruits, vegetables, and dairy by monitoring and controlling temperature and humidity.

2.	Operating mode:

Automatically, the system uses a sensor, to measure the temperature and humidity levels. 
When the temperature rises over 25*C, the alarm rings for a specified duration, a red LED turns on, the system turns the AC ON for a set period of time and displays the temperature and timer on the LCD, after wich it measures the temperature again. If the temperature didn’t drop below 25*C, the AC will stay ON for another set period of time. If the temperature drops below 25*C, the LCD displays that the AC is OFF, the system turns off the red LED and turns on a green LED to display that the temperature is optimal.
When the humidity exceedes 70% (while the temperature is under 25*C -  For this project, it was determined that the temperature has a higher degree of importance than humidity), the alarm rings for a specified duration, a red LED turns on, the system opens a window for a set period of time and displays the humidity and timer on the LCD, after wich it measures the humidity again. If the percentage didn’t drop below 70, the window will stay open for another set period of time. If the humidity drops below 70%, the LCD displays that the window is closing, the system turns off the red LED and turns on a green LED to display that the temperature is optimal.
If there is a problem with the temperature and humidity sensor, the systems turns on a blue LED to indicate that there is a problem with the DHT 11 sensor, the LCD displays „Sensor Error” and the alarm will ring for 24 hours.

3.	The system is made of:

-	1 x Arduino Uno R3 programmable circuit board
-	1 x DHT 11 sensor to measure the parameters
-	1 x Passive Buzzer to simulate the alarm
-	1 x Resistor (1k Ohm) the Buzzer was too loud while experimenting
-	1 x LCD to display the necesary information
-	1 x Stepper Motor (28BYJ-48) to simulate the air conditioner
-	1 x Driver for Stepper Motor (ULN2003) 
-	1 x Micro Servomotor (SG90) to simulate opening/closing the window
-	1 x RGB Module (KY-016) to display the state of the system with LEDs
-	1 x Breadboard


4.	Electrical circuit wiring diagram
 
![image](https://github.com/Adrian-Tudorica/Controlled-System-for-Food-Storage/assets/164034888/c295d9e9-0de3-4d25-9b9a-9ef2d025b6b2)

System running Optimally (Temperature = 22.70*C & Humidity = 57%)
![WhatsApp Image 2024-05-19 at 18 48 52_4b1eb871](https://github.com/Adrian-Tudorica/Controlled-System-for-Food-Storage/assets/164034888/091f196a-7678-4ca2-ac7d-eba8c3a59e8f)

System running while AC is ON (Temperature > 25*C)
![WhatsApp Image 2024-05-19 at 18 48 52_7dff77a1](https://github.com/Adrian-Tudorica/Controlled-System-for-Food-Storage/assets/164034888/643a9ed7-930e-448f-a551-807540f07bb2)

System running while the window is open (Humidity > 70% && Temperature < 25*C)
![WhatsApp Image 2024-05-19 at 18 48 52_eb827dd9](https://github.com/Adrian-Tudorica/Controlled-System-for-Food-Storage/assets/164034888/064cfa21-4fbe-4683-83d3-882cc37ebc1b)
