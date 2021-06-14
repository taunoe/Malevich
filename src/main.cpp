/*
 *  Raadio teel juhitav maatrix: Receiver
 *  main.cpp
 *  12.06.2021
 *  Copyright 2021 Tauno Erik
 */
#include <Arduino.h>
#include <SPI.h>
#include <Tauno_Max7219.h>

/* Max7219 Matrix

   Max7219 CLK - SCLK - Arduino pin 13
   Max7219 DIN - MOSI - Arduino pin 11
   Max7219 LOAD - CS -  Arduino pin 9
*/
const int MAX_CS_PIN = 9;

Tauno_Max7219 mx(MAX_CS_PIN);

uint8_t row = 0;
uint8_t column = 0;

uint8_t matrix[8] = {
  /* Matrix 1 */
  0b00000000,  // 1
  0b00000000,  // 2
  0b00000000,  // 3
  0b00000000,  // 4
  0b00000000,  // 5
  0b00000000,  // 6
  0b00000000,  // 7
  0b00000000   // 8
};

/***0********************************/
/* Matrix */
void random_patern(int16_t delay_value) {
  uint8_t row = 0;
  int i = 0, ud = 1;  // Need signed numbers.

  while (1) {
    i += ud;
    if (i > 255) {
      ud = -1;
      i = 255;
    }
    if (i < 0)   {
      ud = 1;
      i = 0;
    }
    if (row++ > 8) {
      row = 1;
  }

    mx.write(row, random(0, 255));
    // my_matrix.brightness(i>>4);
    delay(delay_value);
  }
}


void one_by_one(int delay_value) {  // int16_t delay_value
  int tulp = 1;

  for (uint8_t j = 1; j < 9; j++) {
    for (uint8_t i = 0; i <= 8; i++) {
      if (i == 8) {
        mx.write(j, 0);
      } else {
        mx.write(j, tulp);
            tulp = tulp << 1;
        delay(delay_value);
      }
    }
    tulp = 1;
  }
}
/***********************************/

void setup() {
  //Serial.begin(9600);

  /** Matrix **/
  mx.begin();
  mx.brightness(5);
  mx.clear();
}

void loop() {
  // mx.write(row, column);
  /*if (column > 256) {
    row++;
    column = 1;
  }*/
  delay(100);
  one_by_one(500);

/*
  mx.write(row + 1, matrix[row]);

  Serial.print("r=");
  Serial.print(row + 1);
  Serial.print(" c=");
  Serial.println(matrix[row]);

  if (matrix[row] == 255) {
    matrix[row+1] = matrix[row+1] + 1;
  }
  matrix[row] = matrix[row] + 1;
*/

/*
  for (uint8_t i = 0; i < 9; i++) {
    mx.write(i+1, matrix[i]);
    delay(500);
  }
*/
}
