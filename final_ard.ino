#include <LiquidCrystal.h>
#include <string.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// initializing photosensor variable
int sensorValue = 0;  

//following code lays out the different characters for lcd screen
byte Ring1[]{
  B00000,
  B00011,
  B00100,
  B00100,
  B00100,
  B00100,
  B00011,
  B00000, 
};

byte Ring2[]{
  B00000,
  B10001,
  B01010,
  B01010,
  B01110,
  B11011,
  B10001,
  B10001, 
};

byte Ring3[]{
  B10001,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000, 
};

byte Ring4[]{
  B00000,
  B11000,
  B00100,
  B00100,
  B00100,
  B00100,
  B11000,
  B00000, 
};

byte Torch[]{
  B11111,
  B01110,
  B01110,
  B01110,
  B00100,
  B00100,
  B00100,
  B00000, 
};

byte Fire1[]{
  B00000,
  B00100,
  B01100,
  B11100,
  B11110,
  B11111,
  B11111,
  B01110, 
};

byte Fire2[]{
  B00000,
  B01100,
  B00100,
  B01101,
  B11101,
  B11111,
  B11111,
  B01110, 
};

byte Fire3[]{
  B00000,
  B00010,
  B00110,
  B10111,
  B11111,
  B11111,
  B11111,
  B01110, 
};

byte Tree1[]{
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B11111,
  B00100,
  B11111, 
};

byte Ground1[]{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
};

byte Ground2[]{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
};

byte Ground12[]{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00011,
  B11100,
};

byte Ground21[]{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B00111,
};

byte Tree2[]{
  B00100,
  B01110,
  B11111,
  B01110,
  B11111,
  B00100,
  B11111,
  B00000,
};

byte Person1[]{
  B00000,
  B01110,
  B00100,
  B01110,
  B11111,
  B01010,
  B11111,
  B11111,
};

byte Person2[]{
  B01110,
  B00100,
  B01110,
  B11111,
  B01010,
  B11111,
  B11111,
  B00000,
};

//following function prints ot bottom row on the screen
int landscapeRunner(int count, char chars[], char c[]){//num that shifts it over, bottom row (array acts like string, calls in the created chars)
  for(int i = 0; i<=39; i++){//prints out the chars array
      lcd.setCursor(i-count, 1);//will print them out one spot to the left every time function is run
      lcd.write(chars[i]);
    }
  lcd.setCursor(1,1);
  //following 2 if statements controls which kind of person gets printed based on landscape
  if(chars[2+count] == c[0] || chars[2+count] == c[1] || chars[2+count] == c[3]){
    lcd.write(c[6]);
  }
  else if(chars[2+count] == c[2] || chars[2+count] == c[5] || chars[2+count] == c[4]){
    lcd.write(c[7]);
  }
  return 0;
}

int wordRunner(String words, char byte[], char b[]){//runs the top line and calls the function for the bottom line
  int charnum = 0;
  for(int a = 0; a <= 24; a++){//prints out the string but moves the place back everytime it's run
    for(int b = 0; b <=39; b++){
      lcd.setCursor(b - a, 0);
      lcd.print(words.charAt(charnum));
      charnum ++;
    }
    landscapeRunner(a, byte, b);//calls bottom line function
    charnum = 0;
    delay(200);
  }
  return 0;
}

void setup() {
  lcd.begin(16, 2);//initializes lcd screen
  //following creates the characters
  lcd.createChar(0, Ring1);
  lcd.createChar(1, Ring2);
  lcd.createChar(2, Ring3);
  lcd.createChar(3, Ring4);
  lcd.createChar(4, Torch);
  lcd.createChar(5, Fire1);
  lcd.createChar(6, Fire2);
  lcd.createChar(7, Fire3);
  // Defines input and output pins as well as initializing the serial bus
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
}

void loop(){
  // setting LED state to off
  digitalWrite(7, LOW);
  
  // bases the sensor value off the current analog reading from the photoresitor 
  sensorValue = analogRead(A0); 
  
  // assigning the anolog readings to a variable
  //following prints original screen

  lcd.setCursor(0,1);
  lcd.write(byte(4));
  lcd.setCursor(1,0);
  lcd.write(byte(0));
  lcd.setCursor(2,0);
  lcd.write(byte(1));
  lcd.setCursor(2,1);
  lcd.write(byte(2));
  lcd.setCursor(3,0);
  lcd.write(byte(1));
  lcd.setCursor(3,1);
  lcd.write(byte(2));
  lcd.setCursor(4,0);
  lcd.write(byte(3));
  lcd.setCursor(5,1);
  lcd.write(byte(4));
  lcd.setCursor(7,0);
  lcd.print("Beijing");
  lcd.setCursor(9,1);
  lcd.print("2022");

  /* animates the flame until second stage is 
  triggered by shining a light on the torch */
   while(sensorValue > 700){
    sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    lcd.setCursor(0,0);
    lcd.write(byte(5));
    lcd.setCursor(5,0);
    lcd.write(byte(5));
    delay(200);
    lcd.setCursor(0,0);
    lcd.write(byte(6));
    lcd.setCursor(5,0);
    lcd.write(byte(6));
    delay(200);
    lcd.setCursor(0,0);
    lcd.write(byte(7));
    lcd.setCursor(5,0);
    lcd.write(byte(7));
    delay(200);
  } 
  
  //shining a light on the photoresistor causes second stage to start
  if(sensorValue > 800){
    // turns the torch on
    digitalWrite(7, HIGH); 
    //recreates characters for the second stage
    lcd.createChar(0, Tree1);
    lcd.createChar(1, Ground1);
    lcd.createChar(2, Ground2);
    lcd.createChar(3, Ground12);
    lcd.createChar(4, Ground21);
    lcd.createChar(5, Tree2);
    lcd.createChar(6, Person1);
    lcd.createChar(7, Person2);
    
    //welcome is the top row, bytes is the bottom row, and a are the created characters in an array so they can be called
    String welcome = "               Welcome to the 2022 Winter Olympics    Introducing: The Min Kao Wanders, The Little Pascals, Smokey's East TN Go Vols Bobsleigh/sled Biatholon ShootnSki Adventure Appreciation Squad, Team Cool Runnings, TwoBD, Baby Rockets, Work in Progress                  ";
    char a[] = {byte(0), byte(1), byte(2), byte(3), byte(4), byte(5), byte(6), byte(7)};
    char bytes[] = {byte(1), byte(1),byte(0),byte(1),byte(3),byte(2),byte(2),byte(5),byte(2),byte(4),byte(1),byte(1),byte(1),byte(1),byte(3),byte(2),byte(2),byte(5),byte(2),byte(4),byte(1),byte(1),byte(0),byte(1),byte(3),byte(2),byte(2),byte(5),byte(2),byte(4),byte(1),byte(1),byte(1),byte(1),byte(3),byte(2),byte(2),byte(5),byte(2), byte(4)};
    
    //will keep running the printing functions until the entire top row has been read
    while(welcome.length()>=39){
    wordRunner(welcome, bytes, a);
    welcome = welcome.substring(24,welcome.length());
    }

    //recreates the characters for the firstm original stage and clears out the second stage
    lcd.createChar(0, Ring1);
    lcd.createChar(1, Ring2);
    lcd.createChar(2, Ring3);
    lcd.createChar(3, Ring4);
    lcd.createChar(4, Torch);
    lcd.createChar(5, Fire1);
    lcd.createChar(6, Fire2);
    lcd.createChar(7, Fire3);
    lcd.clear();
    // turns torch off
    digitalWrite(7, LOW);
    
  }
  
}