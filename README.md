# Arduino Calculator (LCD + Keypad)

## 📖 Overview
This project is a **simple calculator** built with an Arduino board, a **4x4 keypad**, and a **20x4 I2C LCD display**.  
It supports the **basic arithmetic operations** (`+`, `-`, `*`, `/`), displays results on the LCD, and allows resetting with the `C` key.

---

## 🛠️ Hardware Requirements
- Arduino UNO / Mega / Nano (or compatible board)  
- 4x4 Matrix Keypad  
- 20x4 I2C LCD Display (address: `0x27`)  
- Jumper wires  
- Breadboard  

---

## 🔌 Pin Connections

### Keypad
| Keypad Pin | Arduino Pin |
|------------|-------------|
| R1         | 9 |
| R2         | 8 |
| R3         | 7 |
| R4         | 6 |
| C1         | 5 |
| C2         | 4 |
| C3         | 3 |
| C4         | 2 |

### LCD (via I2C Module)
- SDA → A4  
- SCL → A5  
- VCC → 5V  
- GND → GND  

---

## 📂 Project Structure
Arduino-Calculator/
│── Calculator.ino # Main Arduino code
│── README.md # Documentation


---

## ▶️ How to Use
1. Connect all components according to the wiring table above.  
2. Open the project in **Arduino IDE**.  
3. Install the required libraries (see below).  
4. Upload the code to your Arduino.  
5. Use the **keypad** to enter numbers and operators:  
   - `0–9` → digits  
   - `+ - * /` → operators  
   - `=` → compute result  
   - `C` → clear/reset calculator  

---

## 📦 Required Libraries
Make sure the following libraries are installed in Arduino IDE:  
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)  
- [Keypad](https://playground.arduino.cc/code/keypad/)  

---

## 🧮 Features
- ✅ Multi-digit number input  
- ✅ Decimal results (e.g., `5 / 2 = 2.5`)  
- ✅ Division by zero protection (`Error: Div/0`)  
- ✅ Clear/reset with `C`  
- ✅ Supports continuous chained operations  

---

## ⚠️ Edge Cases Handled
- Prevents **division by zero**  
- Ignores multiple operators pressed in sequence  
- Input buffer protected (no memory overflow)  
- Operator ignored if pressed before entering a number  

---

## 📸 Example Output


Input: 12 + 8 =
LCD: 20

Input: 5 / 0 =
LCD: Error: Div/0


---

## 📜 License
This project is open-source and available under the **MIT License**.  
Feel free to modify and improve it for your own projects!
