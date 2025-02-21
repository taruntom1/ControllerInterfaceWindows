#pragma once
#ifndef UARTPROTOCOL_H
#define UARTPROTOCOL_H

#include <windows.h>
#include <iostream>
#include <iomanip>

struct ProtocolConfig {
    std::string portName = "COM6";  // Change as needed
    DWORD baudRate = 115200;
    BYTE byteSize = 8;
    BYTE stopBits = ONESTOPBIT;
    BYTE parity = NOPARITY;
    uint8_t header = 0xAA;
    uint8_t maxPacketSize = 100;
};

class UARTProtocol {
private:
    HANDLE hSerial;
    ProtocolConfig config;

public:
    UARTProtocol(const ProtocolConfig& config);
    ~UARTProtocol();
    bool begin();
    void sendCommand(uint8_t command);
    void sendData(const uint8_t* data, size_t length);
    bool readCommand(uint8_t& command, DWORD timeout = 1000);
    bool readData(uint8_t* data, size_t length, DWORD timeout = 1000);
};

#endif // UARTPROTOCOL_H


