#include<CuBeX.h>

const int w = 1;//bianco
const int y = 2;//giallo
const int g = 3;//verde
const int b = 4;//blu
const int r = 5;//rosso
const int o = 6;//arancione

//inserisci i tuoi colori nei seguenti vettori per ottenere un algoritmo di risoluzione
int FW[9]={w,w,w,
           w,1,w,
           w,w,w};

int FY[9]={y,y,y,
           y,2,y,
           y,y,y};

int FG[9]={g,g,g,
           g,3,g,
           g,g,g};

int FB[9]={b,b,b,
           b,4,b,
           b,b,b};

int FR[9]={r,r,r,
           r,5,r,
           r,r,r};

int FO[9]={o,o,o,
           o,6,o,
           o,o,o};

int mos=0, er=0,i,timerr=0,algoritmo[250];

void setup() {
  Serial.begin(115200);
  af_W(FW[0],FW[1],FW[2],FW[3],FW[5],FW[6],FW[7],FW[8]);
  af_Y(FY[0],FY[1],FY[2],FY[3],FY[5],FY[6],FY[7],FY[8]);
  af_G(FG[0],FG[1],FG[2],FG[3],FG[5],FG[6],FG[7],FG[8]);
  af_B(FB[0],FB[1],FB[2],FB[3],FB[5],FB[6],FB[7],FB[8]);
  af_R(FR[0],FR[1],FR[2],FR[3],FR[5],FR[6],FR[7],FR[8]);
  af_O(FO[0],FO[1],FO[2],FO[3],FO[5],FO[6],FO[7],FO[8]);
  start();
  mos=mosse();
  timerr=tempo();
  er=errori();
  Serial.print("\nmosse totali: ");
  Serial.println(mos);
  Serial.print("tempo impiegato: ");
  Serial.println(timerr);
  Serial.print("errori: ");
  Serial.println(er);
  for(i=1;i<=mos;i++){
    algoritmo[i-1]=mossa(i);
  }
  for(i=1;i<=mos;i++){
    Serial.print(algoritmo[i-1]);
    Serial.print(" ");
  }
  Serial.print("\n");
}

void loop() {
  delay(1000);
}