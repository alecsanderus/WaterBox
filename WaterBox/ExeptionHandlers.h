
#pragma once
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>


std::string GetStackTrace();

void OpenProgramDeathScreen(const std::string& log) {
    std::string fullLog = log + "\n\nStack trace:\n" + GetStackTrace();
    LOG_FATAL(fullLog);

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", log.c_str(), nullptr);
}


void SDLCALL LogCallback(void* userdata, int category, SDL_LogPriority priority, const char* message) {
    std::string level;
    switch (priority) {
    case SDL_LOG_PRIORITY_VERBOSE:
    case SDL_LOG_PRIORITY_DEBUG:   level = "DEBUG"; break;
    case SDL_LOG_PRIORITY_INFO:    level = "INFO";  break;
    case SDL_LOG_PRIORITY_WARN:    level = "WARN";  break;
    case SDL_LOG_PRIORITY_ERROR:   level = "ERROR"; break;
    case SDL_LOG_PRIORITY_CRITICAL:level = "CRITICAL"; break;
    default: level = "UNKNOWN";
    }
    Logger::Instance().Log(level, std::string("[SDL] ") + message);
}



#ifdef _WIN32
#include <windows.h>
#include <eh.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

void TranslateException(unsigned int code, EXCEPTION_POINTERS* ep) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << code;
    std::string errorMsg = "Windows Exception: Code 0x" + ss.str();

    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION:     errorMsg += " (Access Violation)"; break;
    case EXCEPTION_STACK_OVERFLOW:       errorMsg += " (Stack Overflow)"; break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:   errorMsg += " (Division by Zero)"; break;
    }
    throw std::runtime_error(errorMsg);
}

std::string GetStackTrace() {
    std::stringstream ss;
    void* stack[64];
    WORD frames = CaptureStackBackTrace(0, 64, stack, NULL);

    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);

    SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256, 1);
    if (symbol)
    {
        symbol->MaxNameLen = 255;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

        for (WORD i = 0; i < frames; i++) {
            if (SymFromAddr(process, (DWORD64)stack[i], 0, symbol)) {
                ss << "  [" << i << "] " << symbol->Name
                    << " (0x" << std::hex << std::uppercase << symbol->Address << ")\n";
            }
        }

        free(symbol);
    }
    else
        ss << "Can not get Stack Trace";

    SymCleanup(process);
    return ss.str();
}

LONG WINAPI UnhandledExceptionFilterPro(EXCEPTION_POINTERS* ep) {
    std::string errorMsg = "=== UNHANDLED EXCEPTION ===\n";
    DWORD code = ep->ExceptionRecord->ExceptionCode;

    std::stringstream codeStream;
    codeStream << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << code;

    errorMsg += "Exception Code: " + codeStream.str() + "\n";

    std::stringstream addrStream;
    addrStream << std::hex << std::uppercase << (void*)ep->ExceptionRecord->ExceptionAddress;
    errorMsg += "Address: 0x" + addrStream.str() + "\n\n";

    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION:
        errorMsg += "Type: ACCESS VIOLATION\n";
        if (ep->ExceptionRecord->NumberParameters >= 2) {
            errorMsg += ep->ExceptionRecord->ExceptionInformation[0] == 0 ? "Operation: READ\n" : "Operation: WRITE\n";
            std::stringstream faultAddr;
            faultAddr << "Fault Address: 0x" << std::hex << std::uppercase << (void*)ep->ExceptionRecord->ExceptionInformation[1] << "\n";
            errorMsg += faultAddr.str();
        }
        break;
    case EXCEPTION_STACK_OVERFLOW:       errorMsg += "Type: STACK OVERFLOW\n"; break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:   errorMsg += "Type: INTEGER DIVISION BY ZERO\n"; break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:   errorMsg += "Type: FLOAT DIVISION BY ZERO\n"; break;
    case EXCEPTION_BREAKPOINT:           errorMsg += "Type: BREAKPOINT\n"; break;
    default:                             errorMsg += "Type: UNKNOWN\n"; break;
    }

    errorMsg += "\nStack trace:\n" + GetStackTrace();

    LOG_FATAL(errorMsg);

#ifndef _DEBUG
    MessageBoxA(NULL, errorMsg.c_str(), "WaterBox - Critical Error", MB_ICONERROR | MB_OK);
#endif

    return EXCEPTION_EXECUTE_HANDLER;
}

#else

std::string GetStackTrace() {
    return "Stack trace is not available on this platform.\n";
}

#endif