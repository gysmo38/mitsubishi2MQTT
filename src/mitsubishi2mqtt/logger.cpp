#include "logger.h"


Logging &Logging::getInstance() {
  static Logging instance ;
  return instance   ;
}

void Logging:: storeLog(char *log, size_t size){
    // return;

    if (size > 512)
        size = 512;


    memcpy(logBuffPTR + logBuffSize , log, sizeof(char) * size );

    logBuffSize += size;
    

    //Rotate log if buffer full
    if (logBuffSize + 512 >= LOG_SIZE){
        // Serial.println("rotate buff");
        memmove(logBuffPTR, &logBuffPTR[512], logBuffSize);
        // memmove(logBuffPTR, logBuffPTR +512, logBuffSize);
        logBuffSize -= 512;
    }


}


void Logging:: f(const char* tag, char *format, ...){
    va_list args;
    char buff[512];
    int size = 0 ;

    va_start(args, format);
    size += sprintf(buff, "[%s:%08d]\t",tag, millis()/1000);
    size += vsnprintf(&buff[size], 512, format, args);

    #ifdef ESP32
        //Log to USB-CDC of ESP32-S3
        for (int i =0 ;  i < size; i++){
            Serial.print(buff[i]);
        }
    #else
        //Other logging output here.
    #endif
    

    this->storeLog(buff, size);
}

void Logging::  f(const char* tag, const char *format, ...){
    this->f(tag, (char*) format);
}

void Logging:: f(const char* tag,  String string){
    this->f(tag, string.c_str());
}

void Logging::  ln(const char* tag, String string){
    string += "\n";
    this->f(tag, string.c_str());
}

void Logging:: ln(const char* tag, const char *format, ...){

    va_list args;
    char buff[512];
    int size = 0 ;

    va_start(args, format);
    size += sprintf(buff, "[%s:%08d]\t",tag, millis()/1000);
    size += vsnprintf(&buff[size], 512, format, args);
    buff[size] = '\n';
    size++;

    #ifdef ESP32
        //Log to USB-CDC of ESP32-S3
        for (int i =0 ;  i < size; i++){
            Serial.print(buff[i]);
        }
    #else
        //Other logging output here.
    #endif

    this->storeLog(buff, size);
}

String Logging::getLogs(){
    String logs = "";

    for (int i = 0; i < logBuffSize; i++){
        logs += (logBuffPTR)[i];
    }
    return logs;
}

Logging &Log = Log.getInstance();
