# CuBeX

## 🇮🇹 Italiano

Questa libreria serve per gestire una macchina in grado di risolvere il cubo di Rubik.

### Cosa fa CuBeX.h

La libreria è divisa in tre macro-sezioni:

1. Fornisce le mosse da eseguire per risolvere il cubo, ricevendo in ingresso solo i colori delle varie facce.
2. Gestisce 6 motori stepper (uno per faccia del cubo), collegati tramite expander I/O a 8 bit.
3. Gestisce 4 servo facendoli muovere contemporaneamente, permettendo di aprire e chiudere i 4 lati del cubo.

### Evoluzione del metodo di risoluzione

Test eseguiti equamente su 750 cubi.

| Versione | Metodo utilizzato | Media delle mosse | Mosse minime | Mosse massime | Tempo di calcolo | Riduzione media delle mosse |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| **CuBeX_1.0** | Strati | ~136,70 | ~72 | ~198 | ~5ms | — |
| **CuBeX_2.0** | Strati - Fridrich | ~87,37 | ~48 | ~114 | ~5ms | +36,0% |
| **CuBeX_3.0** | Kociemba a due fasi in RAM | ~20,86 | ~17 | ~23 | ~12,80s | +76,1% |
| **CuBeX_3.0_DualCore** | Kociemba a due fasi in flash a 2 core (esp32 a 2 core) | ~19,87 | ~16 | ~22 | ~2,85s | +4,7% |
| **CuBeX_4.0** | In fase di elaborazione... | — | — | — | — | — |

### Compatibilità

CuBeX.h è compatibile solo con:

- ESP32;
- expander a 8 bit (I2C);
- stepper NEMA 17 da 200 passi (con il loro annesso driver L298);
- qualsiasi servomotore gestito da segnale PWM.

---

## 🇬🇧 English

This library is used to manage a machine that is able to solve the Rubik's Cube.

### What CuBeX.h does

CuBeX.h is divided into three macro sections:

1. It provides the moves to perform to solve the cube, taking as input only the colors of the various faces.
2. It manages 6 stepper motors (one per face of the cube), connected using 8-bit I/O expanders.
3. It manages 4 servos, making them move simultaneously and allowing us to open and close the 4 sides of the cube.

### Evolution of the solving method

Tests performed fairly on 750 cubes.

| Version | Method used | Average moves | Minimum moves | Maximum moves | Computation time | Average reduction in moves |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| **CuBeX_1.0** | Layer-by-Layer | ~136.70 | ~72 | ~198 | ~5ms | — |
| **CuBeX_2.0** | Layer-by-Layer – Fridrich | ~87.37 | ~48 | ~114 | ~5ms | +36.0% |
| **CuBeX_3.0** | Two-Phase Kociemba in RAM | ~20.86 | ~17 | ~23 | ~12.80s | +76.1% |
| **CuBeX_3.0_DualCore** | Two-Phase Kociemba in flash using 2 cores (dual-core ESP32) | ~19.87 | ~16 | ~22 | ~2.85s | +4.7% |
| **CuBeX_4.0** | Under development... | — | — | — | — | — |

### Compatibility

CuBeX.h is only compatible with:

- exp32;
- 8-bit expander (I2C);
- 200-step NEMA 17 stepper (with their attached L298 driver);
- any servomotor managed by PWM signal.
