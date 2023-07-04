#ifndef RAM_HPP
#define RAM_HPP

#include <Arduino.h>
#include <SPISRAM.h>
#include <SPI.h>

#define RAM_SIZE 0x20000

uint8_t readByte(SPISRAM *sram, uint64_t address);
void writeByte(SPISRAM *sram, uint64_t address, uint8_t value);
uint64_t readWord(SPISRAM *sram, uint64_t address);
void writeWord(SPISRAM *sram, uint64_t address, uint64_t value);

#endif
