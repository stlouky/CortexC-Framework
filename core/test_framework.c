#include "../include/test_framework.h"

// Definice barev pro výstupy
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"

#include <stdio.h>
#include <time.h>

/**
 * @file test_framework.c
 * @brief Implementace základního testovacího frameworku pro jednotkové testy v jazyce C.
 *
 * Tento soubor poskytuje funkce pro spouštění jednotkových testů, ověřování podmínek
 * a generování souhrnných zpráv o výsledcích testů. Obsahuje nástroje pro porovnávání hodnot,
 * kontrolu ukazatelů a měření doby provádění testů.
 */

// Funkce pro sledování počtu úspěšných a neúspěšných testů
static int passed_tests = 0;  ///< Počítadlo úspěšných testů
static int failed_tests = 0;  ///< Počítadlo neúspěšných testů

/**
 * @brief Spuštění jedné testovací funkce a měření jejího času provádění.
 *
 * Tato funkce spustí zadanou testovací funkci, vypíše začátek a konec testu
 * a změří dobu provádění testu.
 *
 * @param test_func Ukazatel na testovací funkci, která má být spuštěna.
 * @param test_name Název testu, který je prováděn.
 */
void RUN_TEST(void (*test_func)(), const char *test_name) {
    printf("%s\n", test_name);
    clock_t start = clock();

    test_func();

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("%s[INFO] Čas testu %s: %.2fms%s\n", COLOR_BLUE, test_name, time_spent, COLOR_RESET);
}


/**
 * @brief Ověření, že dvě celočíselné hodnoty jsou stejné.
 *
 * Tato funkce kontroluje, zda očekávaná hodnota odpovídá skutečné hodnotě. Pokud se shodují,
 * test projde, jinak selže.
 *
 * @param expected Očekávaná hodnota.
 * @param actual Skutečná hodnota.
 * @param test_name Název testu, který je prováděn.
 */
void ASSERT_EQ(int expected, int actual, const char *test_name) {
    clock_t start = clock();
    if (expected == actual) {
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        printf("%s[PASS] %s - [%.2fms]%s\n", COLOR_GREEN, test_name, time_spent, COLOR_RESET);  // Zelená barva pro úspěch
        passed_tests++;
    } else {
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        printf("%s[FAIL] %s: Očekávaná hodnota %d, ale získána %d - [%.2fms]%s\n", COLOR_RED, test_name, expected, actual, time_spent, COLOR_RESET);  // Červená barva pro selhání
        failed_tests++;
    }
}

/**
 * @brief Ověření, že podmínka je pravdivá.
 *
 * Tato funkce kontroluje, zda je zadaná podmínka pravdivá. Pokud ano, test projde,
 * jinak selže.
 *
 * @param condition Podmínka, která má být vyhodnocena.
 * @param test_name Název testu, který je prováděn.
 */
void ASSERT_TRUE(int condition, const char *test_name) {
    clock_t start = clock();
    if (condition) {
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        printf("%s[PASS] %s - [%.2fms]%s\n", COLOR_GREEN, test_name, time_spent, COLOR_RESET);  // Zelená barva pro úspěch
        passed_tests++;
    } else {
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        printf("%s[FAIL] %s: Podmínka je nepravdivá - [%.2fms]%s\n", COLOR_RED, test_name, time_spent, COLOR_RESET);  // Červená barva pro selhání
        failed_tests++;
    }
}

/**
 * @brief Ověření, že ukazatel je NULL.
 *
 * Tato funkce kontroluje, zda je zadaný ukazatel NULL. Pokud ano, test projde,
 * jinak selže.
 *
 * @param pointer Ukazatel, který má být zkontrolován.
 * @param test_name Název testu, který je prováděn.
 */
void ASSERT_NULL(void *pointer, const char *test_name) {
    clock_t start = clock();
    if (pointer == NULL) {
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        printf("%s[PASS] %s - [%.2fms]%s\n", COLOR_GREEN, test_name, time_spent, COLOR_RESET);  // Zelená barva pro úspěch
        passed_tests++;
    } else {
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        printf("%s[FAIL] %s: Ukazatel není NULL - [%.2fms]%s\n", COLOR_RED, test_name, time_spent, COLOR_RESET);  // Červená barva pro selhání
        failed_tests++;
    }
}

/**
 * @brief Výpis souhrnu výsledků testů.
 *
 * Tato funkce vypíše celkový počet úspěšných a neúspěšných testů, poskytuje souhrn
 * celkového provedení testovací sady.
 */
void TEST_RESULT() {
    printf("\n   -------------\n");
    printf("%s[SUMMARY] Konec testu%s\n", COLOR_BLUE, COLOR_RESET);  // Modrá barva pro souhrn
    printf("%s[TESTŮ] celkem: %d  úspěšných: %d/%d%s\n", COLOR_BLUE, passed_tests + failed_tests, passed_tests, failed_tests, COLOR_RESET);  // Modrá barva pro výsledek
    if (failed_tests == 0) {
        printf("%s[RESULT] PASSED%s\n\n", COLOR_GREEN, COLOR_RESET);  // Zelená barva pro úspěch
    } else {
        printf("%s[RESULT] FAILED%s\n\n", COLOR_RED, COLOR_RESET);  // Červená barva pro selhání
    }
}
