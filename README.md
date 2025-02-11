//ITALIANO
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

//ENGLISH
this library is used to manage a machine that is able to solve the rubik's cube.

CuBeX.h is divided into 3 macro sections: 
 1 - it is able to provide the moves to perform to solve the cube by giving it input only the colors of the various faces of the cube; 
 2 - is able to manage 6 stepper motors (one per face of the cube), connected using 8bit I/O expanders; 
 3 - is able to manage 4 servos making them move simultaneously allowing us to open and close the 4 sides of the cube.

CuBeX.h is only compatible with:

- exp32;
- 8bit expander (I2C);
- 200 step nema 17 stepper (with their attached L298 driver);
- with any servomotor managed by PWM signal.
