queste 3 librerie servono per creare una macchina che sia in grado di risolvere il cubo di rubik.

CuBeX.h è in grado di fornire le mosse da eseguire per risolvere il cubo dandogli in ingresso solo i colori delle varie facce del cubo.
stepCuBeX.h invece è in grado di gestire 6 motori stepper (uno per faccia del  cubo), collegati utilizzando degli i/o expander a 8bit.
servoCuBeX.h invece è in grado di gestire 4servo facendoli muovere in contemporanea permettendoci di aprire e chiudere i 4 lati del cubo.
