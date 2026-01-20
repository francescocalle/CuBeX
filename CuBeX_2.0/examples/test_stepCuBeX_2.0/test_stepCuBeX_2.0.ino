#include <CuBeX_2.0.h>
//QUESTA LIBRERIA FUNZIONA SOLO CON:
// -MOTORI NEMA 17 (o almeno dei motori che facciano 200 passi per giro);
// -DRIVER L298N;
// -I/O EXPANDER (8bit).

void setup() {
  stepper_init(20, 21, 0x00, 0x01, 0x02);   //inizializzo i motori stepper_init(pin sda, pin scl, indirizzo expander UD, indirizzo expander RL, indirizzo expander FB);
  stepper_RPM(60);      //imposto la velocità a 60
}

void loop() {
  stepper_LUN(200);     //imposto la lunghezza della rotazione a 200 (un giro in senso orario)
  step_U();             //faccio eseguire il  movimento la motore
  delay(1000);          //delay per non far muovere subito il motore
  stepper_LUN(-200);    //imposto la lunghezza della rotazione a -200 (un giro in senso antiorario)
  step_U();             //faccio eseguire il  movimento la motore
  delay(1000);          //delay per non far muovere subito il motore
}