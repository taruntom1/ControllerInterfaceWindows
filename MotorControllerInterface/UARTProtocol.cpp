#include "UARTProtocol.h"

UARTProtocol::UARTProtocol(const ProtocolConfig& cfg) : config(cfg), hSerial(INVALID_HANDLE_VALUE) {}

UARTProtocol::~UARTProtocol() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
    }
}

bool UARTProtocol::begin() {
    hSerial = CreateFileA(config.portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port" << std::endl;
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial port state" << std::endl;
        return false;
    }

    dcbSerialParams.BaudRate = config.baudRate;
    dcbSerialParams.ByteSize = config.byteSize;
    dcbSerialParams.StopBits = config.stopBits;
    dcbSerialParams.Parity = config.parity;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port parameters" << std::endl;
        return false;
    }

    return true;
}

void UARTProtocol::sendCommand(uint8_t command) {
    uint8_t commandArr[2] = { config.header, command };
    DWORD bytesWritten;
    WriteFile(hSerial, commandArr, 2, &bytesWritten, nullptr);
}

void UARTProtocol::sendData(const uint8_t* data, size_t length) {
    DWORD bytesWritten;
    WriteFile(hSerial, data, length, &bytesWritten, nullptr);
}

bool UARTProtocol::readCommand(uint8_t& command, DWORD timeout) {
    COMMTIMEOUTS timeouts = { 0, 0, timeout, 0, 0 };
    SetCommTimeouts(hSerial, &timeouts);

    uint8_t buffer;
    DWORD bytesRead;

    // Keep reading until we get the header
    while (ReadFile(hSerial, &buffer, 1, &bytesRead, nullptr) && bytesRead > 0) {
        if (buffer == config.header) {
            // Header found, now read the command byte
            if (ReadFile(hSerial, &command, 1, &bytesRead, nullptr) && bytesRead > 0) {
                return true;
            }
            return false; // Failed to read the command
        }
    }
    return false; // No valid header found within timeout
}


bool UARTProtocol::readData(uint8_t* data, size_t length, DWORD timeout) {
    DWORD bytesRead;
    COMMTIMEOUTS timeouts = { 0, 0, timeout, 0, 0 };
    SetCommTimeouts(hSerial, &timeouts);

    return ReadFile(hSerial, data, length, &bytesRead, nullptr) && bytesRead == length;
}
