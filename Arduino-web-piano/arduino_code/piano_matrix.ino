// Keypad rows x 7 OUTPUT
int K_ROW_A = 0; 
int K_ROW_B = 1;   
int K_ROW_C = 2; 
int K_ROW_D = 3;   
int K_ROW_E = 4; 
int K_ROW_F = 5;  
int K_ROW_G = 6;   

// Keypad cols x 6 INPUT
int K_COL_A = 13; 
int K_COL_B = 12;   
int K_COL_C = 11; 
int K_COL_D = 10;   
int K_COL_E = 9; 
int K_COL_F = 8;  


int JOY_X = A0;
int JOY_Y = A1;
int KNOB_1 = A2;
int SLIDE_1 = A3;
int SLIDE_2 = A4;
int SLIDE_3 = A5; 


int joy_x_val = 0;
int joy_y_val = 0;
int knob_1_val = 0;
int slide_1_value = 0;
int slide_2_value = 0;
int slide_3_value = 0;


struct DATARAW
{
  byte b0: 1;
  byte b1: 1;
  byte b2: 1;
  byte b3: 1;
};

union DATA
{
  DATARAW set;
  byte value;
};


DATA oct_0a;
DATA oct_0b;
DATA oct_0c;

DATA oct_1a;
DATA oct_1b;
DATA oct_1c;

DATA oct_2a;
DATA oct_2b;
DATA oct_2c;

DATA swi_0a;
DATA swi_0b;

void setup() {
  
  Serial.begin(115200);
 
  pinMode(K_ROW_A, OUTPUT);
  pinMode(K_ROW_B, OUTPUT);
  pinMode(K_ROW_C, OUTPUT);
  pinMode(K_ROW_D, OUTPUT);
  pinMode(K_ROW_E, OUTPUT);
  pinMode(K_ROW_F, OUTPUT);
  pinMode(K_ROW_G, OUTPUT);

  pinMode(K_COL_A, INPUT_PULLUP);
  pinMode(K_COL_B, INPUT_PULLUP);
  pinMode(K_COL_C, INPUT_PULLUP);
  pinMode(K_COL_D, INPUT_PULLUP);
  pinMode(K_COL_E, INPUT_PULLUP);
  pinMode(K_COL_F, INPUT_PULLUP);
  
  digitalWrite(K_ROW_A, HIGH);
  digitalWrite(K_ROW_B, HIGH);
  digitalWrite(K_ROW_C, HIGH);
  digitalWrite(K_ROW_D, HIGH);
  digitalWrite(K_ROW_E, HIGH);
  digitalWrite(K_ROW_F, HIGH);
  digitalWrite(K_ROW_G, HIGH);
}

