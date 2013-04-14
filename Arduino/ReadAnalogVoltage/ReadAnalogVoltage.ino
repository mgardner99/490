//left foot pin codes
/*
const int s0 = A2;
const int s1 = A1;
const int s2 = A4;
const int s3 = A0;
const int s4 = A5;
const int s5 = A3;
*/

//right foot pin codes
const int s0 = A3;
const int s1 = A4;
const int s2 = A1;
const int s3 = A5;
const int s4 = A0;
const int s5 = A2;



//vars
int val0;
int val1;
int val2;
int val3;
int val4;
int val5;

void outData(int sensor, int data);

void setup() {
  Serial.begin(9600);
}

void loop() {
 
  val0 = analogRead(s0);
  val1 = analogRead(s1);
  val2 = analogRead(s2);
  val3 = analogRead(s3);
  val4 = analogRead(s4);
  val5 = analogRead(s5);
  
  //transmit the data
  outData('a',val0);
  outData('b',val1);
  outData('c',val2);
  outData('d',val3);
  outData('e',val4);
  outData('f',val5);
  
  delay(1000/60); //this can be changed later
  
  
}


//should output a packet onto the wireless of constant size 6 bytes.
//1 byte sensor label, 4 bytes data, 1 byte footer
void outData(char sensor, int data){
 
  Serial.print(sensor); //1 byte label
  
  for(int i = 0; i < 4 - String(data).length(); i++){
    Serial.print(0); //1 byte ascii 0 buffer to maintain constant packet size
  }
  
  Serial.print(data); //actual data
  Serial.print('z'); //1 byte footer
  
}
