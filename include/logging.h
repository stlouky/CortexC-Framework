#ifndef LOGGING_H
#define LOGGING_H

#include <stdarg.h>
#include <stdio.h>

/**
 * @brief Nastaví logovací soubor, do kterého budou zapisovány všechny logovací zprávy.
 *
 * Pokud je již nějaký logovací soubor otevřen, nejprve se uzavře.
 * Pokud se nový soubor nepodaří otevřít, vypíše se chybová zpráva.
 *
 * @param file_path Cesta k souboru, do kterého se budou zapisovat logy.
 */
void set_log_file(const char *file_path);

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
void log_message(const char *level, const char *function, const char *format, ...);

/**
 * @brief Loguje informační zprávu.
 *
 * Tato funkce volá log_message() s úrovní "INFO".
 *
 * @param function Název funkce, odkud je logovací zpráva volána.
 * @param format Formátovací řetězec pro zprávu (podobně jako printf).
 * @param ... Další argumenty pro formátování zprávy.
 */
#define LOG_INFO(function, format, ...) log_message("INFO", function, format, ##__VA_ARGS__)

/**
 * @brief Loguje varovnou zprávu.
 *
 * Tato funkce volá log_message() s úrovní "WARNING".
 *
 * @param function Název funkce, odkud je logovací zpráva volána.
 * @param format Formátovací řetězec pro zprávu (podobně jako printf).
 * @param ... Další argumenty pro formátování zprávy.
 */
#define LOG_WARNING(function, format, ...) log_message("WARNING", function, format, ##__VA_ARGS__)

/**
 * @brief Loguje chybovou zprávu.
 *
 * Tato funkce volá log_message() s úrovní "ERROR".
 *
 * @param function Název funkce, odkud je logovací zpráva volána.
 * @param format Formátovací řetězec pro zprávu (podobně jako printf).
 * @param ... Další argumenty pro formátování zprávy.
 */
#define LOG_ERROR(function, format, ...) log_message("ERROR", function, format, ##__VA_ARGS__)

/**
 * @brief Uzavře logovací soubor, pokud je otevřen.
 *
 * Tato funkce slouží k ukončení zápisu do logovacího souboru a uzavření souboru.
 */
void close_log_file();

FILE *get_log_file();  // Přidáno pro přístup k logovacímu souboru

#endif // LOGGING_H
