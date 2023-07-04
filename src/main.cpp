#include <Arduino.h>
#include "CPU/cpu.hpp"
#include "RAM/ram.hpp"
#include <SPI.h>

uint64_t program[] = {
    0x010000000000FF00,
    0x010000000000AE01,
    0x0900000000000102,
    0x0B00000000000002,
    0x0C00000000000000,
};

Processor processor;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    processor.RAM = new SPISRAM(&SPI);

    processor.RAM->begin();

    initCPU(&processor);
    Serial.println("GMA5126X CPU");
    processor.RAM->write(0, sizeof(program), reinterpret_cast<byte *>(&program)); // Load program to SRAM
    loopCPU(&processor);
    Serial.println("CPU finished!");
}

void loop()
{
}