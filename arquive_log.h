#ifndef ARQUIVE_LOG_H
#define ARQUIVE_LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>    // Para obter a data e hora

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

void log_to_file(const char *filename, LogLevel level, const char *format, ...) ;



#endif // CRIA_ARQUIVO_H