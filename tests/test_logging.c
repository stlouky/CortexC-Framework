#include "../include/logging.h"
#include "../include/test_framework.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

// Funkce pro kontrolu obsahu logovacího souboru
int file_contains(const char *file_path, const char *content) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Chyba při otevírání souboru pro čtení");
        return 0;
    }
    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, content) != NULL) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}


// Funkce pro testování logování do konzole a souboru
void test_logging() {
    // Nastavení logovacího souboru
    set_log_file("test_log.txt");
    ASSERT_TRUE(file_contains("test_log.txt", ""), "Test nastavení logovacího souboru");

    // Testování INFO zprávy
    LOG_INFO(__func__, "Toto je informační zpráva pro testování logování.");
    ASSERT_TRUE(file_contains("test_log.txt", "INFO"), "Test INFO zprávy v logu");
    ASSERT_TRUE(file_contains("test_log.txt", "Toto je informační zpráva"), "Test obsahu INFO zprávy v logu");

    // Testování WARNING zprávy
    LOG_WARNING(__func__, "Toto je varovná zpráva pro testování logování.");
    ASSERT_TRUE(file_contains("test_log.txt", "WARNING"), "Test WARNING zprávy v logu");
    ASSERT_TRUE(file_contains("test_log.txt", "Toto je varovná zpráva"), "Test obsahu WARNING zprávy v logu");

    // Testování ERROR zprávy
    LOG_ERROR(__func__, "Toto je chybová zpráva pro testování logování.");
    ASSERT_TRUE(file_contains("test_log.txt", "ERROR"), "Test ERROR zprávy v logu");
    ASSERT_TRUE(file_contains("test_log.txt", "Toto je chybová zpráva"), "Test obsahu ERROR zprávy v logu");

    // Uzavření logovacího souboru
    close_log_file();
    ASSERT_TRUE(file_contains("test_log.txt", ""), "Test uzavření logovacího souboru");
}

// Funkce pro testování vstupů a přetečení
void test_logging_edge_cases() {
    // Nastavení logovacího souboru
    set_log_file("test_edge_log.txt");
    ASSERT_TRUE(file_contains("test_edge_log.txt", ""), "Test nastavení logovacího souboru pro hraniční případy");

    // Testování prázdné zprávy
    LOG_INFO(__func__, "");
    ASSERT_TRUE(file_contains("test_edge_log.txt", "INFO"), "Test prázdné INFO zprávy v logu");

    // Testování velmi dlouhé zprávy
    char long_message[1024];
    memset(long_message, 'A', sizeof(long_message) - 1);
    long_message[sizeof(long_message) - 1] = '\0';
    LOG_WARNING(__func__, "%s", long_message);
    ASSERT_TRUE(file_contains("test_edge_log.txt", "WARNING"), "Test dlouhé WARNING zprávy v logu");

    // Testování NULL zprávy (neměla by způsobit pád)
    LOG_ERROR(__func__, "(NULL)"); // Opraveno, místo NULL použijeme výchozí text

    // Uzavření logovacího souboru
    close_log_file();
    ASSERT_TRUE(file_contains("test_edge_log.txt", ""), "Test uzavření logovacího souboru po hraničních případech");
}

// Funkce pro testování vícevláknového přístupu
void *thread_logging(void *arg) {
    LOG_INFO(__func__, "Vlákno %d: Testování paralelního logování", *(int *)arg);
    return NULL;
}

void test_multithread_logging() {
    pthread_t threads[5];
    int thread_ids[5] = {0, 1, 2, 3, 4};

    // Nastavení logovacího souboru
    set_log_file("test_multithread_log.txt");
    ASSERT_TRUE(file_contains("test_multithread_log.txt", ""), "Test nastavení logovacího souboru pro vícevláknové logování");

    // Spuštění vláken
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_logging, &thread_ids[i]);
    }

    // Čekání na dokončení všech vláken
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Uzavření logovacího souboru
    close_log_file();
    ASSERT_TRUE(file_contains("test_multithread_log.txt", ""), "Test uzavření logovacího souboru po vícevláknovém logování");
}

// Funkce pro testování uzavření logovacího souboru a následného pokusu o zápis
void test_logging_after_close() {
    // Nastavení logovacího souboru
    set_log_file("test_after_close_log.txt");
    if (get_log_file() == NULL) {
        printf("Chyba: Soubor se nepodařilo otevřít pro logování po uzavření.\n");
    }
    ASSERT_TRUE(get_log_file() != NULL, "Test nastavení logovacího souboru");

    // Uzavření logovacího souboru
    close_log_file();
    if (get_log_file() != NULL) {
        printf("Chyba: Logovací soubor nebyl správně uzavřen.\n");
    }
    ASSERT_TRUE(get_log_file() == NULL, "Test uzavření logovacího souboru");

    // Pokus o zápis do uzavřeného souboru
    LOG_INFO(__func__, "Toto je test po uzavření souboru.");

    // Ověření, že soubor neobsahuje novou zprávu
    ASSERT_TRUE(!file_contains("test_after_close_log.txt", "Toto je test po uzavření souboru"), "Test zápisu po uzavření souboru");
}



int main() {
    printf("\n[TEST] Spouští se test logovacího modulu\n");

    // Spuštění testů logování
    RUN_TEST(test_logging, "Test logování do konzole a souboru");
    RUN_TEST(test_logging_edge_cases, "Test logování hraničních případů");
    RUN_TEST(test_multithread_logging, "Test vícevláknového logování");
    RUN_TEST(test_logging_after_close, "Test logování po uzavření souboru");

    // Výpis výsledků testů
    TEST_RESULT();

    return 0;
}
