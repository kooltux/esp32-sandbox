#ifndef __log_h__
#define __log_h__

typedef enum {
    LOG_DEBUG=0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

class Logger {
    public:
        void log(LogLevel level,const char *);
        void logf(LogLevel level,const char* fmt, ...)  __attribute__ ((format (printf, 2, 3)));

        void debug(const char *msg) { log(LOG_DEBUG,msg); }
        void debug(const char* fmt, ...) __attribute__ ((format (printf, 2, 3)));
        void info(const char *msg) { log(LOG_INFO,msg); }
        void info(const char* fmt, ...) __attribute__ ((format (printf, 2, 3)));
        void warning(const char *msg) { log(LOG_WARNING,msg); }
        void warning(const char* fmt, ...) __attribute__ ((format (printf, 2, 3)));
        void error(const char *msg) { log(LOG_ERROR,msg); }
        void error(const char* fmt, ...) __attribute__ ((format (printf, 2, 3)));

        void setLevel(LogLevel lvl) { _lvl=lvl; };

    private:
        LogLevel _lvl;
        char _buffer[128];
}

extern Logger Log;

#endif