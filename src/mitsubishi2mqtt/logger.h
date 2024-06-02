#pragma once

#include <Arduino.h>

#ifdef ESP32
    #define LOG_SIZE 50000
#else 
    #define LOG_SIZE 10000 
#endif
class Logging{

    private:
        Logging() = default;
        // char logBuff[LOG_SIZE];
        // char *logBuffPTR = NULL;
        char logBuffPTR [LOG_SIZE];
        unsigned int logBuffSize = 0;
    public:
        static Logging &getInstance();
        Logging(const Logging &) = delete; // no copying
        Logging &operator=(const Logging &) = delete;

        void storeLog(char *log, size_t size);
        void f(const char* tag, char *format, ...);
        void f(const char* tag, const char *format, ...);
        void f(const char* tag,  String string);
        void ln(const char* tag, String string);
        void ln(const char* tag, const char *format, ...);
        String getLogs();

};

extern Logging &Log;