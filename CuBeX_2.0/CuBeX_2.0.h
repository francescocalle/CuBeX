#ifndef CuBe_X_2
#define CuBe_X_2
#include <Arduino.h>
#include<Wire.h>

//aggiorna le facce
void af_W(int CFW1,int CFW2,int CFW3,int CFW4,int CFW5,int CFW6,int CFW7,int CFW8);  //quì vanno inseriti i colori delle varie facce (no i centri)
void af_Y(int CFY1,int CFY2,int CFY3,int CFY4,int CFY5,int CFY6,int CFY7,int CFY8);
void af_G(int CFG1,int CFG2,int CFG3,int CFG4,int CFG5,int CFG6,int CFG7,int CFG8);
void af_B(int CFB1,int CFB2,int CFB3,int CFB4,int CFB5,int CFB6,int CFB7,int CFB8);
void af_R(int CFR1,int CFR2,int CFR3,int CFR4,int CFR5,int CFR6,int CFR7,int CFR8);
void af_O(int CFO1,int CFO2,int CFO3,int CFO4,int CFO5,int CFO6,int CFO7,int CFO8);

//restituizione valori
int mosse();                               //restituisce il numero di mosse
int errori();                              //restituisce il valore di errore (0 nessun errore)
int mossa(int nmnm);                       //restituisce un numero che sta ad indicare la mossa nella posizione del numero dato in ingresso
int tempo();                               //restituisce un numero che sta ad indicare il tempo in millisecondi impiegato per eseguire la risoluzione

//start processo
void start();                              //richiamando questa funzione verrà avviata la risoluzione

//funzioni per i servo
void servo_1(int pins1, int s1c, int s1a); //funzioni per creare i servomotori servo*(pin, angolo da chiuso, angolo da aperto);
void servo_2(int pins2, int s2c, int s2a);
void servo_3(int pins3, int s3c, int s3a);
void servo_4(int pins4, int s4c, int s4a);
void servo_op();                           //funzione per aprire i servo
void servo_cl();                           //funzione per chiudere i servo

//funzioni per gli stepper
void stepper_init(int sdapin, int sclpin, int adr1, int adr2, int adr3);                                   //funzione per inizializzare i motori stepper e i loro pin
void stepper_RPM(int speed);                                   //funzione per impostare la velocità dei motori
void stepper_LUN(int lunghezzamossa);                          //funzione per impostare gli step da fare per mossa (se negativa il motore gira in senso antiorario)
void step_U();                                                 //funzione per richiamare una determinata  mossa
void step_D();
void step_R();
void step_L();
void step_F();
void step_B();
void step_CUS();                                               //funzione per richiamare una mossa custom che muove U e D nel senso opposto

//funzioni aggiuntive
void MossaU();
void MossaU1();
void MossaD();
void MossaD1();
void MossaR();
void MossaR1();
void MossaL();
void MossaL1();
void MossaF();
void MossaF1();
void MossaB();
void MossaB1();
void risoluzione();
void semplificazione();
void movu();
void movd();
void movr();
void movl();
void movf();
void movb();
void aggexp();

#endif