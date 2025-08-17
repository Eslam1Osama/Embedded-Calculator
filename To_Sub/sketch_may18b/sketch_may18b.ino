#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string.h>

#define ROWS 4
#define COLS 4

char Keys[ROWS][COLS] = {
  {'7' , '8' , '9' , '/'},
  {'4' , '5' , '6' , '*'},
  {'1' , '2' , '3' , '-'},
  {'C' , '0' , '=' , '+'}  
};

byte RowPins[ROWS] = {9 , 8 , 7 , 6};
byte ColPins[COLS] = {5 , 4 , 3 , 2};

Keypad CustomKeypad = Keypad(makeKeymap(Keys), RowPins, ColPins, ROWS, COLS);
LiquidCrystal_I2C LCD(0x27, 20, 4);

#define BUFFER_SIZE 100
char buf[BUFFER_SIZE];
int count = 0;

float var = 0.0, Res = 0.0;
char operat;
bool Got_Var = false, Got_Sign = false, Got_1stVar = false;
char custom_key;

// ✅ safe buffer append
void addToBuffer(char c) {
  if (count < BUFFER_SIZE - 1) {
    buf[count++] = c;
    buf[count] = '\0'; // keep string terminated
  }
}

void Get_Var(void) {
  addToBuffer(custom_key);
  LCD.print(custom_key);
  Got_Var = true;
  Got_Sign = true;
}

void Get_oper(void) {
  buf[count] = '\0';
  var = atof(buf); // ✅ support decimals
  count = 0;

  if (!Got_1stVar) {
    Got_1stVar = true;
    Res = var;
  } else {
    if (operat == '+')      Res += var;
    else if (operat == '-') Res -= var;  
    else if (operat == '*') Res *= var;
    else if (operat == '/') {
      if (var == 0) { // ✅ prevent division by zero
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Error: Div/0");
        delay(2000);
        Res = 0;
        Got_1stVar = false;
        LCD.clear();
        return;
      }
      Res /= var;
    }
  }

  if (custom_key != '=') {
    operat = custom_key;
    LCD.setCursor(0, 1);
    LCD.print(operat);
    delay(300);
  }

  LCD.clear();
  LCD.setCursor(0, 0);
  Got_Var = false;
  Got_Sign = false;
}

void resetCalc() {
  LCD.clear();
  LCD.setCursor(0, 0);
  var = 0; Res = 0;
  count = 0;
  Got_Var = false;
  Got_Sign = false;
  Got_1stVar = false;
}

void setup() {
  Serial.begin(9600);
  LCD.init();
  LCD.backlight();

  LCD.setCursor(4, 0);
  LCD.print("Welcome");
  LCD.setCursor(3, 1);
  LCD.print("To CulHub");
  delay(1000);
  LCD.clear();
}

void loop() {
  custom_key = CustomKeypad.getKey();
  if (!custom_key) return; // ✅ ignore if no key pressed

  if ((custom_key >= '0' && custom_key <= '9')) {
    Get_Var();
  }
  else if ((custom_key == '+' || custom_key == '-' || custom_key == '*' || custom_key == '/')
           && Got_Var && Got_Sign) {
    Get_oper();
  }
  else if (custom_key == '=' && Got_Var && Got_Sign && Got_1stVar) {
    Get_oper();
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(Res, 4); // ✅ show up to 4 decimals
  }
  else if (custom_key == 'C') {
    resetCalc();
  }
}
