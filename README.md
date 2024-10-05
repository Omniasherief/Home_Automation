
---

# 🌟 Home Automation System

Welcome to the **Home Automation Control Project**! This Arduino-based project brings a smart home experience with automatic doors, secure entry, temperature control, and more. Let’s dive into the features that will make your home a bit smarter! 

---

## 🚪 1. Automatic Door Control

- **How it Works:** Two IR sensors detect if someone is approaching from either side of the door.
- **Action:** The servo motor will open the door in the opposite direction when someone is detected.
- **Bonus:** No need to touch the door—fully automated!

---

## 🔐 2. Secure Keypad Entry with Red LED for Wrong Password

- **Enter your passcode** via a 4x4 keypad.
- **Wrong passcode?** No problem—you have 3 attempts. After a wrong attempt, the system will:
   - Trigger a **buzzer**.
   - Flash a **red LED**.
   - Show "Wrong password" on the **LCD display**.
- **Correct passcode?** You’re in! The system will:
   - Light up a **green LED**.
   - Display "Welcome Home" on the **LCD display**.

---

## 🌡️ 3. Temperature Control with Fan and Alarm

- **Temperature Monitoring:** The sensor continuously checks the room temperature.
- **Fan Activation:** If the temperature exceeds **25°C**, the fan will turn on automatically to cool down the room.
- **High-Temperature Alarm:** If the temperature goes above **35°C**, an alarm (buzzer) will sound, which can only be turned off with a **push button**.
- **LCD Updates:** The current temperature is always displayed on the LCD, so you’re always in the know!
  
---

## 💡 4. LDR-Based Light Control

- **Light Sensor:** The LDR controls the brightness of a connected LED based on ambient light.
- **Display:** The LCD also shows the current light intensity to give you real-time feedback.

---

## 🛠️ Hardware Required:

- Arduino Uno
- Servo Motor
- Two IR Sensors
- Keypad (4x4)
- Buzzer
- 16x2 LCD
- Temperature Sensor (DHT11 or DHT22)
- DC Motor
- Fan (connected to DC motor)
- Push Button
- Red & Green LEDs
- Resistors (check component datasheets for values)
- LDR (Light Dependent Resistor)

---

## 💻 Software Required:

- [Download the Arduino IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)

---

## 🚀 Getting Started:

1. **Wiring:** Refer to the datasheets for correct pin connections.
2. **Upload Code:** Open the Arduino IDE and upload the code to your Arduino board. Don’t forget to install any required libraries.
3. **Run the System:** Watch the magic happen as the system automates your home functions.

---

## 🎯 Future Enhancements:

- Add mobile app control using Bluetooth or Wi-Fi modules.
- Incorporate voice control using Alexa or Google Assistant.
- Extend the project to control lights and other home appliances remotely.

---
