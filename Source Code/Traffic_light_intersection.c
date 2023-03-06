//To understand the variables translate from Romanian to your language.
// I define F_CPU before including delay.h
#define F_CPU 2000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
// Define Stats
struct Stare {
unsigned char Iesire;
unsigned char Afisor;
unsigned long Timp;
// Next is a pointer to the next states from the current state
struct Stare *Urmatoarea[4];
};
// Typedef to struct Status -> TypeState to use below in AUTOMAT.
typedef struct Stare TipStare;

/* definition of the states - are the addresses of the 4 states*/
#define treciN &AUTOMAT[0]
#define staiN  &AUTOMAT[1]
#define treciE &AUTOMAT[2]
#define staiE  &AUTOMAT[3]

/*Our vending machine*/
TipStare AUTOMAT[4]={
{0b00100001,0x54, 5000,{treciN,staiN,treciN,staiN}},
{0b00100010,0x40, 1000,{treciE,treciE,treciE,treciE}},
{0b00001100,0x79, 5000,{treciE,treciE,staiE,staiE}},
{0b00010100,0x40, 1000,{treciN,treciN,treciN,treciN}}
};

int main(void){
TipStare *Pointer;//the status pointer
unsigned char Intrare;
/* ports initialization*/
DDRA = DDRA & 0xFC; //PA1 PA0 inputs
PORTA = PORTA | 0x03; //we activate on internal res. pull up inputs
DDRC = DDRC | 0x3F; //PC5..PC0 output
PORTC = PORTC & 0xE0; //LEDs initially off
DDRD= 0xFF; //Set PD ports as outputs
PORTD= 0x00; //Set the LEDs initially off

Pointer =treciN;//Pointer for the initial state

while(1){
PORTC = Pointer->Iesire;//update the output
PORTD = Pointer->Afisor;
_delay_ms(Pointer-> Timp);//the delay corresponding to the state
Intrare = PINA& 0x03;//read sensors port A
Pointer = Pointer-> Urmatoarea[Intrare];//pass to the next state
}
}
