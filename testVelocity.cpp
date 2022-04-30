/*
 * The purpose of this code is to test the instantaneous acceleration
 */
#include "include/RingBuffer.h"
#include <iostream>
#include "velocity.h"
#define Encoder_output_A 2 // pin2 of the Arduino
#define Encoder_output_B 3 // pin 3 of the Arduino
// these two pins has the hardware interrupts as well. 
#define MAX_SIZE 4097
struct R
{
     float v;
     int p;
};

int pos = 0;
int i = 0;
long prevT = 0;
float posprev = 0;
void setup() {
Serial.begin(9600); // activates the serial communication
pinMode(Encoder_output_A,INPUT); // sets the Encoder_output_A pin as the input
pinMode(Encoder_output_B,INPUT); // sets the Encoder_output_B pin as the input
attachInterrupt(digitalPinToInterrupt(Encoder_output_A),DC_Motor_Encoder,RISING);
 /* Create and initialize ring buffer */
RingBuffer<32, int> buffer; // 
Block<int> block;
}

void loop() {
  Serial.println("Position: ");
  Serial.println(pos); 
  /* Write the value in a ring buffer */
  buffer.Append(pos);
  i = i + 1;
  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;
  // Compute velocity 
  R result = velocity(buffer, block, i, posprev, deltaT);
  Serial.println("Velocity: ");
  Serial.println(result.v); 
  // store previous position
  posprev = result.p;
  
}

void DC_Motor_Encoder(){
  int b = digitalRead(Encoder_output_B);
  if(b > 0){
    pos++;
  }
  else{
    pos--;
  }
}