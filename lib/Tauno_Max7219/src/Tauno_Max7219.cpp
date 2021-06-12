/**********************************
 * Project:     Matrix MAX7219
 * File:        TaunoMax7219.cpp
 * Author:      Tauno Erik
 * Started:     08.07.2019
 * Description:
 *
 * Copyright 2021 Tauno Erik
 **********************************/
#include <Arduino.h>
#include <SPI.h>
#include "Tauno_Max7219.h"

/**
 * @param ss_pin
 */
Tauno_Max7219::Tauno_Max7219(
  const uint8_t ss_pin)
  : _ss_pin(ss_pin) {}

Tauno_Max7219::~Tauno_Max7219() {
  // Turn off chip.
  write_register(REG_SHUTDOWN_ADR, 0);
  SPI.end();
}

/**
 * 
 */
void Tauno_Max7219::begin() {
  pinMode(_ss_pin, OUTPUT);
  // Reverse the SPI Data o/p.
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();

  // Run test - All LED segments lit.
  test(100);

  // Disable BCD mode.
  write_register(REG_DECODE_MODE_ADR, OFF);
  // Use lowest intensity.
  write_register(REG_BRIGHTNESS_ADR, 0x00);
  // All rows are active 0x00 -> 0x07
  write_register(REG_SCAN_LIMIT_ADR, 0x07);
  // Turn on chip.
  write_register(REG_SHUTDOWN_ADR, ON);
}


/**
 * Turn test mode ON and OFF.
 * @param delay_value duration of test.
 */
void Tauno_Max7219::test(const uint16_t delay_value) {
  write_register(REG_TEST_ADR, ON);
  delay(delay_value);
  write_register(REG_TEST_ADR, OFF);
}

/**
 * @param value brightness value: min(0), max(15).
 */
void Tauno_Max7219::brightness(uint8_t value) {
  if (value > 15) {
    value = 15;
  }
  write_register(REG_BRIGHTNESS_ADR, value);  // 0-15, 0x00 - 0x0f
}

/**
 * @param address register address.
 * @param data value to write.
 */
void Tauno_Max7219::write_register(const uint8_t address, const uint8_t data) {
  digitalWrite(_ss_pin, LOW);
  SPI.transfer(address);        // Send address = row
  SPI.transfer(data);           // Send the dat = value
  digitalWrite(_ss_pin, HIGH);  // Finish transfer
}

/**
 * @param address register address.
 * @param data value to write.
 */
void Tauno_Max7219::write(const uint8_t address, const uint8_t data) {
  if (address < 9) {
    write_register(address, data);
  }
}


/**
 *  Turn all LEDs off
 */
void Tauno_Max7219::clear() {
  for (uint8_t i = 0; i < 9; i++) {
    write_register(i, OFF);
  }
}
