#include<CuBeX.h>
const int w  = 1;  //assegno un numero ai colori
const int y  = 2;
const int g  = 3;
const int b  = 4;
const int r  = 5;
const int o  = 6;

int CFW[9] = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
int CFY[9] = { 0, 0, 0, 0, 2, 0, 0, 0, 0 };
int CFG[9] = { 0, 0, 0, 0, 3, 0, 0, 0, 0 };
int CFB[9] = { 0, 0, 0, 0, 4, 0, 0, 0, 0 };
int CFR[9] = { 0, 0, 0, 0, 5, 0, 0, 0, 0 };
int CFO[9] = { 0, 0, 0, 0, 6, 0, 0, 0, 0 };
int pa[25];    //in questo vettore vengono inseriti tutti i valori delle posizioni dei vari angoli seguendo un ordine prestabilito
int ps[25];    //in questo vettore vengono inseriti tutti i valori delle posizioni dei vari spigoli seguendo un ordine prestabilito
int sy[4];     //questo vettore serve per la risoluzione dell ultima faccia
int alg[255];  //questo vettore serve per tenere a mente le mosse da fare per la risoluzione
int mosse404, cambiamenti404, spazzola, bf, cicli,temp_init=0, primocolore, secondocolore, numero404notfound = 0, er404notfound = 0;  //variabili varie per eseguire il codice

//variabili per gli stepper
unsigned long t_init;
float tempostep = 5000;
int cicli1, SU=0, SD=0, SR=0, SL=0, SF=0, SB=0, lunghe=50, dir404=1;
int Upin1 = 1, Upin2 = 1, Upin3 = 1, Upin4 = 1;
int Dpin1 = 1, Dpin2 = 1, Dpin3 = 1, Dpin4 = 1;
int Rpin1 = 1, Rpin2 = 1, Rpin3 = 1, Rpin4 = 1;
int Lpin1 = 1, Lpin2 = 1, Lpin3 = 1, Lpin4 = 1;
int Fpin1 = 1, Fpin2 = 1, Fpin3 = 1, Fpin4 = 1;
int Bpin1 = 1, Bpin2 = 1, Bpin3 = 1, Bpin4 = 1;
int exp1, exr2, exp3;
int adrs1 = 0;
int adrs2 = 0;
int adrs3 = 0;

//variabili per i  servo
const int pwmmin = 1638;
const int pwmmax = 8190;
int ss1a, ss2a, ss3a, ss4a, ss1c, ss2c, ss3c, ss4c, pinss1, pinss2, pinss3, pinss4;

//aggiorna le facce
void af_W(int CFW1,int CFW2,int CFW3,int CFW4,int CFW5,int CFW6,int CFW7,int CFW8){  //quì vanno inseriti i colori delle varie facce (no i centri)
  CFW[0] =CFW1;
  CFW[1] =CFW2;
  CFW[2] =CFW3;
  CFW[3] =CFW4;
  CFW[5] =CFW5;
  CFW[6] =CFW6;
  CFW[7] =CFW7;
  CFW[8] =CFW8;
}
void af_Y(int CFY1,int CFY2,int CFY3,int CFY4,int CFY5,int CFY6,int CFY7,int CFY8){
  CFY[0] =CFY1;
  CFY[1] =CFY2;
  CFY[2] =CFY3;
  CFY[3] =CFY4;
  CFY[5] =CFY5;
  CFY[6] =CFY6;
  CFY[7] =CFY7;
  CFY[8] =CFY8;
}
void af_G(int CFG1,int CFG2,int CFG3,int CFG4,int CFG5,int CFG6,int CFG7,int CFG8){
  CFG[0] =CFG1;
  CFG[1] =CFG2;
  CFG[2] =CFG3;
  CFG[3] =CFG4;
  CFG[5] =CFG5;
  CFG[6] =CFG6;
  CFG[7] =CFG7;
  CFG[8] =CFG8;
}
void af_B(int CFB1,int CFB2,int CFB3,int CFB4,int CFB5,int CFB6,int CFB7,int CFB8){
  CFB[0] =CFB1;
  CFB[1] =CFB2;
  CFB[2] =CFB3;
  CFB[3] =CFB4;
  CFB[5] =CFB5;
  CFB[6] =CFB6;
  CFB[7] =CFB7;
  CFB[8] =CFB8;
}
void af_R(int CFR1,int CFR2,int CFR3,int CFR4,int CFR5,int CFR6,int CFR7,int CFR8){
  CFR[0] =CFR1;
  CFR[1] =CFR2;
  CFR[2] =CFR3;
  CFR[3] =CFR4;
  CFR[5] =CFR5;
  CFR[6] =CFR6;
  CFR[7] =CFR7;
  CFR[8] =CFR8;
}
void af_O(int CFO1,int CFO2,int CFO3,int CFO4,int CFO5,int CFO6,int CFO7,int CFO8){
  CFO[0] =CFO1;
  CFO[1] =CFO2;
  CFO[2] =CFO3;
  CFO[3] =CFO4;
  CFO[5] =CFO5;
  CFO[6] =CFO6;
  CFO[7] =CFO7;
  CFO[8] =CFO8;
}

//restituizione valori
int mosse(){                     //restituisce il numero di mosse
  return numero404notfound;
}
int errori(){                    //restituisce il valore di errore (0 nessun errore)
  return er404notfound;
}
int mossa(int nmnm){             //restituisce un numero che sta ad indicare la mossa nella posizione del numero dato in ingresso
  return alg[nmnm-1];
}
int tempo(){                     //restituisce un numero che sta ad indicare il tempo in millisecondi impiegato per eseguire la risoluzione
  return temp_init;
}

