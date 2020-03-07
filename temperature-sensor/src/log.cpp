#include "log.h"

#include <stdarg.h>

Logger Log;

Logger::Logger(void) :
    _lvl(LOG_INFO),
    _buffer("")
{}

void Logger::log(LogLevel level,const char * msg) {
    if (_lvl > level) return;
    switch(_lvl) {
        case LOG_INFO:
            Serial.print("I ");
            break;
        case LOG_ERROR:
            Serial.print("E ");
            break;
        case LOG_WARNING:
            Serial.print("W ");
            break;
        case LOG_DEBUG:
            Serial.print("D ");
            break;
        default:
            Serial.print("  ");
            break;
    }
    Serial.println(msg);
}

void Logger::log(LogLevel level,const char* fmt, va_list arg) {
    char * temp = _buffer;
    va_list copy;
    va_copy(copy, arg);
    int len = vsnprintf(temp, sizeof(loc_buf), fmt, copy);
    va_end(copy);
    if (len < 0) {
        va_end(arg);
        return;
    }
    if (len >= sizeof(loc_buf)) {
        temp=(char*) malloc(len+1);
        if (!temp) {
            va_end(arg);
            return;
        }
        len = vsnprintf(temp, len+1, fmt, arg);
    }
    va_end(arg);

    log(level,_buffer);

    if(temp != loc_buf){
        free(temp);
    }
}

void Logger::logf(level,const char* fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    log(level,fmt,arg);
    va_end(arg);
}

void Logger::debug(const char* fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    log(LOG_DEBUG,fmt,arg);
    va_end(arg);
}

void Logger::info(const char* fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    log(LOG_INFO,fmt,arg);
    va_end(arg);
}

void Logger::warning(const char* fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    log(LOG_WARNING,fmt,arg);
    va_end(arg);
}

void Logger::error(const char* fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    log(LOG_ERROR,fmt,arg);
    va_end(arg);
}
