#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

/**
 * @file test_framework.h
 * @brief Hlavičkový soubor pro základní testovací framework v jazyce C.
 *
 * Tento soubor deklaruje funkce pro jednotkové testování, včetně funkcí pro
 * ověřování podmínek, porovnávání hodnot, kontrolu ukazatelů a generování
 * souhrnných zpráv o výsledcích testů.
 */

/**
 * @brief Spuštění jedné testovací funkce a měření jejího času provádění.
 *
 * @param test_func Ukazatel na testovací funkci, která má být spuštěna.
 * @param test_name Název testu, který je prováděn.
 */
void RUN_TEST(void (*test_func)(), const char *test_name);

/**
 * @brief Ověření, že dvě celočíselné hodnoty jsou stejné.
 *
 * @param expected Očekávaná hodnota.
 * @param actual Skutečná hodnota.
 * @param test_name Název testu, který je prováděn.
 */
void ASSERT_EQ(int expected, int actual, const char *test_name);

/**
 * @brief Ověření, že podmínka je pravdivá.
 *
 * @param condition Podmínka, která má být vyhodnocena.
 * @param test_name Název testu, který je prováděn.
 */
void ASSERT_TRUE(int condition, const char *test_name);

/**
 * @brief Ověření, že ukazatel je NULL.
 *
 * @param pointer Ukazatel, který má být zkontrolován.
 * @param test_name Název testu, který je prováděn.
 */
void ASSERT_NULL(void *pointer, const char *test_name);

/**
 * @brief Výpis souhrnu výsledků testů.
 */
void TEST_RESULT();

#endif // TEST_FRAMEWORK_H
