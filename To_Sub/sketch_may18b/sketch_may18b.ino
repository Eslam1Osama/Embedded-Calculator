#include<LiquidCrystal_I2C.h>
#include<Keypad.h>
#include<string.h>

#define ROWS 4
#define COLS 4

char Keys[ROWS][COLS] = {
  {'7' , '8' , '9' , '/'},
  {'4' , '5' , '6' , '*'},
  {'1' , '2' , '3' , '-'},
  {'C' , '0' , '=' , '+'}  
};

//conncetion of rows of KeyPad
byte RowPins[ROWS] = {9 , 8 , 7 , 6};
//conncetion of columns of KeyPad
byte ColPins[COLS] = {5 , 4 , 3 , 2};

//create object from class Keypad
Keypad CustomKeypad = Keypad(makeKeymap(Keys) , RowPins , ColPins , ROWS , COLS);

//create object from class LiquidCrystal_I2C
/* 0X27-> the address which arduino is going to address 
   LCD through I2C communication protocole
   20-> number of columns in LCD
   4-> number of rows in LCD
*/
LiquidCrystal_I2C LCD(0X27 , 20 , 4);

/**********************************************/
      /*  Calculator  */
      /****************/
float var = 0.0 , Res = 0.0;

/* buffer with data type of char (string of characters) with size of BUFFER_SIZE */
#define BUFFER_SIZE 100
char buf[BUFFER_SIZE];

char operat;
bool Got_Var = false , Got_Sign = false , Got_1stVar = false;
int count = 0;
char custom_key;

void Get_Var(void)
{
  buf[count] = custom_key;
  LCD.setCursor(count++ , 0);
  Got_Var = true;
  Got_Sign = true;
  LCD.print(custom_key);
}
void Get_oper(void)
{
  buf[count] = '\0';
  var = atoi(buf);
  count = 0;
  
  
  if(!Got_1stVar) 
  {
    Got_1stVar = true;
    Res = var;
  }
  else{
  if(operat == '+')     Res += var;
  else if(operat == '-')  Res -= var;  
  else if(operat == '*')  Res *= var;
  else if(operat == '/')  Res /= var;}
  
  if(custom_key != '=')
  {
    LCD.setCursor(0, 1);
    LCD.print(custom_key);
    operat = custom_key;
    delay(500);
  }

  //clear LCD
  LCD.clear();
  LCD.setCursor(0, 0);
  Got_Var = false;
  Got_Sign = false;
}

/**********************************************/
void setup()
{
  //initialize serial monitor
  Serial.begin(9600);
  
  //initialize LCD
  LCD.init();
  
  //clear LCD
  LCD.clear();
  
  //turn on back light of LCD
  LCD.backlight();

  LCD.setCursor(4, 0);
  LCD.print("Welcome");
  LCD.setCursor(3, 1);
  LCD.print("To CulHub");
  delay(500);
  LCD.clear();
  
  
}

void loop()
{
  custom_key = CustomKeypad.getKey();
  if( ((custom_key >= '0') && (custom_key <= '9')) || ((!Got_Sign) && ((custom_key == '+') || (custom_key == '-'))) )
    Get_Var();
  
  else if( ((custom_key == '+') || (custom_key == '-') || (custom_key == '*') || (custom_key == '/')) && (Got_Var & Got_Sign) )
    Get_oper();

  else if( (custom_key == '=') && (Got_Var & Got_Sign & Got_1stVar) )
  {
    Get_oper();
    LCD.clear();
    String str = String(Res);
    LCD.setCursor(0, 0);
    LCD.print(str);
  }
    
  else if(custom_key == 'C') 
  {
    LCD.clear();
    LCD.setCursor(0, 0);
    var = 0 ; Res = 0;
    count = 0;
    Got_Var = false;
    Got_Sign = false;
    Got_1stVar = false;
  }
}
