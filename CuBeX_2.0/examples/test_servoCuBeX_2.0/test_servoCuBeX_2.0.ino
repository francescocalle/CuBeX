#include <CuBeX_2.0.h>

void setup() {
  servo_1(33,0,90);           //funzione per creare i servomotori servo*(pin, angolo da chiuso, angolo da aperto);
  servo_2(34,0,90);
  servo_3(35,0,90);
  servo_4(36,0,90);
}

void loop() {
  servo_op();                 //funzione per aprire i servo
  delay(1000);
  servo_cl();                 //funzione per chiudere i servo
  delay(1000);
}