//start processo
void start(){                    //richiamando questa funzione verrà avviata la risoluzione
  temp_init=millis();
  for (cicli = 0; cicli <= 24; cicli++) {
    pa[cicli] = 0;
    ps[cicli] = 0;
  }
  risoluzione();
  semplificazione();
  for (cicli = 0; cicli <= 8; cicli++) {
  CFW[cicli] = 0;
  CFY[cicli] = 0;
  CFG[cicli] = 0;
  CFB[cicli] = 0;
  CFR[cicli] = 0;
  CFO[cicli] = 0;
  }
  CFW[4] = 1;
  CFY[4] = 2;
  CFG[4] = 3;
  CFB[4] = 4;
  CFR[4] = 5;
  CFO[4] = 6;
  temp_init=millis()-temp_init;
}
void semplificazione() {        //codice per la semplificazione
  do{
    cambiamenti404=0;
    for(cicli = 0; cicli <= numero404notfound; cicli++){
      for(mosse404 = 0; mosse404 <= 10; mosse404 = mosse404+2){
        if((alg[cicli]==1+mosse404&&alg[cicli+1]==2+mosse404)||(alg[cicli]==2+mosse404&&alg[cicli+1]==1+mosse404)){
          cambiamenti404=1;
          numero404notfound = numero404notfound-2;
          for(bf = cicli; bf <= numero404notfound; bf++){
            alg[bf] = alg[bf+2];
          }
        }
      }
      if(alg[cicli]==alg[cicli+1]&&alg[cicli+1]==alg[cicli+2]&&alg[cicli]>=1){
        cambiamenti404=1;
        numero404notfound = numero404notfound-3;
        for(mosse404 = 1; mosse404 <= 11; mosse404 = mosse404+2){
          if(alg[cicli]==mosse404){
            alg[cicli]=alg[cicli]+1;
          }
          if(alg[cicli]==mosse404+1){
            alg[cicli]=alg[cicli]-1;
          }
        }
        for(bf = cicli; bf <= numero404notfound; bf++){
          alg[bf+1] = alg[bf+3];
        }
      }
    }
  }while(cambiamenti404==1);
  for(cicli = 0; cicli <= numero404notfound; cicli++){
    if(alg[cicli]==alg[cicli+1]){
      if(alg[cicli]==1||alg[cicli+1]==2){
        numero404notfound = numero404notfound-1;
        for(bf = cicli; bf <= numero404notfound; bf++){
          alg[bf+1] = alg[bf+2];
        }
        alg[cicli]=13;
      }
      if(alg[cicli]==3||alg[cicli+1]==4){
        numero404notfound = numero404notfound-1;
        for(bf = cicli; bf <= numero404notfound; bf++){
          alg[bf+1] = alg[bf+2];
        }
        alg[cicli]=14;
      }
      if(alg[cicli]==5||alg[cicli+1]==6){
        numero404notfound = numero404notfound-1;
        for(bf = cicli; bf <= numero404notfound; bf++){
          alg[bf+1] = alg[bf+2];
        }
        alg[cicli]=15;
      }
      if(alg[cicli]==7||alg[cicli+1]==8){
        numero404notfound = numero404notfound-1;
        for(bf = cicli; bf <= numero404notfound; bf++){
          alg[bf+1] = alg[bf+2];
        }
        alg[cicli]=16;
      }
      if(alg[cicli]==9||alg[cicli+1]==10){
        numero404notfound = numero404notfound-1;
        for(bf = cicli; bf <= numero404notfound; bf++){
          alg[bf+1] = alg[bf+2];
        }
        alg[cicli]=17;
      }
      if(alg[cicli]==11||alg[cicli+1]==12){
        numero404notfound = numero404notfound-1;
        for(bf = cicli; bf <= numero404notfound; bf++){
          alg[bf+1] = alg[bf+2];
        }
        alg[cicli]=18;
      }
    }
  }
  for (cicli = numero404notfound+1; cicli <= 254; cicli++) {
    alg[cicli] = 0;
  }
}
void risoluzione() {
  numero404notfound = 0;
  er404notfound = 0;
  for (cicli = 0; cicli <= 254; cicli++) {
    alg[cicli] = 0;
  }
  for (cicli = 1; cicli <= 8; cicli++) {
    if (cicli == 1) {
      primocolore = w;
      secondocolore = g;
    }
    if (cicli == 2) {
      primocolore = w;
      secondocolore = r;
    }
    if (cicli == 3) {
      primocolore = w;
      secondocolore = b;
    }
    if (cicli == 4) {
      primocolore = w;
      secondocolore = o;
    }
    if (cicli == 5) {
      primocolore = y;
      secondocolore = r;
    }
    if (cicli == 6) {
      primocolore = y;
      secondocolore = b;
    }
    if (cicli == 7) {
      primocolore = y;
      secondocolore = o;
    }
    if (cicli == 8) {
      primocolore = y;
      secondocolore = g;
    }
    if (CFW[8] == primocolore && CFG[2] == secondocolore) {
      pa[1] = cicli;
    }
    if (CFW[2] == primocolore && CFR[2] == secondocolore) {
      pa[2] = cicli;
    }
    if (CFW[0] == primocolore && CFB[2] == secondocolore) {
      pa[3] = cicli;
    }
    if (CFW[6] == primocolore && CFO[2] == secondocolore) {
      pa[4] = cicli;
    }
    if (CFY[2] == primocolore && CFR[6] == secondocolore) {
      pa[5] = cicli;
    }
    if (CFY[8] == primocolore && CFB[6] == secondocolore) {
      pa[6] = cicli;
    }
    if (CFY[6] == primocolore && CFO[6] == secondocolore) {
      pa[7] = cicli;
    }
    if (CFY[0] == primocolore && CFG[6] == secondocolore) {
      pa[8] = cicli;
    }
    if (CFG[2] == primocolore && CFR[0] == secondocolore) {
      pa[9] = cicli;
    }
    if (CFB[0] == primocolore && CFW[2] == secondocolore) {
      pa[10] = cicli;
    }
    if (CFB[2] == primocolore && CFO[0] == secondocolore) {
      pa[11] = cicli;
    }
    if (CFG[0] == primocolore && CFW[6] == secondocolore) {
      pa[12] = cicli;
    }
    if (CFG[8] == primocolore && CFY[2] == secondocolore) {
      pa[13] = cicli;
    }
    if (CFB[6] == primocolore && CFR[8] == secondocolore) {
      pa[14] = cicli;
    }
    if (CFB[8] == primocolore && CFY[6] == secondocolore) {
      pa[15] = cicli;
    }
    if (CFG[6] == primocolore && CFO[8] == secondocolore) {
      pa[16] = cicli;
    }
    if (CFR[0] == primocolore && CFW[8] == secondocolore) {
      pa[17] = cicli;
    }
    if (CFR[2] == primocolore && CFB[0] == secondocolore) {
      pa[18] = cicli;
    }
    if (CFO[0] == primocolore && CFW[0] == secondocolore) {
      pa[19] = cicli;
    }
    if (CFO[2] == primocolore && CFG[0] == secondocolore) {
      pa[20] = cicli;
    }
    if (CFR[6] == primocolore && CFG[8] == secondocolore) {
      pa[21] = cicli;
    }
    if (CFR[8] == primocolore && CFY[8] == secondocolore) {
      pa[22] = cicli;
    }
    if (CFO[6] == primocolore && CFB[8] == secondocolore) {
      pa[23] = cicli;
    }
    if (CFO[8] == primocolore && CFY[0] == secondocolore) {
      pa[24] = cicli;
    }
  }
  for (cicli = 1; cicli <= 12; cicli++) {
    if (cicli == 1) {
      primocolore = w;
      secondocolore = g;
    }
    if (cicli == 2) {
      primocolore = w;
      secondocolore = r;
    }
    if (cicli == 3) {
      primocolore = w;
      secondocolore = b;
    }
    if (cicli == 4) {
      primocolore = w;
      secondocolore = o;
    }
    if (cicli == 5) {
      primocolore = g;
      secondocolore = r;
    }
    if (cicli == 6) {
      primocolore = b;
      secondocolore = r;
    }
    if (cicli == 7) {
      primocolore = b;
      secondocolore = o;
    }
    if (cicli == 8) {
      primocolore = g;
      secondocolore = o;
    }
    if (cicli == 9) {
      primocolore = y;
      secondocolore = g;
    }
    if (cicli == 10) {
      primocolore = y;
      secondocolore = r;
    }
    if (cicli == 11) {
      primocolore = y;
      secondocolore = b;
    }
    if (cicli == 12) {
      primocolore = y;
      secondocolore = o;
    }
    if (CFW[7] == primocolore && CFG[1] == secondocolore) {
      ps[1] = cicli;
    }
    if (CFW[5] == primocolore && CFR[1] == secondocolore) {
      ps[2] = cicli;
    }
    if (CFW[1] == primocolore && CFB[1] == secondocolore) {
      ps[3] = cicli;
    }
    if (CFW[3] == primocolore && CFO[1] == secondocolore) {
      ps[4] = cicli;
    }
    if (CFG[5] == primocolore && CFR[3] == secondocolore) {
      ps[5] = cicli;
    }
    if (CFB[3] == primocolore && CFR[5] == secondocolore) {
      ps[6] = cicli;
    }
    if (CFB[5] == primocolore && CFO[3] == secondocolore) {
      ps[7] = cicli;
    }
    if (CFG[3] == primocolore && CFO[5] == secondocolore) {
      ps[8] = cicli;
    }
    if (CFY[1] == primocolore && CFG[7] == secondocolore) {
      ps[9] = cicli;
    }
    if (CFY[5] == primocolore && CFR[7] == secondocolore) {
      ps[10] = cicli;
    }
    if (CFY[7] == primocolore && CFB[7] == secondocolore) {
      ps[11] = cicli;
    }
    if (CFY[3] == primocolore && CFO[7] == secondocolore) {
      ps[12] = cicli;
    }
    if (CFW[7] == secondocolore && CFG[1] == primocolore) {
      ps[13] = cicli;
    }
    if (CFW[5] == secondocolore && CFR[1] == primocolore) {
      ps[14] = cicli;
    }
    if (CFW[1] == secondocolore && CFB[1] == primocolore) {
      ps[15] = cicli;
    }
    if (CFW[3] == secondocolore && CFO[1] == primocolore) {
      ps[16] = cicli;
    }
    if (CFG[5] == secondocolore && CFR[3] == primocolore) {
      ps[17] = cicli;
    }
    if (CFB[3] == secondocolore && CFR[5] == primocolore) {
      ps[18] = cicli;
    }
    if (CFB[5] == secondocolore && CFO[3] == primocolore) {
      ps[19] = cicli;
    }
    if (CFG[3] == secondocolore && CFO[5] == primocolore) {
      ps[20] = cicli;
    }
    if (CFY[1] == secondocolore && CFG[7] == primocolore) {
      ps[21] = cicli;
    }
    if (CFY[5] == secondocolore && CFR[7] == primocolore) {
      ps[22] = cicli;
    }
    if (CFY[7] == secondocolore && CFB[7] == primocolore) {
      ps[23] = cicli;
    }
    if (CFY[3] == secondocolore && CFO[7] == primocolore) {
      ps[24] = cicli;
    }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 1 (bianco-verde) all'interno del cubo
  while (ps[spazzola] != 1) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 1:
      break;
    case 2:
      //mosse da fare:U
      MossaU();
      break;
    case 3:
      //mosse da fare:U,U
      MossaU();
      MossaU();
      break;
    case 4:
      //mosse da fare:U1
      MossaU1();
      break;
    case 5:
      //mosse da fare:R,U
      MossaR();
      MossaU();
      break;
    case 6:
      //mosse da fare:R1,U
      MossaR1();
      MossaU();
      break;
    case 7:
      //mosse da fare:L,U1
      MossaL();
      MossaU1();
      break;
    case 8:
      //mosse da fare:L1,U1
      MossaL1();
      MossaU1();
      break;
    case 9:
      //mosse da fare:F,F
      MossaF();
      MossaF();
      break;
    case 10:
      //mosse da fare:D1,F,F
      MossaD1();
      MossaF();
      MossaF();
      break;
    case 11:
      //mosse da fare:D,D,F,F
      MossaD();
      MossaD();
      MossaF();
      MossaF();
      break;
    case 12:
      //mosse da fare:D,F,F
      MossaD();
      MossaF();
      MossaF();
      break;
    case 13:
      //mosse da fare:F,R,U
      MossaF();
      MossaR();
      MossaU();
      break;
    case 14:
      //mosse da fare:R1,F1
      MossaR1();
      MossaF1();
      break;
    case 15:
      //mosse da fare:U,R1,F1
      MossaU();
      MossaR1();
      MossaF1();
      break;
    case 16:
      //mosse da fare:L,F
      MossaL();
      MossaF();
      break;
    case 17:
      //mosse da fare:F1
      MossaF1();
      break;
    case 18:
      //mosse da fare:R,R,F1
      MossaR();
      MossaR();
      MossaF1();
      break;
    case 19:
      //mosse da fare:L,L,F
      MossaL();
      MossaL();
      MossaF();
      break;
    case 20:
      //mosse da fare:F
      MossaF();
      break;
    case 21:
      //mosse da fare:F1,R,U
      MossaF1();
      MossaR();
      MossaU();
      break;
    case 22:
      //mosse da fare:R,F1
      MossaR();
      MossaF1();
      break;
    case 23:
      //mosse da fare:D1,R,F1
      MossaD1();
      MossaR();
      MossaF1();
      break;
    case 24:
      //mosse da fare:L1,F
      MossaL1();
      MossaF();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 1;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 2 (bianco-rosso) all'interno del cubo
  while (ps[spazzola] != 2) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 2:
      break;
    case 3:
      //mosse da fare:B1,U1,B,U
      MossaB1();
      MossaU1();
      MossaB();
      MossaU();
      break;
    case 4:
      //mosse da fare:F,U,U,F1
      MossaF();
      MossaU();
      MossaU();
      MossaF1();
      break;
    case 5:
      //mosse da fare:R
      MossaR();
      break;
    case 6:
      //mosse da fare:R1
      MossaR1();
      break;
    case 7:
      //mosse da fare:B,B,R1
      MossaB();
      MossaB();
      MossaR1();
      break;
    case 8:
      //mosse da fare:U,U,L1,U,U
      MossaU();
      MossaU();
      MossaL1();
      MossaU();
      MossaU();
      break;
    case 9:
      //mosse da fare:D,R,R
      MossaD();
      MossaR();
      MossaR();
      break;
    case 10:
      //mosse da fare:R,R
      MossaR();
      MossaR();
      break;
    case 11:
      //mosse da fare:D1,R,R
      MossaD1();
      MossaR();
      MossaR();
      break;
    case 12:
      //mosse da fare:D,D,R,R
      MossaD();
      MossaD();
      MossaR();
      MossaR();
      break;
    case 14:
      //mosse da fare:R,U1,B,U
      MossaR();
      MossaU1();
      MossaB();
      MossaU();
      break;
    case 15:
      //mosse da fare:B1,R1
      MossaB1();
      MossaR1();
      break;
    case 16:
      //mosse da fare:L,U,F,U1
      MossaL();
      MossaU();
      MossaF();
      MossaU1();
      break;
    case 17:
      //mosse da fare:U,F1,U1
      MossaU();
      MossaF1();
      MossaU1();
      break;
    case 18:
      //mosse da fare:U1,B,U
      MossaU1();
      MossaB();
      MossaU();
      break;
    case 19:
      //mosse da fare:U1,B1,U
      MossaU1();
      MossaB1();
      MossaU();
      break;
    case 20:
      //mosse da fare:U,F,U1
      MossaU();
      MossaF();
      MossaU1();
      break;
    case 21:
      //mosse da fare:F1,R,F
      MossaF1();
      MossaR();
      MossaF();
      break;
    case 22:
      //mosse da fare:D,B,R1
      MossaD();
      MossaB();
      MossaR1();
      break;
    case 23:
      //mosse da fare:B,R1
      MossaB();
      MossaR1();
      break;
    case 24:
      //mosse da fare:D1,B,R1
      MossaD1();
      MossaB();
      MossaR1();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 2;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 3 (bianco-blu) all'interno del cubo
  while (ps[spazzola] != 3) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 3:
      break;
    case 4:
      //mosse da fare:L,U1,L1,U
      MossaL();
      MossaU1();
      MossaL1();
      MossaU();
      break;
    case 5:
      //mosse da fare:U,R,U1
      MossaU();
      MossaR();
      MossaU1();
      break;
    case 6:
      //mosse da fare:U,R1,U1
      MossaU();
      MossaR1();
      MossaU1();
      break;
    case 7:
      //mosse da fare:U1,L,U
      MossaU1();
      MossaL();
      MossaU();
      break;
    case 8:
      //mosse da fare:U1,L1,U
      MossaU1();
      MossaL1();
      MossaU();
      break;
    case 9:
      //mosse da fare:D,D,B,B
      MossaD();
      MossaD();
      MossaB();
      MossaB();
      break;
    case 10:
      //mosse da fare:D,B,B
      MossaD();
      MossaB();
      MossaB();
      break;
    case 11:
      //mosse da fare:B,B
      MossaB();
      MossaB();
      break;
    case 12:
      //mosse da fare:D1,B,B
      MossaD1();
      MossaB();
      MossaB();
      break;
    case 15:
      //mosse da fare:B,U1,L,U
      MossaB();
      MossaU1();
      MossaL();
      MossaU();
      break;
    case 16:
      //mosse da fare:L1,B1
      MossaL1();
      MossaB1();
      break;
    case 17:
      //mosse da fare:U,U,F1,U,U
      MossaU();
      MossaU();
      MossaF1();
      MossaU();
      MossaU();
      break;
    case 18:
      //mosse da fare:B
      MossaB();
      break;
    case 19:
      //mosse da fare:B1
      MossaB1();
      break;
    case 20:
      //mosse da fareL,L,B1
      MossaL();
      MossaL();
      MossaB1();
      break;
    case 21:
      //mosse da fare:D1,L,B1
      MossaD1();
      MossaL();
      MossaB1();
      break;
    case 22:
      //mosse da fare:R1,B,R
      MossaR1();
      MossaB();
      MossaR();
      break;
    case 23:
      //mosse da fare:B1,U1,L,U
      MossaB1();
      MossaU1();
      MossaL();
      MossaU();
      break;
    case 24:
      //mosse da fare:L,B1
      MossaL();
      MossaB1();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 3;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 4 (bianco-arancione) all'interno del cubo
  while (ps[spazzola] != 4) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 4:
      break;
    case 5:
      //mosse da fare:U,U,R,U,U
      MossaU();
      MossaU();
      MossaR();
      MossaU();
      MossaU();
      break;
    case 6:
      //mosse da fare:U,U,R1,U,U
      MossaU();
      MossaU();
      MossaR1();
      MossaU();
      MossaU();
      break;
    case 7:
      //mosse da fare:L
      MossaL();
      break;
    case 8:
      //mosse da fare:L1
      MossaL1();
      break;
    case 9:
      //mosse da fare:D1,L,L
      MossaD1();
      MossaL();
      MossaL();
      break;
    case 10:
      //mosse da fare:D,D,L,L
      MossaD();
      MossaD();
      MossaL();
      MossaL();
      break;
    case 11:
      //mosse da fare:D,L,L
      MossaD();
      MossaL();
      MossaL();
      break;
    case 12:
      //mosse da fare:L,L
      MossaL();
      MossaL();
      break;
    case 16:
      //mosse da fare:L,U1,F,U
      MossaL();
      MossaU1();
      MossaF();
      MossaU();
      break;
    case 17:
      //mosse da fare:U1,F1,U
      MossaU1();
      MossaF1();
      MossaU();
      break;
    case 18:
      //mosse da fare:U,B,U1
      MossaU();
      MossaB();
      MossaU1();
      break;
    case 19:
      //mosse da fare:U,B1,U1
      MossaU();
      MossaB1();
      MossaU1();
      break;
    case 20:
      //mosse da fare:U1,F,U
      MossaU1();
      MossaF();
      MossaU();
      break;
    case 21:
      //mosse da fare:F,L1,F1
      MossaF();
      MossaL1();
      MossaF1();
      break;
    case 22:
      //mosse da fare:D1,F,L1,F1
      MossaD1();
      MossaF();
      MossaL1();
      MossaF1();
      break;
    case 23:
      //mosse da fare:B1,L,B
      MossaB1();
      MossaL();
      MossaB();
      break;
      break;
    case 24:
      //mosse da fare:D1,B1,L,B
      MossaD1();
      MossaB1();
      MossaL();
      MossaB();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 4;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare l'angolo 1 (bianco-verde-rosso) all'interno del cubo
  while (pa[spazzola] != 1) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 1:
      break;
    case 2:
      //mosse da fare:B1,D,B,F,D1,F1
      MossaB1();
      MossaD();
      MossaB();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 3:
      //mosse da fare:B,D,D,B1,R1,D1,R
      MossaB();
      MossaD();
      MossaD();
      MossaB1();
      MossaR1();
      MossaD1();
      MossaR();
      break;
    case 4:
      //mosse da fare:F1,D1,F,R1,D,D,R
      MossaF1();
      MossaD1();
      MossaF();
      MossaR1();
      MossaD();
      MossaD();
      MossaR();
      break;
    case 5:
      //mosse da fare:F,D1,F1,R1,D,D,R
      MossaF();
      MossaD1();
      MossaF1();
      MossaR1();
      MossaD();
      MossaD();
      MossaR();
      break;
    case 6:
      //mosse da fare:R,D1,R,R,D,R
      MossaR();
      MossaD1();
      MossaR();
      MossaR();
      MossaD();
      MossaR();
      break;
    case 7:
      //mosse da fare:D1,R,D1,R,R,D,R
      MossaD1();
      MossaR();
      MossaD1();
      MossaR();
      MossaR();
      MossaD();
      MossaR();
      break;
    case 8:
      //mosse da fare:F1,D,F,F,D1,F1
      MossaF1();
      MossaD();
      MossaF();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 9:
      //mosse da fare:R1,D,R,D1,R1,D,R
      MossaR1();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 10:
      //mosse da fare:B1,F,D1,B,F1
      MossaB1();
      MossaF();
      MossaD1();
      MossaB();
      MossaF1();
      break;
    case 11:
      //mosse da fare:B,R1,D,D,B1,R
      MossaB();
      MossaR1();
      MossaD();
      MossaD();
      MossaB1();
      MossaR();
      break;
    case 12:
      //mosse da fare:L,D1,L1,D,R1,D1,R
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaR1();
      MossaD1();
      MossaR();
      break;
    case 13:
      //mosse da fare:D1,R1,D,R
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 14:
      //mosse da fare:F,D1,F1
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 15:
      //mosse da fare:R1,D,D,R
      MossaR1();
      MossaD();
      MossaD();
      MossaR();
      break;
    case 16:
      //mosse da fare:D,R1,D1,R
      MossaD();
      MossaR1();
      MossaD1();
      MossaR();
      break;
    case 17:
      //mosse da fare:R1,D1,R,D,R1,D1,R
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaR1();
      MossaD1();
      MossaR();
      break;
    case 18:
      //mosse da fare:R,D,R,R,D,D,R
      MossaR();
      MossaD();
      MossaR();
      MossaR();
      MossaD();
      MossaD();
      MossaR();
      break;
    case 19:
      //mosse da fare:B,D1,B1,F,D,D,F1
      MossaB();
      MossaD1();
      MossaB1();
      MossaF();
      MossaD();
      MossaD();
      MossaF1();
      break;
    case 20:
      //mosse da fare:F1,D,F,R1,D,R
      MossaF1();
      MossaD();
      MossaF();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 21:
      //mosse da fare:R1,D1,R
      MossaR1();
      MossaD1();
      MossaR();
      break;
    case 22:
      //mosse da fare:D,D,R1,D,R
      MossaD();
      MossaD();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 23:
      //mosse da fare:F,D,D,F1
      MossaF();
      MossaD();
      MossaD();
      MossaF1();
      break;
      break;
    case 24:
      //mosse da fare:R1,D,R
      MossaR1();
      MossaD();
      MossaR();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 5;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare l'angolo 2 (bianco-blu-rosso) all'interno del cubo
  while (pa[spazzola] != 2) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 2:
      break;
    case 3:
      //mosse da fare:L1,D,L,R,D1,R1
      MossaL1();
      MossaD();
      MossaL();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 4:
      //mosse da fare:L,R,D,D,L1,R1
      MossaL();
      MossaR();
      MossaD();
      MossaD();
      MossaL1();
      MossaR1();
      break;
    case 5:
      //mosse da fare:D,R,D1,R1,B1,D,D,B
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaB1();
      MossaD();
      MossaD();
      MossaB();
      break;
    case 6:
      //mosse da fare:B1,D,B,R,D,D,R1
      MossaB1();
      MossaD();
      MossaB();
      MossaR();
      MossaD();
      MossaD();
      MossaR1();
      break;
    case 7:
      //mosse da fare:B,D1,B,B,D,B
      MossaB();
      MossaD1();
      MossaB();
      MossaB();
      MossaD();
      MossaB();
      break;
    case 8:
      //mosse da fare:D1,B,D1,B,B,D,B
      MossaD1();
      MossaB();
      MossaD1();
      MossaB();
      MossaB();
      MossaD();
      MossaB();
      break;
    case 10:
      //mosse da fare:R,D1,R1,D,R,D1,R1
      MossaR();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 11:
      //mosse da fare:B,D,B,B,D,D,B
      MossaB();
      MossaD();
      MossaB();
      MossaB();
      MossaD();
      MossaD();
      MossaB();
      break;
    case 12:
      //mosse da fare:F1,R,D,D,R1,F
      MossaF1();
      MossaR();
      MossaD();
      MossaD();
      MossaR1();
      MossaF();
      break;
    case 13:
      //mosse da fare:B1,D,B
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 14:
      //mosse da fare:D,R,D1,R1
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 15:
      //mosse da fare:D,D,B1,D,B
      MossaD();
      MossaD();
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 16:
      //mosse da fare:R,D,D,R1
      MossaR();
      MossaD();
      MossaD();
      MossaR1();
      break;
    case 18:
      //mosse da fare:B1,D,B,D1,B1,D,B
      MossaB1();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 19:
      //mosse da fare:L1,R,D1,L,R1
      MossaL1();
      MossaR();
      MossaD1();
      MossaL();
      MossaR1();
      break;
    case 20:
      //mosse da fare:L,B1,D,D,L1,B
      MossaL();
      MossaB1();
      MossaD();
      MossaD();
      MossaL1();
      MossaB();
      break;
    case 21:
      //mosse da fare:D,B1,D1,B
      MossaD();
      MossaB1();
      MossaD1();
      MossaB();
      break;
    case 22:
      //mosse da fare:R,D,R1
      MossaR();
      MossaD();
      MossaR1();
      break;
    case 23:
      //mosse da fare:R,D1,R1
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 24:
      //mosse da fare:B1,D,D,B
      MossaB1();
      MossaD();
      MossaD();
      MossaB();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 6;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare l'angolo 3 (bianco-blu-arancione) all'interno del cubo
  while (pa[spazzola] != 3) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 3:
      break;
    case 4:
      //mosse da fare:F1,D,F,B,D1,B1
      MossaF1();
      MossaD();
      MossaF();
      MossaB();
      MossaD1();
      MossaB1();
      break;
    case 5:
      //mosse da fare:D1,L,D1,L,L,D,L
      MossaD1();
      MossaL();
      MossaD1();
      MossaL();
      MossaL();
      MossaD();
      MossaL();
      break;
    case 6:
      //mosse da fare:D,D,L,D1,L,L,D,L
      MossaD();
      MossaD();
      MossaL();
      MossaD1();
      MossaL();
      MossaL();
      MossaD();
      MossaL();
      break;
    case 7:
      //mosse da fare:D,L,D1,L,L,D,L
      MossaD();
      MossaL();
      MossaD1();
      MossaL();
      MossaL();
      MossaD();
      MossaL();
      break;
    case 8:
      //mosse da fare:L,D1,L,L,D,L
      MossaL();
      MossaD1();
      MossaL();
      MossaL();
      MossaD();
      MossaL();
      break;
    case 11:
      //mosse da fare:L1,D,L,D1,L1,D,L
      MossaL1();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 12:
      //mosse da fare:F1,B,D1,F,B1
      MossaF1();
      MossaB();
      MossaD1();
      MossaF();
      MossaB1();
      break;
    case 13:
      //mosse da fare:L1,D,D,L
      MossaL1();
      MossaD();
      MossaD();
      MossaL();
      break;
    case 14:
      //mosse da fare:D1,B,D,D,B1
      MossaD1();
      MossaB();
      MossaD();
      MossaD();
      MossaB1();
      break;
    case 15:
      //mosse da fare:B,D,B1
      MossaB();
      MossaD();
      MossaB1();
      break;
    case 16:
      //mosse da fare:B,D1,B1
      MossaB();
      MossaD1();
      MossaB1();
      break;
    case 19:
      //mosse da fare:B,D1,B1,D,B,D1,B1
      MossaB();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      break;
    case 20:
      //mosse da fare:L,D,L,L,D,D,L
      MossaL();
      MossaD();
      MossaL();
      MossaL();
      MossaD();
      MossaD();
      MossaL();
      break;
    case 21:
      //mosse da fare:B,D,D,B1
      MossaB();
      MossaD();
      MossaD();
      MossaB1();
      break;
    case 22:
      //mosse da fare:L1,D,L
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 23:
      //mosse da fare:L1,D1,L
      MossaL1();
      MossaD1();
      MossaL();
      break;
    case 24:
      //mosse da fare:D1,B,D,B1
      MossaD1();
      MossaB();
      MossaD();
      MossaB1();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 7;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare l'angolo 4 (bianco-verde-arancione) all'interno del cubo
  while (pa[spazzola] != 4) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 4:
      break;
    case 5:
      //mosse da fare:D1,L,D1,L1,F1,D,D,F
      MossaD1();
      MossaL();
      MossaD1();
      MossaL1();
      MossaF1();
      MossaD();
      MossaD();
      MossaF();
      break;
    case 6:
      //mosse da fare:D,D,L,D1,L1,F1,D,D,F
      MossaD();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaF1();
      MossaD();
      MossaD();
      MossaF();
      break;
    case 7:
      //mosse da fare:D,L,D1,L1,F1,D,D,F
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaF1();
      MossaD();
      MossaD();
      MossaF();
      break;
    case 8:
      //mosse da fare:L,D1,L1,F1,D,D,F
      MossaL();
      MossaD1();
      MossaL1();
      MossaF1();
      MossaD();
      MossaD();
      MossaF();
      break;
    case 12:
      //mosse da fare:L,D1,L1,F1,D1,F
      MossaL();
      MossaD1();
      MossaL1();
      MossaF1();
      MossaD1();
      MossaF();
      break;
    case 13:
      //mosse da fare:D1,L,D,L1
      MossaD1();
      MossaL();
      MossaD();
      MossaL1();
      break;
    case 14:
      //mosse da fare:L,D,D,L1
      MossaL();
      MossaD();
      MossaD();
      MossaL1();
      break;
    case 15:
      //mosse da fare:F1,D,F
      MossaF1();
      MossaD();
      MossaF();
      break;
    case 16:
      //mosse da fare:F1,D1,F
      MossaF1();
      MossaD1();
      MossaF();
      break;
    case 20:
      //mosse da fare:F1,D,F,L,D,L1
      MossaF1();
      MossaD();
      MossaF();
      MossaL();
      MossaD();
      MossaL1();
      break;
    case 21:
      //mosse da fare:L,D1,L1
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 22:
      //mosse da fare:F1,D,D,F
      MossaF1();
      MossaD();
      MossaD();
      MossaF();
      break;
    case 23:
      //mosse da fare:D,F1,D1,F
      MossaD();
      MossaF1();
      MossaD1();
      MossaF();
      break;
    case 24:
      //mosse da fare:L,D,L1
      MossaL();
      MossaD();
      MossaL1();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 8;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 5 (verde-rosso) all'interno del cubo
  while (ps[spazzola] != 5) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 5:
      break;
    case 6:
      //mosse da fare:D,R,D1,R1,D1,B1,D,B,D,D,F,D1,F1,D1,R1,D,R
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 7:
      //mosse da fare:D1,L1,D,L,D,B,D1,B1,D,D,F,D1,F1,D1,R1,D,R
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 8:
      //mosse da fare:D,L,D1,L1,D1,F1,D,F,F,D1,F1,D1,R1,D,R
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaF1();
      MossaD();
      MossaF();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 9:
      //mosse da fare:D,D,F,D1,F1,D1,R1,D,R
      MossaD();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 10:
      //mosse da fare:D,F,D1,F1,D1,R1,D,R
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 11:
      //mosse da fare:F,D1,F1,D1,R1,D,R
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 12:
      //mosse da fare:D1,F,D1,F1,D1,R1,D,R
      MossaD1();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 17:
      //mosse da fare:F,D1,F1,D1,R1,D,R,D1,F,D1,F1,D1,R1,D,R
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD1();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 18:
      //mosse da fare:R,D1,R1,D1,B1,D,B,D1,R1,D,R,D,F,D1,F1
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 19:
      //mosse da fare:L1,D,L,D,B,D1,B1,D1,R1,D,R,D,F,D1,F1
      MossaL1();
      MossaD();
      MossaL();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 20:
      //mosse da fare:F1,D,F,D,L,D1,L1,D,F,D1,F1,D1,R1,D,R
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 21:
      //mosse da fare:D1,R1,D,R,D,F,D1,F1
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 22:
      //mosse da fare:D,D,R1,D,R,D,F,D1,F1
      MossaD();
      MossaD();
      MossaR1();
      MossaD();
      MossaR();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 23:
      //mosse da fare:D,R1,D,R,D,F,D1,F1
      MossaD();
      MossaR1();
      MossaD();
      MossaR();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    case 24:
      //mosse da fare:R1,D,R,D,F,D1,F1
      MossaR1();
      MossaD();
      MossaR();
      MossaD();
      MossaF();
      MossaD1();
      MossaF1();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 9;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 6 (blu-rosso) all'interno del cubo
  while (ps[spazzola] != 6) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 6:
      break;
    case 7:
      //mosse da fare:B,D1,B1,D1,L1,D,L,D,D,R,D1,R1,D1,B1,D,B
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      MossaD();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 8:
      //mosse da fare:F1,D,F,D,L,D1,L1,D,D,R,D1,R1,D1,B1,D,B
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 9:
      //mosse da fare:B1,D,B,D,R,D1,R1
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 10:
      //mosse da fare:D1,B1,D,B,D,R,D1,R1
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 11:
      //mosse da fare:D,D,B1,D,B,D,R,D1,R1
      MossaD();
      MossaD();
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 12:
      //mosse da fare:D,B1,D,B,D,R,D1,R1
      MossaD();
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 18:
      //mosse da fare:B1,D,B,D,R,D1,R1,D,B1,D,B,D,R,D1,R1
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD();
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 19:
      //mosse da fare:B,D1,B1,D1,L1,D,L,D1,B1,D,B,D,R,D1,R1
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 20:
      //mosse da fare:F1,D,F,D,L,D1,L1,D1,B1,D,B,D,R,D1,R1
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      break;
    case 21:
      //mosse da fare:D1,R,D1,R1,D1,B1,D,B
      MossaD1();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 22:
      //mosse da fare:D,D,R,D1,R1,D1,B1,D,B
      MossaD();
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 23:
      //mosse da fare:D,R,D1,R1,D1,B1,D,B
      MossaD();
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      break;
    case 24:
      //mosse da fare:R,D1,R1,D1,B1,D,B
      MossaR();
      MossaD1();
      MossaR1();
      MossaD1();
      MossaB1();
      MossaD();
      MossaB();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 10;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 7 (blu-arancione) all'interno del cubo
  while (ps[spazzola] != 7) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 7:
      break;
    case 8:
      //mosse da fare:L,D1,L1,D1,F1,D,F,D,D,B,D1,B1,D1,L1,D,L
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 9:
      //mosse da fare:B,D1,B1,D1,L1,D,L
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 10:
      //mosse da fare:D1,B,D1,B1,D1,L1,D,L
      MossaD1();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 11:
      //mosse da fare:D,D,B,D1,B1,D1,L1,D,L
      MossaD();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 12:
      //mosse da fare:D,B,D1,B1,D1,L1,D,L
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 19:
      //mosse da fare:B,D1,B1,D1,L1,D,L,D1,B,D1,B1,D1,L1,D,L
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      MossaD1();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 20:
      //mosse da fare:F1,D,F,D,L,D1,L1,D1,B,D1,B1,D1,L1,D,L
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaB();
      MossaD1();
      MossaB1();
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      break;
    case 21:
      //mosse da fare:D,L1,D,L,D,B,D1,B1
      MossaD();
      MossaL1();
      MossaD();
      MossaL();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      break;
    case 22:
      //mosse da fare:L1,D,L,D,B,D1,B1
      MossaL1();
      MossaD();
      MossaL();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      break;
    case 23:
      //mosse da fare:D1,L1,D,L,D,B,D1,B1
      MossaD1();
      MossaL1();
      MossaD();
      MossaL();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      break;
    case 24:
      //mosse da fare:D,D,L1,D,L,D,B,D1,B1
      MossaD();
      MossaD();
      MossaL1();
      MossaD();
      MossaL();
      MossaD();
      MossaB();
      MossaD1();
      MossaB1();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 11;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 8 (verde-arancione) all'interno del cubo
  while (ps[spazzola] != 8) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 8:
      break;
    case 9:
      //mosse da fare:D,D,F1,D,F,D,L,D1,L1
      MossaD();
      MossaD();
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 10:
      //mosse da fare:D,F1,D,F,D,L,D1,L1
      MossaD();
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 11:
      //mosse da fare:F1,D,F,D,L,D1,L1
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 12:
      //mosse da fare:D1,F1,D,F,D,L,D1,L1
      MossaD1();
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 20:
      //mosse da fare:F1,D,F,D,L,D1,L1,D,F1,D,F,D,L,D1,L1
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaF1();
      MossaD();
      MossaF();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 21:
      //mosse da fare:D,L,D1,L1,D1,F1,D,F
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaF1();
      MossaD();
      MossaF();
      break;
    case 22:
      //mosse da fare:L,D1,L1,D1,F1,D,F
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaF1();
      MossaD();
      MossaF();
      break;
    case 23:
      //mosse da fare:D1,L,D1,L1,D1,F1,D,F
      MossaD1();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaF1();
      MossaD();
      MossaF();
      break;
    case 24:
      //mosse da fare:D,D,L,D1,L1,D1,F1,D,F
      MossaD();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaF1();
      MossaD();
      MossaF();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 12;
      }
  }
  sy[0] = 0;
  sy[1] = 0;
  sy[2] = 0;
  sy[3] = 0;
  if (ps[9] == 9 || ps[9] == 10 || ps[9] == 11 || ps[9] == 12) {
    sy[0] = 1;
  }
  if (ps[10] == 9 || ps[10] == 10 || ps[10] == 11 || ps[10] == 12) {
    sy[1] = 1;
  }
  if (ps[11] == 9 || ps[11] == 10 || ps[11] == 11 || ps[11] == 12) {
    sy[2] = 1;
  }
  if (ps[12] == 9 || ps[12] == 10 || ps[12] == 11 || ps[12] == 12) {
    sy[3] = 1;
  }
  if (sy[0] == 0 && sy[1] == 0 && sy[2] == 0 && sy[3] == 0) {
    //mosse da fare:F1,D1,R1,D,R,D1,R1,D,R,F,B1,D1,L1,D,L,B
    MossaF1();
    MossaD1();
    MossaR1();
    MossaD();
    MossaR();
    MossaD1();
    MossaR1();
    MossaD();
    MossaR();
    MossaF();
    MossaB1();
    MossaD1();
    MossaL1();
    MossaD();
    MossaL();
    MossaB();
  }
  if (sy[0] == 1 && sy[1] == 1 && sy[2] == 0 && sy[3] == 0) {
    //mosse da fare:B1,D1,L1,D,L,B
    MossaB1();
    MossaD1();
    MossaL1();
    MossaD();
    MossaL();
    MossaB();
  }
  if (sy[0] == 0 && sy[1] == 1 && sy[2] == 1 && sy[3] == 0) {
    //mosse da fare:D1,B1,D1,L1,D,L,B
    MossaD1();
    MossaB1();
    MossaD1();
    MossaL1();
    MossaD();
    MossaL();
    MossaB();
  }
  if (sy[0] == 0 && sy[1] == 0 && sy[2] == 1 && sy[3] == 1) {
    //mosse da fare:D,D,B1,D1,L1,D,L,B
    MossaD();
    MossaD();
    MossaB1();
    MossaD1();
    MossaL1();
    MossaD();
    MossaL();
    MossaB();
  }
  if (sy[0] == 1 && sy[1] == 0 && sy[2] == 0 && sy[3] == 1) {
    //mosse da fare:D,B1,D1,L1,D,L,B
    MossaD();
    MossaB1();
    MossaD1();
    MossaL1();
    MossaD();
    MossaL();
    MossaB();
  }
  if (sy[0] == 1 && sy[1] == 0 && sy[2] == 1 && sy[3] == 0) {
    //mosse da fare:D,F1,D1,R1,D,R,D1,R1,D,R,F
    MossaD();
    MossaF1();
    MossaD1();
    MossaR1();
    MossaD();
    MossaR();
    MossaD1();
    MossaR1();
    MossaD();
    MossaR();
    MossaF();
  }
  if (sy[0] == 0 && sy[1] == 1 && sy[2] == 0 && sy[3] == 1) {
    //mosse da fare:F1,D1,R1,D,R,D1,R1,D,R,F
    MossaF1();
    MossaD1();
    MossaR1();
    MossaD();
    MossaR();
    MossaD1();
    MossaR1();
    MossaD();
    MossaR();
    MossaF();
  }
  if (sy[0] + sy[1] + sy[2] + sy[3] == 1 || sy[0] + sy[1] + sy[2] + sy[3] == 3) {
    if (er404notfound == 0) {
      er404notfound = 13;
    }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 9 (verde-giallo) all'interno del cubo
  while (ps[spazzola] != 9) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 9:
      break;
    case 10:
      //mosse da fare:D1
      MossaD1();
      break;
    case 11:
      //mosse da fare:D,D
      MossaD();
      MossaD();
      break;
    case 12:
      //mosse da fare:D
      MossaD();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 14;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 11 (blu-giallo) all'interno del cubo
  while (ps[spazzola] != 11) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 10:
      //mosse da fare:L,L,R,R,U1,L1,R,B,B,L,R1,U1,L,L,R,R
      MossaL();
      MossaL();
      MossaR();
      MossaR();
      MossaU1();
      MossaL1();
      MossaR();
      MossaB();
      MossaB();
      MossaL();
      MossaR1();
      MossaU1();
      MossaL();
      MossaL();
      MossaR();
      MossaR();
      break;
    case 11:
      break;
    case 12:
      //mosse da fare:L,L,R,R,U,L1,R,B,B,L,R1,U,L,L,R,R
      MossaL();
      MossaL();
      MossaR();
      MossaR();
      MossaU();
      MossaL1();
      MossaR();
      MossaB();
      MossaB();
      MossaL();
      MossaR1();
      MossaU();
      MossaL();
      MossaL();
      MossaR();
      MossaR();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 15;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare lo spigolo 10 (arancione-giallo) all'interno del cubo
  while (ps[spazzola] != 12) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 10:
      //mosse da fare:L,D,L1,D1,L1,F,L,L,D1,L1,D1,L,D,L1,F1
      MossaL();
      MossaD();
      MossaL1();
      MossaD1();
      MossaL1();
      MossaF();
      MossaL();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD1();
      MossaL();
      MossaD();
      MossaL1();
      MossaF1();
      break;
    case 12:
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 16;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare l'angolo 5 (verde-rosso-giallo) all'interno del cubo
  while (pa[spazzola] != 5) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 5:
      break;
    case 13:
      break;
    case 21:
      break;
    case 6:
      //mosse da fare:D,L,R1,D1,R,D,L1,D1,R1,D,R,D1
      MossaD();
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD1();
      break;
    case 14:
      //mosse da fare:D,L,R1,D1,R,D,L1,D1,R1,D,R,D1
      MossaD();
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD1();
      break;
    case 22:
      //mosse da fare:D,L,R1,D1,R,D,L1,D1,R1,D,R,D1
      MossaD();
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      MossaD1();
      break;
    case 7:
      //mosse da fare:L,R1,D,L1,D1,R,D,L,D,L1
      MossaL();
      MossaR1();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 15:
      //mosse da fare:L,R1,D,L1,D1,R,D,L,D,L1
      MossaL();
      MossaR1();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 23:
      //mosse da fare:L,R1,D,L1,D1,R,D,L,D,L1
      MossaL();
      MossaR1();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      break;
    case 8:
      //mosse da fare:D,D,L,R1,D,L1,D1,R,D,L,D,L1,D,D
      MossaD();
      MossaD();
      MossaL();
      MossaR1();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaD();
      break;
    case 16:
      //mosse da fare:D,D,L,R1,D,L1,D1,R,D,L,D,L1,D,D
      MossaD();
      MossaD();
      MossaL();
      MossaR1();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaD();
      break;
    case 24:
      //mosse da fare:D,D,L,R1,D,L1,D1,R,D,L,D,L1,D,D
      MossaD();
      MossaD();
      MossaL();
      MossaR1();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL();
      MossaD1();
      MossaL1();
      MossaD();
      MossaD();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 17;
      }
  }
  spazzola = 1;  //questo while ci consente di trovare l'angolo 6 (blu-rosso-giallo) all'interno del cubo
  while (pa[spazzola] != 6) {
    spazzola = spazzola + 1;
  }
  switch (spazzola) {
    case 6:
      break;
    case 14:
      break;
    case 22:
      break;
    case 7:
      //mosse da fare:L,R1,D1,R,D,L1,D1,R1,D,R
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 15:
      //mosse da fare:L,R1,D1,R,D,L1,D1,R1,D,R
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 23:
      //mosse da fare:L,R1,D1,R,D,L1,D1,R1,D,R
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 8:
      //mosse da fare:L,R1,D1,R,D,L1,D1,R1,D,L,D1,R,D,L1,D1,R1,D,R
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaL();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 16:
      //mosse da fare:L,R1,D1,R,D,L1,D1,R1,D,L,D1,R,D,L1,D1,R1,D,R
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaL();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    case 24:
      //mosse da fare:L,R1,D1,R,D,L1,D1,R1,D,L,D1,R,D,L1,D1,R1,D,R
      MossaL();
      MossaR1();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaL();
      MossaD1();
      MossaR();
      MossaD();
      MossaL1();
      MossaD1();
      MossaR1();
      MossaD();
      MossaR();
      break;
    default:
      if (er404notfound == 0) {
        er404notfound = 18;
      }
  }
  if (pa[5] == 0 || pa[6] == 0 || pa[7] == 0 || pa[8] == 0) {
    for (cicli = 0; cicli <= 3; cicli++) {
      if (pa[5] == 0) {
        MossaR();
        MossaU();
        MossaR1();
        MossaU1();
        MossaR();
        MossaU();
        MossaR1();
        MossaU1();
        if (pa[5] == 0) {
          MossaR();
          MossaU();
          MossaR1();
          MossaU1();
          MossaR();
          MossaU();
          MossaR1();
          MossaU1();
        }
      }
      MossaD1();
    }
  }
  for (cicli = 1; cicli <= 12; cicli++) {
    if (ps[cicli] != cicli) {
      if (er404notfound == 0) {
        er404notfound = 19;
      }
    }
  }
  for (cicli = 1; cicli <= 8; cicli++) {
    if (pa[cicli] != cicli) {
      if (er404notfound == 0) {
        er404notfound = 20;
      }
    }
  }
}
void MossaU() {
  alg[numero404notfound] = 1;
  numero404notfound = numero404notfound + 1;
  bf = ps[4];  //muovo gli spigoli dritti
  ps[4] = 0;
  ps[4] = ps[1];
  ps[1] = 0;
  ps[1] = ps[2];
  ps[2] = 0;
  ps[2] = ps[3];
  ps[3] = 0;
  ps[3] = bf;

  bf = ps[16];  //muovo gli spigoli invertiti
  ps[16] = 0;
  ps[16] = ps[13];
  ps[13] = 0;
  ps[13] = ps[14];
  ps[14] = 0;
  ps[14] = ps[15];
  ps[15] = 0;
  ps[15] = bf;

  bf = pa[4];  //muovo gli angoli
  pa[4] = 0;
  pa[4] = pa[1];
  pa[1] = 0;
  pa[1] = pa[2];
  pa[2] = 0;
  pa[2] = pa[3];
  pa[3] = 0;
  pa[3] = bf;

  bf = pa[12];
  pa[12] = 0;
  pa[12] = pa[17];
  pa[17] = 0;
  pa[17] = pa[10];
  pa[10] = 0;
  pa[10] = pa[19];
  pa[19] = 0;
  pa[19] = bf;

  bf = pa[20];
  pa[20] = 0;
  pa[20] = pa[9];
  pa[9] = 0;
  pa[9] = pa[18];
  pa[18] = 0;
  pa[18] = pa[11];
  pa[11] = 0;
  pa[11] = bf;
}
void MossaU1() {
  alg[numero404notfound] = 2;
  numero404notfound = numero404notfound + 1;
  bf = ps[1];  //muovo gli spigoli dritti
  ps[1] = 0;
  ps[1] = ps[4];
  ps[4] = 0;
  ps[4] = ps[3];
  ps[3] = 0;
  ps[3] = ps[2];
  ps[2] = 0;
  ps[2] = bf;

  bf = ps[13];  //muovo gli spigoli invertiti
  ps[13] = 0;
  ps[13] = ps[16];
  ps[16] = 0;
  ps[16] = ps[15];
  ps[15] = 0;
  ps[15] = ps[14];
  ps[14] = 0;
  ps[14] = bf;

  bf = pa[1];  //muovo gli angoli
  pa[1] = 0;
  pa[1] = pa[4];
  pa[4] = 0;
  pa[4] = pa[3];
  pa[3] = 0;
  pa[3] = pa[2];
  pa[2] = 0;
  pa[2] = bf;

  bf = pa[10];
  pa[10] = 0;
  pa[10] = pa[17];
  pa[17] = 0;
  pa[17] = pa[12];
  pa[12] = 0;
  pa[12] = pa[19];
  pa[19] = 0;
  pa[19] = bf;

  bf = pa[18];
  pa[18] = 0;
  pa[18] = pa[9];
  pa[9] = 0;
  pa[9] = pa[20];
  pa[20] = 0;
  pa[20] = pa[11];
  pa[11] = 0;
  pa[11] = bf;
}
void MossaD() {
  alg[numero404notfound] = 3;
  numero404notfound = numero404notfound + 1;
  bf = ps[9];  //muovo gli spigoli dritti
  ps[9] = 0;
  ps[9] = ps[12];
  ps[12] = 0;
  ps[12] = ps[11];
  ps[11] = 0;
  ps[11] = ps[10];
  ps[10] = 0;
  ps[10] = bf;

  bf = ps[21];  //muovo gli spigoli invertiti
  ps[21] = 0;
  ps[21] = ps[24];
  ps[24] = 0;
  ps[24] = ps[23];
  ps[23] = 0;
  ps[23] = ps[22];
  ps[22] = 0;
  ps[22] = bf;

  bf = pa[5];  //muovo gli angoli
  pa[5] = 0;
  pa[5] = pa[8];
  pa[8] = 0;
  pa[8] = pa[7];
  pa[7] = 0;
  pa[7] = pa[6];
  pa[6] = 0;
  pa[6] = bf;

  bf = pa[22];
  pa[22] = 0;
  pa[22] = pa[13];
  pa[13] = 0;
  pa[13] = pa[24];
  pa[24] = 0;
  pa[24] = pa[15];
  pa[15] = 0;
  pa[15] = bf;

  bf = pa[14];
  pa[14] = 0;
  pa[14] = pa[21];
  pa[21] = 0;
  pa[21] = pa[16];
  pa[16] = 0;
  pa[16] = pa[23];
  pa[23] = 0;
  pa[23] = bf;
}
void MossaD1() {
  alg[numero404notfound] = 4;
  numero404notfound = numero404notfound + 1;
  bf = ps[12];  //muovo gli spigoli dritti
  ps[12] = 0;
  ps[12] = ps[9];
  ps[9] = 0;
  ps[9] = ps[10];
  ps[10] = 0;
  ps[10] = ps[11];
  ps[11] = 0;
  ps[11] = bf;

  bf = ps[24];  //muovo gli spigoli invertiti
  ps[24] = 0;
  ps[24] = ps[21];
  ps[21] = 0;
  ps[21] = ps[22];
  ps[22] = 0;
  ps[22] = ps[23];
  ps[23] = 0;
  ps[23] = bf;

  bf = pa[8];  //muovo gli angoli
  pa[8] = 0;
  pa[8] = pa[5];
  pa[5] = 0;
  pa[5] = pa[6];
  pa[6] = 0;
  pa[6] = pa[7];
  pa[7] = 0;
  pa[7] = bf;

  bf = pa[24];
  pa[24] = 0;
  pa[24] = pa[13];
  pa[13] = 0;
  pa[13] = pa[22];
  pa[22] = 0;
  pa[22] = pa[15];
  pa[15] = 0;
  pa[15] = bf;

  bf = pa[16];
  pa[16] = 0;
  pa[16] = pa[21];
  pa[21] = 0;
  pa[21] = pa[14];
  pa[14] = 0;
  pa[14] = pa[23];
  pa[23] = 0;
  pa[23] = bf;
}
void MossaR() {
  alg[numero404notfound] = 5;
  numero404notfound = numero404notfound + 1;
  bf = ps[6];  //muovo gli spigoli dritti
  ps[6] = 0;
  ps[6] = ps[2];
  ps[2] = 0;
  ps[2] = ps[5];
  ps[5] = 0;
  ps[5] = ps[10];
  ps[10] = 0;
  ps[10] = bf;

  bf = ps[18];  //muovo gli spigoli invertiti
  ps[18] = 0;
  ps[18] = ps[14];
  ps[14] = 0;
  ps[14] = ps[17];
  ps[17] = 0;
  ps[17] = ps[22];
  ps[22] = 0;
  ps[22] = bf;

  bf = pa[10];  //muovo gli angoli
  pa[10] = 0;
  pa[10] = pa[1];
  pa[1] = 0;
  pa[1] = pa[13];
  pa[13] = 0;
  pa[13] = pa[6];
  pa[6] = 0;
  pa[6] = bf;

  bf = pa[14];
  pa[14] = 0;
  pa[14] = pa[2];
  pa[2] = 0;
  pa[2] = pa[9];
  pa[9] = 0;
  pa[9] = pa[5];
  pa[5] = 0;
  pa[5] = bf;

  bf = pa[18];
  pa[18] = 0;
  pa[18] = pa[17];
  pa[17] = 0;
  pa[17] = pa[21];
  pa[21] = 0;
  pa[21] = pa[22];
  pa[22] = 0;
  pa[22] = bf;
}
void MossaR1() {
  alg[numero404notfound] = 6;
  numero404notfound = numero404notfound + 1;
  bf = ps[5];  //muovo gli spigoli dritti
  ps[5] = 0;
  ps[5] = ps[2];
  ps[2] = 0;
  ps[2] = ps[6];
  ps[6] = 0;
  ps[6] = ps[10];
  ps[10] = 0;
  ps[10] = bf;

  bf = ps[17];  //muovo gli spigoli invertiti
  ps[17] = 0;
  ps[17] = ps[14];
  ps[14] = 0;
  ps[14] = ps[18];
  ps[18] = 0;
  ps[18] = ps[22];
  ps[22] = 0;
  ps[22] = bf;

  bf = pa[13];  //muovo gli angoli
  pa[13] = 0;
  pa[13] = pa[1];
  pa[1] = 0;
  pa[1] = pa[10];
  pa[10] = 0;
  pa[10] = pa[6];
  pa[6] = 0;
  pa[6] = bf;

  bf = pa[5];
  pa[5] = 0;
  pa[5] = pa[9];
  pa[9] = 0;
  pa[9] = pa[2];
  pa[2] = 0;
  pa[2] = pa[14];
  pa[14] = 0;
  pa[14] = bf;

  bf = pa[21];
  pa[21] = 0;
  pa[21] = pa[17];
  pa[17] = 0;
  pa[17] = pa[18];
  pa[18] = 0;
  pa[18] = pa[22];
  pa[22] = 0;
  pa[22] = bf;
}
void MossaL() {
  alg[numero404notfound] = 7;
  numero404notfound = numero404notfound + 1;
  bf = ps[8];  //muovo gli spigoli dritti
  ps[8] = 0;
  ps[8] = ps[4];
  ps[4] = 0;
  ps[4] = ps[7];
  ps[7] = 0;
  ps[7] = ps[12];
  ps[12] = 0;
  ps[12] = bf;

  bf = ps[20];  //muovo gli spigoli invertiti
  ps[20] = 0;
  ps[20] = ps[16];
  ps[16] = 0;
  ps[16] = ps[19];
  ps[19] = 0;
  ps[19] = ps[24];
  ps[24] = 0;
  ps[24] = bf;

  bf = pa[8];  //muovo gli angoli
  pa[8] = 0;
  pa[8] = pa[12];
  pa[12] = 0;
  pa[12] = pa[3];
  pa[3] = 0;
  pa[3] = pa[15];
  pa[15] = 0;
  pa[15] = bf;

  bf = pa[16];
  pa[16] = 0;
  pa[16] = pa[4];
  pa[4] = 0;
  pa[4] = pa[11];
  pa[11] = 0;
  pa[11] = pa[7];
  pa[7] = 0;
  pa[7] = bf;

  bf = pa[24];
  pa[24] = 0;
  pa[24] = pa[20];
  pa[20] = 0;
  pa[20] = pa[19];
  pa[19] = 0;
  pa[19] = pa[23];
  pa[23] = 0;
  pa[23] = bf;
}
void MossaL1() {
  alg[numero404notfound] = 8;
  numero404notfound = numero404notfound + 1;
  bf = ps[7];  //muovo gli spigoli dritti
  ps[7] = 0;
  ps[7] = ps[4];
  ps[4] = 0;
  ps[4] = ps[8];
  ps[8] = 0;
  ps[8] = ps[12];
  ps[12] = 0;
  ps[12] = bf;

  bf = ps[16];  //muovo gli spigoli invertiti
  ps[16] = 0;
  ps[16] = ps[20];
  ps[20] = 0;
  ps[20] = ps[24];
  ps[24] = 0;
  ps[24] = ps[19];
  ps[19] = 0;
  ps[19] = bf;

  bf = pa[3];  //muovo gli angoli
  pa[3] = 0;
  pa[3] = pa[12];
  pa[12] = 0;
  pa[12] = pa[8];
  pa[8] = 0;
  pa[8] = pa[15];
  pa[15] = 0;
  pa[15] = bf;

  bf = pa[11];
  pa[11] = 0;
  pa[11] = pa[4];
  pa[4] = 0;
  pa[4] = pa[16];
  pa[16] = 0;
  pa[16] = pa[7];
  pa[7] = 0;
  pa[7] = bf;

  bf = pa[19];
  pa[19] = 0;
  pa[19] = pa[20];
  pa[20] = 0;
  pa[20] = pa[24];
  pa[24] = 0;
  pa[24] = pa[23];
  pa[23] = 0;
  pa[23] = bf;
}
void MossaF() {
  alg[numero404notfound] = 9;
  numero404notfound = numero404notfound + 1;
  bf = ps[17];  //muovo gli spigoli dritti
  ps[17] = 0;
  ps[17] = ps[1];
  ps[1] = 0;
  ps[1] = ps[20];
  ps[20] = 0;
  ps[20] = ps[9];
  ps[9] = 0;
  ps[9] = bf;

  bf = ps[5];  //muovo gli spigoli invertiti
  ps[5] = 0;
  ps[5] = ps[13];
  ps[13] = 0;
  ps[13] = ps[8];
  ps[8] = 0;
  ps[8] = ps[21];
  ps[21] = 0;
  ps[21] = bf;

  bf = pa[21];  //muovo gli angoli
  pa[21] = 0;
  pa[21] = pa[1];
  pa[1] = 0;
  pa[1] = pa[20];
  pa[20] = 0;
  pa[20] = pa[8];
  pa[8] = 0;
  pa[8] = bf;

  bf = pa[5];
  pa[5] = 0;
  pa[5] = pa[17];
  pa[17] = 0;
  pa[17] = pa[4];
  pa[4] = 0;
  pa[4] = pa[24];
  pa[24] = 0;
  pa[24] = bf;

  bf = pa[13];
  pa[13] = 0;
  pa[13] = pa[9];
  pa[9] = 0;
  pa[9] = pa[12];
  pa[12] = 0;
  pa[12] = pa[16];
  pa[16] = 0;
  pa[16] = bf;
}
void MossaF1() {
  alg[numero404notfound] = 10;
  numero404notfound = numero404notfound + 1;
  bf = ps[20];  //muovo gli spigoli dritti
  ps[20] = 0;
  ps[20] = ps[1];
  ps[1] = 0;
  ps[1] = ps[17];
  ps[17] = 0;
  ps[17] = ps[9];
  ps[9] = 0;
  ps[9] = bf;

  bf = ps[8];  //muovo gli spigoli invertiti
  ps[8] = 0;
  ps[8] = ps[13];
  ps[13] = 0;
  ps[13] = ps[5];
  ps[5] = 0;
  ps[5] = ps[21];
  ps[21] = 0;
  ps[21] = bf;

  bf = pa[20];  //muovo gli angoli
  pa[20] = 0;
  pa[20] = pa[1];
  pa[1] = 0;
  pa[1] = pa[21];
  pa[21] = 0;
  pa[21] = pa[8];
  pa[8] = 0;
  pa[8] = bf;

  bf = pa[4];
  pa[4] = 0;
  pa[4] = pa[17];
  pa[17] = 0;
  pa[17] = pa[5];
  pa[5] = 0;
  pa[5] = pa[24];
  pa[24] = 0;
  pa[24] = bf;

  bf = pa[12];
  pa[12] = 0;
  pa[12] = pa[9];
  pa[9] = 0;
  pa[9] = pa[13];
  pa[13] = 0;
  pa[13] = pa[16];
  pa[16] = 0;
  pa[16] = bf;
}
void MossaB() {
  alg[numero404notfound] = 11;
  numero404notfound = numero404notfound + 1;
  bf = ps[19];  //muovo gli spigoli dritti
  ps[19] = 0;
  ps[19] = ps[3];
  ps[3] = 0;
  ps[3] = ps[18];
  ps[18] = 0;
  ps[18] = ps[11];
  ps[11] = 0;
  ps[11] = bf;

  bf = ps[7];  //muovo gli spigoli invertiti
  ps[7] = 0;
  ps[7] = ps[15];
  ps[15] = 0;
  ps[15] = ps[6];
  ps[6] = 0;
  ps[6] = ps[23];
  ps[23] = 0;
  ps[23] = bf;

  bf = pa[19];  //muovo gli angoli
  pa[19] = 0;
  pa[19] = pa[2];
  pa[2] = 0;
  pa[2] = pa[22];
  pa[22] = 0;
  pa[22] = pa[7];
  pa[7] = 0;
  pa[7] = bf;

  bf = pa[3];
  pa[3] = 0;
  pa[3] = pa[18];
  pa[18] = 0;
  pa[18] = pa[6];
  pa[6] = 0;
  pa[6] = pa[23];
  pa[23] = 0;
  pa[23] = bf;

  bf = pa[11];
  pa[11] = 0;
  pa[11] = pa[10];
  pa[10] = 0;
  pa[10] = pa[14];
  pa[14] = 0;
  pa[14] = pa[15];
  pa[15] = 0;
  pa[15] = bf;
}
void MossaB1() {
  alg[numero404notfound] = 12;
  numero404notfound = numero404notfound + 1;
  bf = ps[18];  //muovo gli spigoli dritti
  ps[18] = 0;
  ps[18] = ps[3];
  ps[3] = 0;
  ps[3] = ps[19];
  ps[19] = 0;
  ps[19] = ps[11];
  ps[11] = 0;
  ps[11] = bf;

  bf = ps[6];  //muovo gli spigoli invertiti
  ps[6] = 0;
  ps[6] = ps[15];
  ps[15] = 0;
  ps[15] = ps[7];
  ps[7] = 0;
  ps[7] = ps[23];
  ps[23] = 0;
  ps[23] = bf;

  bf = pa[22];  //muovo gli angoli
  pa[22] = 0;
  pa[22] = pa[2];
  pa[2] = 0;
  pa[2] = pa[19];
  pa[19] = 0;
  pa[19] = pa[7];
  pa[7] = 0;
  pa[7] = bf;

  bf = pa[6];
  pa[6] = 0;
  pa[6] = pa[18];
  pa[18] = 0;
  pa[18] = pa[3];
  pa[3] = 0;
  pa[3] = pa[23];
  pa[23] = 0;
  pa[23] = bf;

  bf = pa[14];
  pa[14] = 0;
  pa[14] = pa[10];
  pa[10] = 0;
  pa[10] = pa[11];
  pa[11] = 0;
  pa[11] = pa[15];
  pa[15] = 0;
  pa[15] = bf;
}

