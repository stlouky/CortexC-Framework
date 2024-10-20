# C Application Development Framework

## Struktura projektu

```
c-framework/
│
├── src/
│   ├── logging.c
│   └── test_framework.c
│
├── include/
│   ├── logging.h
│   └── test_framework.h
│
├── examples/
│   └── example_usage.c
│
├── tests/
│   └── run_tests.c
│
├── docs/
│   └── API.md
│
├── .gitignore
├── LICENSE
├── README.md
└── Makefile
```

## README.md

```markdown
# C Application Development Framework

Tento framework poskytuje základní nástroje pro vývoj aplikací v jazyce C, včetně logovacího systému a testovacího frameworku.

## Funkce

- **Logovací systém**: Flexibilní systém pro logování zpráv s různými úrovněmi závažnosti.
- **Testovací framework**: Jednoduchý, ale účinný framework pro jednotkové testování.

## Instalace

1. Naklonujte repozitář:
   ```
   git clone https://github.com/yourusername/c-framework.git
   ```
2. Přejděte do adresáře projektu:
   ```
   cd c-framework
   ```
3. Sestavte projekt pomocí make:
   ```
   make
   ```

## Použití

### Logovací systém

```c
#include "logging.h"

int main() {
    set_log_file("application.log");
    LOG_INFO(__func__, "Aplikace spuštěna");
    // Váš kód zde
    LOG_INFO(__func__, "Aplikace ukončena");
    return 0;
}
```

### Testovací framework

```c
#include "test_framework.h"

void test_example() {
    ASSERT_TRUE(1 == 1, "1 se rovná 1");
    ASSERT_EQ(42, 42, "42 se rovná 42");
}

int main() {
    RUN_TEST(test_example, "Příklad testu");
    TEST_RESULT();
    return 0;
}
```

## Dokumentace

Podrobná dokumentace API je k dispozici v souboru [API.md](docs/API.md).

## Přispívání

Příspěvky jsou vítány! Prosím, přečtěte si [CONTRIBUTING.md](CONTRIBUTING.md) pro detaily o našem kodexu chování a procesu pro zasílání pull requestů.

## Licence

Tento projekt je licencován pod MIT licencí - viz soubor [LICENSE](LICENSE) pro detaily.

## Kontakt

Vaše Jméno - [@váš_twitter](https://twitter.com/váš_twitter) - email@example.com

Odkaz na projekt: [https://github.com/yourusername/c-framework](https://github.com/yourusername/c-framework)
```

Nezapomeňte upravit odkazy, uživatelská jména a kontaktní informace podle vašich potřeb.