#include "test_framework.h"
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
    printf("\033[34m[TIMER] Start: %s\033[0m\n", test_name);  // Modrá barva pro začátek měření času
    clock_t start = clock();

    test_func();

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;  // Čas v milisekundách
    printf("\033[34m[TIMER] Konec: %s (Čas: %.2fms)\033[0m\n", test_name, time_spent);  // Modrá barva pro konec měření času
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
    if (expected == actual) {
        printf("\033[32m[PASS] %s\033[0m\n", test_name);  // Zelená barva pro úspěch
        passed_tests++;
    } else {
        printf("\033[31m[FAIL] %s: Očekávaná hodnota %d, ale získána %d\033[0m\n", test_name, expected, actual);  // Červená barva pro selhání
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
    if (condition) {
        printf("\033[32m[PASS] %s\033[0m\n", test_name);  // Zelená barva pro úspěch
        passed_tests++;
    } else {
        printf("\033[31m[FAIL] %s: Podmínka je nepravdivá\033[0m\n", test_name);  // Červená barva pro selhání
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
    if (pointer == NULL) {
        printf("\033[32m[PASS] %s\033[0m\n", test_name);  // Zelená barva pro úspěch
        passed_tests++;
    } else {
        printf("\033[31m[FAIL] %s: Ukazatel není NULL\033[0m\n", test_name);  // Červená barva pro selhání
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
    printf("\033[34m[SUMMARY] Testovací sada dokončena.\033[0m\n");  // Modrá barva pro souhrn
    printf("\033[34m[RESULT] Úspěšné: %d, Neúspěšné: %d\033[0m\n", passed_tests, failed_tests);  // Modrá barva pro výsledek
}
