#include "arquive_log.h"

// Função para converter o nível de log em string
const char* get_log_level_string(LogLevel level) {
    switch (level) {
        case LOG_INFO: return "INFO";
        case LOG_WARNING: return "WARNING";
        case LOG_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}


// Função para gravar mensagens formatadas em um arquivo de log
void log_to_file(const char *filename, LogLevel level, const char *format, ...)  {
    FILE *file;
    va_list args;
    time_t timer;
    struct tm *tm_info;
    char timestamp_buffer[25]; // Buffer para armazenar o timestamp formatado

    // Abre o arquivo em modo de anexação (append)
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de log");
        return;
    }

    // --- Obter e formatar o timestamp (sem milissegundos) ---
    time(&timer); // Obtém o tempo atual em segundos
    tm_info = localtime(&timer); // Converte para hora local

    // Formata o timestamp: [AAAA-MM-DD HH:MM:SS]
    snprintf(timestamp_buffer, sizeof(timestamp_buffer), "[%04d-%02d-%02d %02d:%02d:%02d]",
             tm_info->tm_year + 1900, // Ano desde 1900
             tm_info->tm_mon + 1,    // Mês (0-11)
             tm_info->tm_mday,       // Dia do mês
             tm_info->tm_hour,       // Hora
             tm_info->tm_min,        // Minuto
             tm_info->tm_sec);       // Segundo

    // Escreve o timestamp e o nível no arquivo
    fprintf(file, "%s [%s] ", timestamp_buffer, get_log_level_string(level));

    // --- Gravar a mensagem formatada ---
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);

    fclose(file);
}