//funzioni per gli stepper
void stepper_init(int sdapin, int sclpin, int adr1, int adr2, int adr3){    //funzione per inizializzare i motori stepper e i loro pin
  adrs1 = adr1,
  Wire.begin(sdapin, sclpin);
  Wire.beginTransmission(adrs1);
  Wire.write((byte)0b11111111);
  Wire.endTransmission();
  adrs2 = adr2,
  Wire.beginTransmission(adrs2);
  Wire.write((byte)0b11111111);
  Wire.endTransmission();
  adrs3 = adr3,
  Wire.beginTransmission(adrs3);
  Wire.write((byte)0b11111111);
  Wire.endTransmission();
}
void stepper_RPM(int speed){                            //funzione per impostare la velocità dei motori
  tempostep = 300000 / speed;
}
void stepper_LUN(int lunghezzamossa){                   //funzione per impostare gli step da fare per mossa
  lunghe = lunghezzamossa;
  if(lunghe > 0){
    dir404=1;
  }else if(lunghe < 0){
    dir404=0;
  }else{
    dir404=2;
  }

}
void step_U(){                                                 //funzione per richiamare una determinata  mossa
  if(dir404==1){
    t_init = micros();
    for(cicli1=1; cicli1<=lunghe; cicli1++){
      SU++;
      if(SU > 3){
        SU=0;
      }
      movu();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  if(dir404==0){
    t_init = micros();
    
    for(cicli1=-1; cicli1>=lunghe; cicli1--){
      SU--;
      if(SU < 0){
        SU=3;
      }
      movu();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  Upin1 = 1;
  Upin2 = 1;
  Upin3 = 1;
  Upin4 = 1;
  aggexp();
}
void step_D(){
  if(dir404==1){
    t_init = micros();
    for(cicli1=1; cicli1<=lunghe; cicli1++){
      SD++;
      if(SD > 3){
        SD=0;
      }
      movd();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  if(dir404==0){
    t_init = micros();
    
    for(cicli1=-1; cicli1>=lunghe; cicli1--){
      SD--;
      if(SD < 0){
        SD=3;
      }
      movd();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  Dpin1 = 1;
  Dpin2 = 1;
  Dpin3 = 1;
  Dpin4 = 1;
  aggexp();
}
void step_R(){
  if(dir404==1){
    t_init = micros();
    for(cicli1=1; cicli1<=lunghe; cicli1++){
      SR++;
      if(SR > 3){
        SR=0;
      }
      movr();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  if(dir404==0){
    t_init = micros();
    
    for(cicli1=-1; cicli1>=lunghe; cicli1--){
      SR--;
      if(SR < 0){
        SR=3;
      }
      movr();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  Rpin1 = 1;
  Rpin2 = 1;
  Rpin3 = 1;
  Rpin4 = 1;
  aggexp();
}
void step_L(){
  if(dir404==1){
    t_init = micros();
    for(cicli1=1; cicli1<=lunghe; cicli1++){
      SL++;
      if(SL > 3){
        SL=0;
      }
      movl();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  if(dir404==0){
    t_init = micros();
    
    for(cicli1=-1; cicli1>=lunghe; cicli1--){
      SL--;
      if(SL < 0){
        SL=3;
      }
      movl();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  Lpin1 = 1;
  Lpin2 = 1;
  Lpin3 = 1;
  Lpin4 = 1;
  aggexp();
}
void step_F(){
  if(dir404==1){
    t_init = micros();
    for(cicli1=1; cicli1<=lunghe; cicli1++){
      SF++;
      if(SF > 3){
        SF=0;
      }
      movf();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  if(dir404==0){
    t_init = micros();
    
    for(cicli1=-1; cicli1>=lunghe; cicli1--){
      SF--;
      if(SF < 0){
        SF=3;
      }
      movf();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  Fpin1 = 1;
  Fpin2 = 1;
  Fpin3 = 1;
  Fpin4 = 1;
  aggexp();
}
void step_B(){
  if(dir404==1){
    t_init = micros();
    for(cicli1=1; cicli1<=lunghe; cicli1++){
      SB++;
      if(SB > 3){
        SB=0;
      }
      movb();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  if(dir404==0){
    t_init = micros();
    
    for(cicli1=-1; cicli1>=lunghe; cicli1--){
      SB--;
      if(SB < 0){
        SB=3;
      }
      movb();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  Bpin1 = 1;
  Bpin2 = 1;
  Bpin3 = 1;
  Bpin4 = 1;
  aggexp();
}
void step_CUS(){                                               //funzione per richiamare una mossa custom che muove U e D nel senso opposto
  if(dir404==1){
    t_init = micros();
    for(cicli1=1; cicli1<=lunghe; cicli1++){
      SU++;
      if(SU > 3){
        SU=0;
      }
      SD--;
      if(SD < 0){
        SD=3;
      }
      movu();
      movd();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  if(dir404==0){
    t_init = micros();
    
    for(cicli1=-1; cicli1>=lunghe; cicli1--){
      SU--;
      if(SU < 0){
        SU=3;
      }
      SD++;
      if(SD > 3){
        SD=0;
      }
      movu();
      movd();
      aggexp();
      while(micros() - t_init <= tempostep){}
      t_init = micros();
    }
  }
  Upin1 = 1;
  Upin2 = 1;
  Upin3 = 1;
  Upin4 = 1;
  Dpin1 = 1;
  Dpin2 = 1;
  Dpin3 = 1;
  Dpin4 = 1;
  aggexp();
}
void movu(){
  if(SU==0){
    Upin1 = 0;
    Upin2 = 1;
    Upin3 = 0;
    Upin4 = 1;
  }
  if(SU==1){
    Upin1 = 1;
    Upin2 = 0;
    Upin3 = 0;
    Upin4 = 1;
  }
  if(SU==2){
    Upin1 = 1;
    Upin2 = 0;
    Upin3 = 1;
    Upin4 = 0;
  }
  if(SU==3){
    Upin1 = 0;
    Upin2 = 1;
    Upin3 = 1;
    Upin4 = 0;
  }
}
void movd(){
  if(SD==0){
    Dpin1 = 0;
    Dpin2 = 1;
    Dpin3 = 0;
    Dpin4 = 1;
  }
  if(SD==1){
    Dpin1 = 1;
    Dpin2 = 0;
    Dpin3 = 0;
    Dpin4 = 1;
  }
  if(SD==2){
    Dpin1 = 1;
    Dpin2 = 0;
    Dpin3 = 1;
    Dpin4 = 0;
  }
  if(SD==3){
    Dpin1 = 0;
    Dpin2 = 1;
    Dpin3 = 1;
    Dpin4 = 0;
  }
}
void movr(){
  if(SR==0){
    Rpin1 = 0;
    Rpin2 = 1;
    Rpin3 = 0;
    Rpin4 = 1;
  }
  if(SR==1){
    Rpin1 = 1;
    Rpin2 = 0;
    Rpin3 = 0;
    Rpin4 = 1;
  }
  if(SR==2){
    Rpin1 = 1;
    Rpin2 = 0;
    Rpin3 = 1;
    Rpin4 = 0;
  }
  if(SR==3){
    Rpin1 = 0;
    Rpin2 = 1;
    Rpin3 = 1;
    Rpin4 = 0;
  }
}
void movl(){
  if(SL==0){
    Lpin1 = 0;
    Lpin2 = 1;
    Lpin3 = 0;
    Lpin4 = 1;
  }
  if(SL==1){
    Lpin1 = 1;
    Lpin2 = 0;
    Lpin3 = 0;
    Lpin4 = 1;
  }
  if(SL==2){
    Lpin1 = 1;
    Lpin2 = 0;
    Lpin3 = 1;
    Lpin4 = 0;
  }
  if(SL==3){
    Lpin1 = 0;
    Lpin2 = 1;
    Lpin3 = 1;
    Lpin4 = 0;
  }
}
void movf(){
  if(SF==0){
    Fpin1 = 0;
    Fpin2 = 1;
    Fpin3 = 0;
    Fpin4 = 1;
  }
  if(SF==1){
    Fpin1 = 1;
    Fpin2 = 0;
    Fpin3 = 0;
    Fpin4 = 1;
  }
  if(SF==2){
    Fpin1 = 1;
    Fpin2 = 0;
    Fpin3 = 1;
    Fpin4 = 0;
  }
  if(SF==3){
    Fpin1 = 0;
    Fpin2 = 1;
    Fpin3 = 1;
    Fpin4 = 0;
  }
}
void movb(){
  if(SB==0){
    Bpin1 = 0;
    Bpin2 = 1;
    Bpin3 = 0;
    Bpin4 = 1;
  }
  if(SB==1){
    Bpin1 = 1;
    Bpin2 = 0;
    Bpin3 = 0;
    Bpin4 = 1;
  }
  if(SB==2){
    Bpin1 = 1;
    Bpin2 = 0;
    Bpin3 = 1;
    Bpin4 = 0;
  }
  if(SB==3){
    Bpin1 = 0;
    Bpin2 = 1;
    Bpin3 = 1;
    Bpin4 = 0;
  }
}
void aggexp(){
  exp1 = (Dpin4*128) + (Dpin3*64) + (Dpin2*32) + (Dpin1*16) + (Upin4*8) + (Upin3*4) + (Upin2*2) + Upin1;
  Wire.beginTransmission(adrs1);
  Wire.write(exp1);
  Wire.endTransmission();
  exr2 = (Lpin4*128) + (Lpin3*64) + (Lpin2*32) + (Lpin1*16) + (Rpin4*8) + (Rpin3*4) + (Rpin2*2) + Rpin1;
  Wire.beginTransmission(adrs2);
  Wire.write(exr2);
  Wire.endTransmission();
  exp3 = (Bpin4*128) + (Bpin3*64) + (Bpin2*32) + (Bpin1*16) + (Fpin4*8) + (Fpin3*4) + (Fpin2*2) + Fpin1;
  Wire.beginTransmission(adrs3);
  Wire.write(exp3);
  Wire.endTransmission();
}

//funzioni per i servo
void servo_1(int pins1, int s1c, int s1a){ //funzioni per creare i servomotori servo*(pin, angolo da chiuso, angolo da aperto);
  ledcAttach(pins1, 50, 16);
  pinss1 = pins1;
  ss1a = map(s1a,0,180,pwmmin,pwmmax);
  ss1c = map(s1c,0,180,pwmmin,pwmmax);
}
void servo_2(int pins2, int s2c, int s2a){
  ledcAttach(pins2, 50, 16);
  pinss2 = pins2;
  ss2a = map(s2a,0,180,pwmmin,pwmmax);
  ss2c = map(s2c,0,180,pwmmin,pwmmax);
}
void servo_3(int pins3, int s3c, int s3a){
  ledcAttach(pins3, 50, 16);
  pinss3 = pins3;
  ss3a = map(s3a,0,180,pwmmin,pwmmax);
  ss3c = map(s3c,0,180,pwmmin,pwmmax);
}
void servo_4(int pins4, int s4c, int s4a){
  ledcAttach(pins4,50, 16);
  pinss4 = pins4;
  ss4a = map(s4a,0,180,pwmmin,pwmmax);
  ss4c = map(s4c,0,180,pwmmin,pwmmax);
}
void servo_op(){                           //funzione per aprire i servo
  ledcWrite(pinss1,ss1a);
  ledcWrite(pinss2,ss2a);
  ledcWrite(pinss3,ss3a);
  ledcWrite(pinss4,ss4a);
}
void servo_cl(){                           //funzione per chiudere i servo
  ledcWrite(pinss1,ss1c);
  ledcWrite(pinss2,ss2c);
  ledcWrite(pinss3,ss3c);
  ledcWrite(pinss4,ss4c);
}