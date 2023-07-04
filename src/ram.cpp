#include "RAM/ram.hpp"

uint8_t readByte(SPISRAM *sram, uint64_t address)
{
    if (address % sizeof(uint64_t) != 0)
    {
        Serial.println("Error: invalid 64-bit address!");
        return 0;
    }

    byte value;
    sram->read(address, sizeof(uint8_t), &value);
    return value;
}

void writeByte(SPISRAM *sram, uint64_t address, uint8_t value)
{
    if (address % sizeof(uint64_t) != 0)
    {
        Serial.println("Error: invalid 64-bit address!");
        return;
    }

    sram->write(address, sizeof(uint8_t), &value);
}

uint64_t readWord(SPISRAM *sram, uint64_t address)
{
    if (address % sizeof(uint64_t) != 0)
    {
        Serial.println("Error: invalid 64-bit address!");
        return 0;
    }

    uint64_t value = readByte(sram, address);
    return value;
}

void writeWord(SPISRAM *sram, uint64_t address, uint64_t value)
{
    if (address % sizeof(uint64_t) != 0)
    {
        Serial.println("Error: invalid 64-bit address!");
        return;
    }

    writeByte(sram, address, (uint8_t)(value >> 56) & 0xFF);
    writeByte(sram, address, (uint8_t)(value >> 48) & 0xFF);
    writeByte(sram, address, (uint8_t)(value >> 40) & 0xFF);
    writeByte(sram, address, (uint8_t)(value >> 32) & 0xFF);
    writeByte(sram, address, (uint8_t)(value >> 24) & 0xFF);
    writeByte(sram, address, (uint8_t)(value >> 16) & 0xFF);
    writeByte(sram, address, (uint8_t)(value >> 8) & 0xFF);
    writeByte(sram, address, (uint8_t)value & 0xFF);
}
