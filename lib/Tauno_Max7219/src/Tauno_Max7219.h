/*********************************************
 * Project:     Matrix MAX7219
 * File:        TaunoMax7219.h
 * Author:      Tauno Erik
 * Started:     08.07.2019
 * Description:
 * 
 * Copyright 2021 Tauno Erik
 *********************************************/
#ifndef LIB_TAUNO_MAX7219_SRC_TAUNO_MAX7219_H_
#define LIB_TAUNO_MAX7219_SRC_TAUNO_MAX7219_H_

#include "Arduino.h"

// MAX7219 Register Address Map
#define REG_NOOP_ADR        0x00
#define REG_DIGIT_0_ADR     0x01
#define REG_DIGIT_1_ADR     0x02
#define REG_DIGIT_2_ADR     0x03
#define REG_DIGIT_3_ADR     0x04
#define REG_DIGIT_4_ADR     0x05
#define REG_DIGIT_5_ADR     0x06
#define REG_DIGIT_6_ADR     0x07
#define REG_DIGIT_7_ADR     0x08
#define REG_DECODE_MODE_ADR 0x09
#define REG_BRIGHTNESS_ADR  0x0a
#define REG_SCAN_LIMIT_ADR  0x0b
#define REG_SHUTDOWN_ADR    0x0c
#define REG_TEST_ADR        0x0f
//
#define ON                  0x01
#define OFF                 0x00

class Tauno_Max7219 {
 private:
  int _ss_pin;

  void write_register(uint8_t address, uint8_t data);

 public:
  // constructor
  explicit Tauno_Max7219(const uint8_t ss_pin);
  // deconstructor
  ~Tauno_Max7219();
  // methods
  void begin();
  void test(uint16_t delay_value);
  void brightness(uint8_t value);  // 0-15 0x0 - 0xF
  void write(uint8_t address, uint8_t data);
  void clear();  // all off
};

#endif  // LIB_TAUNO_MAX7219_SRC_TAUNO_MAX7219_H_
