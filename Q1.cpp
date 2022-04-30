/*
 * The purpose of this code is to count the encoder outputs 
 * as you rotate the Motor shaft and store 
 * that value in a ring buffer.
 */
#include "include/RingBuffer.h"
#include <iostream>
#define Encoder_output_A 2 // pin2 of the Arduino
#define Encoder_output_B 3 // pin 3 of the Arduino
// these two pins has the hardware interrupts as well. 
#define MAX_SIZE 4097


int Count_pulses = 0;
void setup() {
Serial.begin(9600); // activates the serial communication
pinMode(Encoder_output_A,INPUT); // sets the Encoder_output_A pin as the input
pinMode(Encoder_output_B,INPUT); // sets the Encoder_output_B pin as the input
attachInterrupt(digitalPinToInterrupt(Encoder_output_A),DC_Motor_Encoder,RISING);
 /* Create and initialize ring buffer */
RingBuffer<32, int> buffer;
Block<int> block;
}

void loop() {
  Serial.println("Result: ");
  Serial.println(Count_pulses); 
   /* Write the value in a ring buffer */
  buffer.Append(Count_pulses);
}

void DC_Motor_Encoder(){
  int b = digitalRead(Encoder_output_B);
  if(b > 0){
    Count_pulses++;
  }
  else{
    Count_pulses--;
  }
}