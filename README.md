# arduino-ds1307-digital-clock-with-date-and-time
A digital clock and calendar using Arduino Nano, DS1307 RTC, and 16x2 I2C LCD with 12-hour AM/PM format, date, and day display.

# Arduino Nano Digital Clock with DS1307 RTC

This project is a **digital clock and calendar** built using an **Arduino Nano**, **DS1307 RTC module**, and a **16×2 I²C LCD**.  
It displays the **time in 12-hour format with AM/PM**, as well as the **date and day of the week**.  
The clock also allows setting and adjusting time/date using push buttons.

---

## ✨ Features
- 12-hour clock format with **AM/PM**
- **Date and day of week** display
- **Blinking cursor effect** on the active field during setting mode
- Handles **month lengths** and **leap years**
- Three-button control system:
  - **Set Button** → Switch between edit fields (hour, minute, day, month, year)
  - **Up Button** → Increase value of the active field
  - **Down Button** → Decrease value of the active field
- Smooth display updates (no flickering)

---

## 🛠️ Hardware Required
- Arduino Nano (or Uno/Pro Mini)
- DS1307 RTC module (with CR2032 backup battery)
- 16×2 LCD with I²C interface
- Push buttons × 3
- 10kΩ resistors × 3 (for pull-downs if needed)
- Jumper wires and breadboard

---

## 📖 Circuit Diagram (Connections)

<img width="3000" height="2570" alt="circuit_image" src="https://github.com/user-attachments/assets/87f2a3ce-f957-4f26-9666-4e578f2dcbd5" />
 

---

## 💻 Libraries Used
Make sure to install these libraries in Arduino IDE:
- [RTClib](https://github.com/adafruit/RTClib)
  <img width="1335" height="679" alt="Screenshot 2025-09-13 155122" src="https://github.com/user-attachments/assets/e2e4fb38-2770-44b5-be51-7820a7ec0462" />

- [LiquidCrystal_I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)
  <img width="1009" height="575" alt="Screenshot 2025-09-14 113522" src="https://github.com/user-attachments/assets/871ef528-d58a-4c00-875d-2b938fb92663" />


---

## 🚀 How to Use
1. Upload the provided sketch to your Arduino Nano.
2. Connect the RTC and LCD as per the circuit table.
3. Use the three buttons:
   - **SET** → Select which field to edit (hour → minute → day → month → year).
   - **UP/DOWN** → Adjust the selected value.
4. Time/date will update in the DS1307 RTC automatically.

---

## 📷 Demo (Optional)
*(Add photos or GIFs of your working setup here)*

---

## 📂 Project Structure
