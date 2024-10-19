#include "../include/logging.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdlib.h>

// Cesta k logovacímu souboru
/**
 * @brief Ukazatel na soubor, do kterého se zapisují logy.
 *
 * Pokud není nastaven žádný logovací soubor, zůstane NULL.
 */
static FILE *log_file = NULL;

// Mutex pro synchronizaci přístupu k logovacímu souboru
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

// Funkce pro nastavení logovacího souboru
/**
 * @brief Nastaví logovací soubor, do kterého budou zapisovány všechny logovací zprávy.
 *
 * Pokud je již nějaký logovací soubor otevřen, nejprve se uzavře.
 * Pokud se nový soubor nepodaří otevřít, vypíše se chybová zpráva.
 *
 * @param file_path Cesta k souboru, do kterého se budou zapisovat logy.
 */
void set_log_file(const char *file_path) {
    pthread_mutex_lock(&log_mutex);
    if (log_file != NULL) {
        fclose(log_file);
    }
    log_file = fopen(file_path, "a");
    if (log_file == NULL) {
        perror("[ERROR] Nelze otevřít logovací soubor");
    } else {
        atexit(close_log_file);
    }
    pthread_mutex_unlock(&log_mutex);
}

// Funkce pro získání aktuálního časového razítka
/**
 * @brief Získá aktuální časové razítko ve formátu "YYYY-MM-DD HH:MM:SS".
 *
 * Tato funkce zapíše aktuální čas do zadaného bufferu.
 *
 * @param buffer Ukazatel na buffer, kam se zapíše časové razítko.
 * @param buffer_size Velikost bufferu.
 */
static void get_timestamp(char *buffer, size_t buffer_size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", t);
}

// Funkce pro logování zpráv
/**
 * @brief Loguje zprávu s danou úrovní závažnosti.
 *
 * Tato funkce formátuje logovací zprávu a vypisuje ji do konzole a případně do logovacího souboru.
 *
 * @param level Úroveň závažnosti logu (např. "INFO", "WARNING", "ERROR").
 * @param function Název funkce, odkud je logovací zpráva volána.
 * @param format Formátovací řetězec pro zprávu (podobně jako printf).
 * @param ... Další argumenty pro formátování zprávy.
 */
void log_message(const char *level, const char *function, const char *format, ...) {
    if (format == NULL) {
        format = "(NULL)";  // Nahrazení NULL formátovacího řetězce výchozím textem
    }

    char timestamp[20];
    get_timestamp(timestamp, sizeof(timestamp));

    // Formátování zprávy
    char buffer[512];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Výpis do konzole
    printf("[%s] [%s] [%s] %s\n", timestamp, level, function, buffer);

    // Logování do souboru, pokud je nastaven
    if (log_file != NULL) {
        pthread_mutex_lock(&log_mutex);
        fprintf(log_file, "[%s] [%s] [%s] %s\n", timestamp, level, function, buffer);
        fflush(log_file);
        pthread_mutex_unlock(&log_mutex);
    }
}


// Uzavření logovacího souboru
/**
 * @brief Uzavře logovací soubor, pokud je otevřen.
 *
 * Tato funkce slouží k ukončení zápisu do logovacího souboru a uzavření souboru.
 */
void close_log_file() {
    pthread_mutex_lock(&log_mutex);
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
    pthread_mutex_unlock(&log_mutex);
}

FILE *get_log_file() {
    return log_file;
}
