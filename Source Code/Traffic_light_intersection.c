// Definesc F_CPU inainte de a include delay.h
#define F_CPU 2000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
// Definesc Stare
struct Stare {
unsigned char Iesire;
unsigned char Afisor;
unsigned long Timp;
// Urmatoarea este un pointer catre urmatoarele stari din starea curenta
struct Stare *Urmatoarea[4];
};
// Typedef catre struct Stare -> TipStare pentru a utiliza mai jos in AUTOMAT.
typedef struct Stare TipStare;

/* definirea starilor-sunt adresele celor 4 stari*/
#define treciN &AUTOMAT[0]
#define staiN  &AUTOMAT[1]
#define treciE &AUTOMAT[2]
#define staiE  &AUTOMAT[3]

/*Automatul nostru*/
TipStare AUTOMAT[4]={
{0b00100001,0x54, 5000,{treciN,staiN,treciN,staiN}},
{0b00100010,0x40, 1000,{treciE,treciE,treciE,treciE}},
{0b00001100,0x79, 5000,{treciE,treciE,staiE,staiE}},
{0b00010100,0x40, 1000,{treciN,treciN,treciN,treciN}}
};

int main(void){
TipStare *Pointer;//pointerul de stare
unsigned char Intrare;
/* initializare porturi*/
DDRA = DDRA & 0xFC; //PA1 PA0 intrari
PORTA = PORTA | 0x03; //activam pe intrari rez.interne de pull up
DDRC = DDRC | 0x3F; //PC5..PC0 iesiri
PORTC = PORTC & 0xE0; //LED uri initial stinse
DDRD= 0xFF; //Setam porturile PD ca iesiri
PORTD= 0x00; //Setam LED-urile initial stinse

Pointer =treciN;//pointer pentru starea initiala

while(1){
PORTC = Pointer->Iesire;//actualizam iesire
PORTD = Pointer->Afisor;
_delay_ms(Pointer-> Timp);//intarzierea corespunzatoare starii
Intrare = PINA& 0x03;//citire senzori, port A
//INCERCAREA DE A PUNE CONDITII PENTRU A SE APRINDE DOAR PENTRU TRECI E SI TRECI E AUTOMATE PE POZITIA 2 SI 4
Pointer = Pointer-> Urmatoarea[Intrare];//trecerea la urmatoarea stare
}
}
