# Home  Automation

# Control Project:

This README file outlines an Arduino-based home automation system offering the following functionalities:

**1. Automatic Door Control:**

- Two IR sensors detect presence on either side of the door.

- Upon detecting someone approaching, the servo motor opens the door in the opposite direction.


**2. Secure Keypad Entry with Red LED for Wrong Password:**

- Keypad allows entering a password for access.

- Incorrect password triggers a buzzer and displays "Wrong password" on the LCD, along with a red LED indication.
 You are granted three attempts to enter the correct password.

- Correct password turns on a green LED and displays "Welcome Home" on the LCD.


**3. Temperature Control with Fan and Alarm:**

- Temperature sensor monitors the environment.

- If the temperature exceeds a threshold (e.g., 25°C), a DC motor activates a fan to cool down.

- If the temperature surpasses a higher threshold (e.g., 35°C), an alarm sounds (using the buzzer). This alarm can only be deactivated manually 
 with a push button .

- The LCD displays the current temperature in all scenarios.

- LDR controls Light of led, LCD displays intensity of light
# Hardware Required:

- Arduino Uno

- Servo motor


- Two IR sensors

- Keypad (4x4 or similar)

- Buzzer

- LCD display (16x2 or similar)

- Temperature sensor (e.g., DHT11)

- DC motor

- Fan (connected to DC motor)

- Push button 

- Red LED

- Resistors (values depend on specific components)

- LDR
# Software Required:

-Arduino IDE

**Getting Started:**

 - Refer to the datasheets of your specific components for proper connection details.


 - Download and install the Arduino IDE from https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE.

 - Upload the provided code  to your Arduino board.