String getkeys(){

  String octave0, octave1, octave2;
  String switches;
  
  // Scan 1st row
  digitalWrite(K_ROW_G, HIGH);
  digitalWrite(K_ROW_A, LOW);
  oct_0a.set.b3 = digitalRead(K_COL_A);
  oct_0a.set.b2 = digitalRead(K_COL_B);
  oct_0a.set.b1 = digitalRead(K_COL_C);
  oct_0a.set.b0 = digitalRead(K_COL_D);
  oct_0b.set.b3 = digitalRead(K_COL_E);
  oct_0b.set.b2 = digitalRead(K_COL_F);

  // Scan 2nd row
  digitalWrite(K_ROW_A, HIGH);
  digitalWrite(K_ROW_B, LOW);
  oct_0b.set.b1 = digitalRead(K_COL_A);
  oct_0b.set.b0 = digitalRead(K_COL_B);
  oct_0c.set.b3 = digitalRead(K_COL_C);
  oct_0c.set.b2 = digitalRead(K_COL_D);
  oct_0c.set.b1 = digitalRead(K_COL_E);
  oct_0c.set.b0 = digitalRead(K_COL_F);

  // Scan 3rd row
  digitalWrite(K_ROW_B, HIGH);
  digitalWrite(K_ROW_C, LOW);
  oct_1a.set.b3 = digitalRead(K_COL_A);
  oct_1a.set.b2 = digitalRead(K_COL_B);
  oct_1a.set.b1 = digitalRead(K_COL_C);
  oct_1a.set.b0 = digitalRead(K_COL_D);
  oct_1b.set.b3 = digitalRead(K_COL_E);
  oct_1b.set.b2 = digitalRead(K_COL_F);

  // Scan 4th row
  digitalWrite(K_ROW_C, HIGH);
  delay(2);
  digitalWrite(K_ROW_D, LOW);
  oct_1b.set.b1 = digitalRead(K_COL_A);
  oct_1b.set.b0 = digitalRead(K_COL_B);
  oct_1c.set.b3 = digitalRead(K_COL_C);
  oct_1c.set.b2 = digitalRead(K_COL_D);
  oct_1c.set.b1 = digitalRead(K_COL_E);
  oct_1c.set.b0 = digitalRead(K_COL_F);

  // Scan 5th row
  digitalWrite(K_ROW_D, HIGH);
  delay(2);
  digitalWrite(K_ROW_E, LOW);  
  oct_2a.set.b3 = digitalRead(K_COL_A);
  oct_2a.set.b2 = digitalRead(K_COL_B);
  oct_2a.set.b1 = digitalRead(K_COL_C);
  oct_2a.set.b0 = digitalRead(K_COL_D);
  oct_2b.set.b3 = digitalRead(K_COL_E);
  oct_2b.set.b2 = digitalRead(K_COL_F);

  // Scan 6th row
  digitalWrite(K_ROW_E, HIGH);
  delay(2);
  digitalWrite(K_ROW_F, LOW);
  oct_2b.set.b1 = digitalRead(K_COL_A);
  oct_2b.set.b0 = digitalRead(K_COL_B);
  oct_2c.set.b3 = digitalRead(K_COL_C);
  oct_2c.set.b2 = digitalRead(K_COL_D);
  oct_2c.set.b1 = digitalRead(K_COL_E);
  oct_2c.set.b0 = digitalRead(K_COL_F);

  // Scan 7th row
  digitalWrite(K_ROW_F, HIGH);
  delay(2);
  digitalWrite(K_ROW_G, LOW);
  swi_0a.set.b3 = digitalRead(K_COL_A);
  swi_0a.set.b2 = digitalRead(K_COL_B);
  swi_0a.set.b1 = digitalRead(K_COL_C);
  swi_0a.set.b0 = digitalRead(K_COL_D);
  swi_0b.set.b3 = digitalRead(K_COL_E);
  swi_0b.set.b2 = digitalRead(K_COL_F);
  swi_0b.set.b1 = 1;
  swi_0b.set.b0 = 1;
  
  octave0 = String(oct_0a.value, HEX)+String(oct_0b.value, HEX)+String(oct_0c.value, HEX);
  octave1 = String(oct_1a.value, HEX)+String(oct_1b.value, HEX)+String(oct_1c.value, HEX);
  octave2 = String(oct_2a.value, HEX)+String(oct_2b.value, HEX)+String(oct_2c.value, HEX);
  switches = String(swi_0a.value, HEX)+String(swi_0b.value, HEX);

  return octave0+octave1+octave2+switches;

}

String getanalog(){
  char analog_values[12] = {0};
  joy_x_val = analogRead(JOY_X)/4;
  joy_y_val = analogRead(JOY_Y)/4;
  knob_1_val = analogRead(KNOB_1)/4;
  slide_1_value = analogRead(SLIDE_1)/4;
  slide_2_value = analogRead(SLIDE_2)/4;
  slide_3_value = analogRead(SLIDE_3)/4; 
  sprintf(analog_values, "%02x%02x%02x%02x%02x%02x",joy_x_val,joy_y_val,knob_1_val,slide_1_value,slide_2_value,slide_3_value);
  return analog_values;
}

void loop() {
  Serial.println(getkeys()+getanalog());
  delay(50);
}
