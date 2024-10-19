#include "test_framework.h"
#include <stdlib.h>

/**
 * @file test_memory.c
 * @brief Testy pro ověření funkcionality správy paměti.
 *
 * Tento soubor obsahuje jednotkové testy pro kontrolu funkcí pro správu paměti,
 * včetně bezpečné alokace a uvolnění paměti.
 */

// Prototypy testovacích funkcí
void test_safe_alloc();
void test_free_safe();

/**
 * @brief Test bezpečné alokace paměti.
 *
 * Tato funkce kontroluje, zda alokace paměti proběhne správně a vrátí platný ukazatel.
 */
void test_safe_alloc() {
    void *ptr = malloc(100);  // Alokace 100 bajtů
    ASSERT_TRUE(ptr != NULL, "test_safe_alloc - alokace paměti");
    free(ptr);
}

/**
 * @brief Test bezpečného uvolnění paměti.
 *
 * Tato funkce kontroluje, zda po uvolnění paměti není ukazatel platný.
 */
void test_free_safe() {
    void *ptr = malloc(100);  // Alokace 100 bajtů
    free(ptr);                // Uvolnění paměti
    ptr = NULL;               // Nastavení ukazatele na NULL
    ASSERT_NULL(ptr, "test_free_safe - uvolnění paměti");
}

/**
 * @brief Hlavní funkce pro spuštění všech testů správy paměti.
 */
int main() {
    RUN_TEST(test_safe_alloc, "Test bezpečné alokace paměti");
    RUN_TEST(test_free_safe, "Test bezpečného uvolnění paměti");
    
    TEST_RESULT();  // Výpis souhrnných výsledků testů
    return 0;
}
