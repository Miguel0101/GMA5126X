#include <Arduino.h>
#include "CPU/cpu.hpp"

void fetch(Processor *processor)
{
    uint64_t address = processor->PC * sizeof(uint64_t);
    byte buffer[sizeof(uint64_t)];
    processor->RAM->read(address, sizeof(uint64_t), buffer);
    memcpy(&processor->MDR, buffer, sizeof(uint64_t));
    processor->IR = processor->MDR;
}

void decodeExecute(Processor *processor)
{
    uint64_t opcode = (processor->IR >> 56) & 0xFF;
    uint64_t operand1 = (processor->IR >> 32) & 0xFFFFFF;
    uint64_t operand2 = (processor->IR >> 8) & 0xFFFFFF;
    uint64_t operand3 = (processor->IR) & 0xFF;
    uint64_t operand4 = (processor->IR >> 8) & 0xFFFFFFFFFFFF;

    switch (opcode)
    {
    case 0x00:
        processor->REG[operand3] = readByte(processor->RAM, operand4);
        break;
    case 0x01:
        processor->REG[operand3] = operand4;
        break;
    case 0x02:
        writeByte(processor->RAM, processor->REG[operand4], operand3);
        break;
    case 0x03:
        processor->REG[operand3] = readByte(processor->RAM, processor->REG[operand4]);
        break;
    case 0x04:
        processor->REG[operand3] = processor->REG[operand4];
        break;
    case 0x05:
        processor->REG[operand3] = readWord(processor->RAM, processor->sp);
        processor->sp += sizeof(uint64_t);
        break;
    case 0x06:
        processor->sp -= sizeof(uint64_t);
        writeWord(processor->RAM, processor->sp, processor->REG[operand3]);
        break;
    case 0x07:
        processor->REG[operand3] = processor->REG[operand1] + processor->REG[operand2];
        break;
    case 0x08:
        processor->REG[operand3] = processor->REG[operand1] - processor->REG[operand2];
        break;
    case 0x09:
        processor->REG[operand3] = processor->REG[operand1] * processor->REG[operand2];
        break;
    case 0x0A:
        processor->REG[operand3] = processor->REG[operand1] / processor->REG[operand2];
        break;
    case 0x0B:
        Serial.print("0x");
        Serial.print((uint32_t)processor->REG[operand3], HEX);
        Serial.println();
        break;
    case 0x0C:
        Serial.println("HLT");
        processor->FLAGS = 0;
        break;
    case 0x0D:
        processor->PC = operand4;
        processor->FLAGS = 2;
        break;
    default:
        Serial.println("Invalid opcode!");
        break;
    }
}

void initCPU(Processor *processor)
{
    processor->PC = 0;
    processor->IR = 0;
    processor->MDR = 0;
    processor->ACC = 0;
    processor->ALU = 0;
    processor->sp = 0;
    processor->FLAGS = 1;

    for (int i = 0; i < NUM_REGS; i++)
    {
        processor->REG[i] = 0;
    }
}

void loopCPU(Processor *processor)
{
    Serial.println("Loop CPU initialized!");
    while (1)
    {
        fetch(processor);
        decodeExecute(processor);
        if (processor->FLAGS == 0)
        {
            return;
        }
        else if (processor->FLAGS == 2)
        {
            continue;
        }

        processor->PC++;
    }
}
