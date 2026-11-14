//ITALIANO
questa libreria serve per gestire una macchina che sia in grado di risolvere il cubo di rubik.

CuBeX.h è divisa in 3 macro sezioni:
- 1 è in grado di fornire le mosse da eseguire per risolvere il cubo dandogli in ingresso solo i colori delle varie facce del cubo;
- 2 è in grado di gestire 6 motori stepper (uno per faccia del  cubo), collegati utilizzando degli i/o expander a 8bit;
- 3 è in grado di gestire 4 servo facendoli muovere in contemporanea permettendoci di aprire e chiudere i 4 lati del cubo.

CuBeX.h metodo di risoluzione cambiato tra versioni (test eseguiti equamente su 750 cubi):
- CuBeX_1.0:
  - Metodo utilizzato: Strati
  - Media delle mosse: ~136,70
  - Mosse minime:      ~72
  - Mosse massime:     ~198
  - Tempo di calcolo:  ~5ms
- CuBeX_2.0:
  - Metodo utilizzato: Strati - Fridrich 
  - Media delle mosse: ~87,37
  - Mosse minime:      ~48
  - Mosse massime:     ~114
  - Tempo di calcolo:  ~5ms
- CuBeX_3.0:
  - Metodo utilizzato: Kociemba a due fasi in RAM
  - Media delle mosse: ~20,86
  - Mosse minime:      ~17
  - Mosse massime:     ~23
  - Tempo di calcolo:  ~12,80s
- CuBeX_3.0_DualCore:
  - Metodo utilizzato:  Kociemba a due fasi in flash a 2 core (esp32 a 2 core)
  - Media delle mosse: ~19,87
  - Mosse minime:      ~16
  - Mosse massime:     ~22
  - Tempo di calcolo:  ~2,85s
- CuBeX_4.0:
  - In fase di elaborazione...

CuBeX.h è compatibile solo con:
- esp32;
- expander a 8bit (I2C);
- stepper nema 17 da 200 passi (con il loro annesso driver L298);
- con qualsiasi servomotore gestito da segnale PWM.

//ENGLISH
this library is used to manage a machine that is able to solve the rubik's cube.

CuBeX.h is divided into 3 macro sections: 
- 1 it is able to provide the moves to perform to solve the cube by giving it input only the colors of the various faces of the cube; 
- 2 is able to manage 6 stepper motors (one per face of the cube), connected using 8bit I/O expanders; 
- 3 is able to manage 4 servos making them move simultaneously allowing us to open and close the 4 sides of the cube.

CuBeX.h solving method changed across versions (tests performed fairly on 750 cubes):
- CuBeX_1.0:
  - Method used:      Layer-by-Layer
  - Average moves:    ~136.70
  - Minimum moves:    ~72
  - Maximum moves:    ~198
  - Computation time: ~5ms
- CuBeX_2.0:
  - Method used:      Layer-by-Layer – Fridrich
  - Average moves:    ~87.37
  - Minimum moves:    ~48
  - Maximum moves:    ~114
  - Computation time: ~5ms
- CuBeX_3.0:
  - Method used:      Two-Phase Kociemba in RAM
  - Average moves:    ~20.86
  - Minimum moves:    ~17
  - Maximum moves:    ~23
  - Computation time: ~12.80s
- CuBeX_3.0_DualCore:
  - Method used:      Two-Phase Kociemba in flash using 2 cores (dual-core ESP32)
  - Average moves:    ~19.87
  - Minimum moves:    ~16
  - Maximum moves:    ~22
  - Computation time: ~2.85s
- CuBeX_4.0:
  - Under development...

CuBeX.h is only compatible with:
- exp32;
- 8bit expander (I2C);
- 200 step nema 17 stepper (with their attached L298 driver);
- with any servomotor managed by PWM signal.
