
# 🌐 ESP8266 Web-Controlled LEDs and Buzzer

This project creates a **web-based control panel** to toggle multiple LEDs and a buzzer using the **ESP8266**. It supports both web control (via WiFi) and physical buttons for hardware toggling.

---

##  Overview
- Control **LEDs** and a **buzzer** using:
  - A simple web interface
  - Physical push buttons connected to the ESP8266
- Built-in debounce handling for physical buttons
- Real-time feedback via the web panel

---

##  Hardware Components
- **ESP8266 (NodeMCU)**
- 2 LEDs (connected to D1 and D2)
- 2 Push Buttons for LED control (connected to D5 and D6)
- 1 Buzzer (connected to D3)
- 1 Push Button for buzzer control (connected to D8)
- Resistors (for LEDs and buttons)
- Breadboard and jumper wires

---

##  Web Control Features
- Access the ESP8266’s IP address in your browser
- Click buttons to toggle LEDs and the buzzer:
  - **/toggleLED0** – Toggle LED 1
  - **/toggleLED1** – Toggle LED 2
  - **/toggleLED2** – Toggle the Buzzer
- Simple and responsive HTML control panel

---

##  Pin Configuration
| Device      | ESP8266 Pin |
|-------------|-------------|
| LED 1       | D1          |
| LED 2       | D2          |
| Button 1    | D5          |
| Button 2    | D6          |
| Button 3    | D7          |
| Buzzer      | D3          |
| Buzzer Btn  | D8          |

---

##  How It Works
- **WiFi Connection**: The ESP8266 connects to the specified SSID (`GESTURE`) and password.
- **Web Server**: Runs on port 80 and listens for button requests.
- **Web Interface**: Provides toggle buttons for LEDs and the buzzer.
- **Physical Buttons**: Allow manual toggling of LEDs and the buzzer.
- **Debounce Logic**: Prevents rapid multiple toggles from button presses.

---

##  Setup Instructions
1. **Wiring**:
   - Connect LEDs, buzzer, and buttons as per the pin configuration table.
   - Use pull-up resistors for button stability (if not using `INPUT_PULLUP`).

2. **Code Upload**:
   - Open the code in **Arduino IDE** or **PlatformIO**.
   - Select **NodeMCU 1.0 (ESP-12E Module)**.
   - Enter your WiFi credentials (`ssid` and `password`) in the code.
   - Upload to your ESP8266.

3. **Web Access**:
   - After connecting, open the serial monitor at **115200 baud**.
   - Note the ESP8266’s IP address.
   - Open the IP address in your browser (e.g., `http://192.168.x.x/`).

4. **Toggle Control**:
   - Use the web buttons to toggle the LEDs and buzzer.
   - Press physical buttons for local control.

---

##  Features
- Web-based control with immediate response.  
- Dual control: web and hardware.  
- Expandable for additional devices.  
- Built-in button debounce for reliable operation.  

---
