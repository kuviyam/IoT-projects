#include "MIDIUSB.h"

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

String allKeys = "";


int rec_but_val = 0;
int oct_sel1_val = 0;
int oct_sel2_val = 0;

int joy_x_val = 0;
int joy_y_val = 0;
int knob_1_val = 0;
int slide_1_value = 0;
int slide_2_value = 0;
int slide_3_value = 0;

int offset = 36;

int keyState[48];


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

String getkeys() {

  String octave0, octave1, octave2, switches;


  // Scan 1st row
  digitalWrite(K_ROW_G, HIGH);
  digitalWrite(K_ROW_A, LOW);
  octave0 = String(digitalRead(K_COL_A));
  octave0 = octave0 + String(digitalRead(K_COL_B));
  octave0 = octave0 + String(digitalRead(K_COL_C));
  octave0 = octave0 + String(digitalRead(K_COL_D));
  octave0 = octave0 + String(digitalRead(K_COL_E));
  octave0 = octave0 + String(digitalRead(K_COL_F));

  // Scan 2nd row
  digitalWrite(K_ROW_A, HIGH);
  digitalWrite(K_ROW_B, LOW);
  octave0 = octave0 + String(digitalRead(K_COL_A));
  octave0 = octave0 + String(digitalRead(K_COL_B));
  octave0 = octave0 + String(digitalRead(K_COL_C));
  octave0 = octave0 + String(digitalRead(K_COL_D));
  octave0 = octave0 + String(digitalRead(K_COL_E));
  octave0 = octave0 + String(digitalRead(K_COL_F));

  // Scan 3rd row
  digitalWrite(K_ROW_B, HIGH);
  digitalWrite(K_ROW_C, LOW);
  octave1 = digitalRead(K_COL_A);
  octave1 = octave1 + String(digitalRead(K_COL_B));
  octave1 = octave1 + String(digitalRead(K_COL_C));
  octave1 = octave1 + String(digitalRead(K_COL_D));
  octave1 = octave1 + String(digitalRead(K_COL_E));
  octave1 = octave1 + String(digitalRead(K_COL_F));

  // Scan 4th row
  digitalWrite(K_ROW_C, HIGH);
  delay(2);
  digitalWrite(K_ROW_D, LOW);
  octave1 = octave1 + String(digitalRead(K_COL_A));
  octave1 = octave1 + String(digitalRead(K_COL_B));
  octave1 = octave1 + String(digitalRead(K_COL_C));
  octave1 = octave1 + String(digitalRead(K_COL_D));
  octave1 = octave1 + String(digitalRead(K_COL_E));
  octave1 = octave1 + String(digitalRead(K_COL_F));

  // Scan 5th row
  digitalWrite(K_ROW_D, HIGH);
  delay(2);
  digitalWrite(K_ROW_E, LOW);
  octave2 = String(digitalRead(K_COL_A));
  octave2 = octave2 + String(digitalRead(K_COL_B));
  octave2 = octave2 + String(digitalRead(K_COL_C));
  octave2 = octave2 + String(digitalRead(K_COL_D));
  octave2 = octave2 + String(digitalRead(K_COL_E));
  octave2 = octave2 + String(digitalRead(K_COL_F));

  // Scan 6th row
  digitalWrite(K_ROW_E, HIGH);
  delay(2);
  digitalWrite(K_ROW_F, LOW);
  octave2 = octave2 + String(digitalRead(K_COL_A));
  octave2 = octave2 + String(digitalRead(K_COL_B));
  octave2 = octave2 + String(digitalRead(K_COL_C));
  octave2 = octave2 + String(digitalRead(K_COL_D));
  octave2 = octave2 + String(digitalRead(K_COL_E));
  octave2 = octave2 + String(digitalRead(K_COL_F));

  // Scan 7th row
  digitalWrite(K_ROW_F, HIGH);
  delay(2);
  digitalWrite(K_ROW_G, LOW);
  switches = String(digitalRead(K_COL_A));
  switches = switches + String(digitalRead(K_COL_B));
  switches = switches + String(digitalRead(K_COL_C));
  switches = switches + String(digitalRead(K_COL_D));
  switches = switches + String(digitalRead(K_COL_E));
  switches = switches + String(digitalRead(K_COL_F));



  return octave0 + octave1 + octave2 + switches;

}


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


void loop() {
  allKeys = getkeys();

  rec_but_val = allKeys[36];
  oct_sel1_val = allKeys[37];
  oct_sel2_val = allKeys[38];

  if (oct_sel1_val == '0') {
    offset = 36;
  }
  if (oct_sel2_val == '0') {
    offset = 48;
  }


  for (int i = 0; i < 36; i++) {
    if(allKeys[i] == '0' && keyState[i]!='1') {
      noteOn(0, offset + i, 64);
      MidiUSB.flush();
      keyState[i] = '1';
      Serial.print("Key Pressed");
    }
    else if(allKeys[i] == '1' && keyState[i]=='1'){
      noteOff(0, offset + i, 64);
      MidiUSB.flush();
      keyState[i] = '0';
    }
  }
}
