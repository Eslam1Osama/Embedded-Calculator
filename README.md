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
