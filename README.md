questa libreria serve per gestire una macchina che sia in grado di risolvere il cubo di rubik.

CuBeX.h è divisa in 3 macro sezioni:
1 - è in grado di fornire le mosse da eseguire per risolvere il cubo dandogli in ingresso solo i colori delle varie facce del cubo;
2 - è in grado di gestire 6 motori stepper (uno per faccia del  cubo), collegati utilizzando degli i/o expander a 8bit;
3 - è in grado di gestire 4 servo facendoli muovere in contemporanea permettendoci di aprire e chiudere i 4 lati del cubo.

CuBeX.h è compatibile solo con:
- esp32;
- expander a 8bit (I2C);
- stepper nema 17 da 200 passi (con il loro annesso driver L298);
- con qualsiasi servomotore gestito da segnale PWM.
