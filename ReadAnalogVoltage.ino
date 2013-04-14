/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue0 = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage0 = sensorValue0 * (3.3 / 1023.0);
  
  int sensorValue1 = analogRead(A1);
  float voltage1 = sensorValue1 * (3.3 / 1023.0);
//    int sensorValue2 = analogRead(A2);
//  float voltage2 = sensorValue2 * (3.3 / 1023.0);
//    int sensorValue3 = analogRead(A3);
//  float voltage3 = sensorValue3 * (3.3 / 1023.0);
//    int sensorValue4 = analogRead(A4);
//  float voltage4 = sensorValue4 * (3.3 / 1023.0);
//    int sensorValue5 = analogRead(A5);
//  float voltage5 = sensorValue5 * (3.3 / 1023.0);
  
  // print out the value you read:
  Serial.println("V0\tV1");
  Serial.print(sensorValue0);
  Serial.print("\t");
  Serial.print(sensorValue1);
//  Serial.print(voltage2);
//  Serial.print(voltage3);
//  Serial.print(voltage4);
//  Serial.print(voltage5);
  Serial.print("\n");
  
  delay(1000);
}
