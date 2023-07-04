#ifndef CPU_HPP
#define CPU_HPP

#include <Arduino.h>
#include <SPI.h>
#include "RAM/ram.hpp"

#define NUM_REGS 16

typedef struct
{
    uint64_t PC;            // Program Counter
    uint64_t IR;            // Instruction Register
    uint64_t MDR;           // Memory Data Register
    uint64_t ACC;           // Accumulator
    uint64_t ALU;           // Arithmetic Logic Unit
    uint64_t sp;            // Stack Pointer
    uint64_t REG[NUM_REGS]; // Registers
    uint8_t FLAGS;          // Flags: 0 -> HLT, 1 -> RUNNING, 2 -> JMP
    SPISRAM *RAM;
} Processor;

void fetch(Processor *processor);
void decodeExecute(Processor *processor);
void initCPU(Processor *processor);
void loopCPU(Processor *processor);

#endif
