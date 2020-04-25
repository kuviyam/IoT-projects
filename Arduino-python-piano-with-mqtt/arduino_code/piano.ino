struct DATARAW
{
  byte b0: 1;
  byte b1: 1;
  byte b2: 1;
  byte b3: 1;
};

union DATA
{
  DATARAW rawdata;
  byte value;
};

DATA data0;

DATA data1;
DATA data2;
DATA data3;
DATA data4;
DATA data5;
DATA data6;

DATA data7;
DATA data8;
DATA data9;
DATA data10;
DATA data11;
DATA data12;

String zero;

String one;
String two;
String three;

String four;
String five;
String six;

void setup() {
  Serial.begin(115200);

  pinMode(40, INPUT_PULLUP); // octave select
  
  pinMode(38, INPUT_PULLUP); // a3
  pinMode(37, INPUT_PULLUP); // a3#
  pinMode(36, INPUT_PULLUP); // b3

  pinMode(33, INPUT_PULLUP); // c4
  pinMode(32, INPUT_PULLUP); // c4#
  pinMode(31, INPUT_PULLUP); // d4
  pinMode(30, INPUT_PULLUP); // d4#
  pinMode(29, INPUT_PULLUP); // e4
  pinMode(28, INPUT_PULLUP); // f4
  pinMode(27, INPUT_PULLUP); // f4#
  pinMode(26, INPUT_PULLUP); // g4
  pinMode(25, INPUT_PULLUP); // g4#
  pinMode(24, INPUT_PULLUP); // a4
  pinMode(23, INPUT_PULLUP); // a4#
  pinMode(22, INPUT_PULLUP); // b4

  pinMode(2, INPUT_PULLUP); // c5
  pinMode(3, INPUT_PULLUP); // c5#
  pinMode(4, INPUT_PULLUP); // d5
  pinMode(5, INPUT_PULLUP); // d5#
  pinMode(6, INPUT_PULLUP); // e5
  pinMode(7, INPUT_PULLUP); // f5
  pinMode(8, INPUT_PULLUP); // f5#
  pinMode(9, INPUT_PULLUP); // g5
  pinMode(10, INPUT_PULLUP); // g5#
  pinMode(11, INPUT_PULLUP); // a5
  pinMode(12, INPUT_PULLUP); // a5#
  pinMode(13, INPUT_PULLUP); // b5
}


void loop() {
  
  data0.rawdata.b0 = digitalRead(40);
  
  data0.rawdata.b1 = digitalRead(38);
  data0.rawdata.b2 = digitalRead(37);
  data0.rawdata.b3 = digitalRead(36);

  zero = String(data0.value, HEX);

  data1.rawdata.b0 = digitalRead(33);
  data1.rawdata.b1 = digitalRead(32);
  data1.rawdata.b2 = digitalRead(31);
  data1.rawdata.b3 = digitalRead(30);
  data2.rawdata.b0 = digitalRead(29);
  data2.rawdata.b1 = digitalRead(28);
  data2.rawdata.b2 = digitalRead(27);
  data2.rawdata.b3 = digitalRead(26);
  data3.rawdata.b0 = digitalRead(25);
  data3.rawdata.b1 = digitalRead(24);
  data3.rawdata.b2 = digitalRead(23);
  data3.rawdata.b3 = digitalRead(22);
  
  one = String(data1.value, HEX);
  two = String(data2.value, HEX);
  three = String(data3.value, HEX);


  data4.rawdata.b0 = digitalRead(2);
  data4.rawdata.b1 = digitalRead(3);
  data4.rawdata.b2 = digitalRead(4);
  data4.rawdata.b3 = digitalRead(5);
  data5.rawdata.b0 = digitalRead(6);
  data5.rawdata.b1 = digitalRead(7);
  data5.rawdata.b2 = digitalRead(8);
  data5.rawdata.b3 = digitalRead(9);
  data6.rawdata.b0 = digitalRead(10);
  data6.rawdata.b1 = digitalRead(11);
  data6.rawdata.b2 = digitalRead(12);
  data6.rawdata.b3 = digitalRead(13);
  
  four = String(data4.value, HEX);
  five = String(data5.value, HEX);
  six = String(data6.value, HEX);
  
  Serial.println(zero+one+two+three+four+five+six);
  delay(5);
}
