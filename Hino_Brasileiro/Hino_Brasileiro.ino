#include "pitches.h"
#define NO_SOUND 0

// Notas que devem ser tocadas ordenadamente;
int melodia[] = {
  NOTE_C4,
  NOTE_F4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_AS4,
  NOTE_B4,NOTE_C5,NOTE_F4,NOTE_C4,
  NOTE_F4,NOTE_E4,NOTE_G4,NOTE_F4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4,
  NOTE_FS4,NOTE_G4,NO_SOUND,NO_SOUND,NOTE_C4,
  NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_A4,NOTE_AS4,NOTE_A4,NOTE_AS4,NOTE_B4,

  NOTE_CS5,NOTE_D5,NOTE_G4,NOTE_C4,
  NOTE_G4,NOTE_F4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4,NOTE_B4,NOTE_AS4,
  NOTE_GS4,NOTE_A4,NO_SOUND,NOTE_A4,NOTE_A4,
  NOTE_AS4,NOTE_A4,NO_SOUND,NOTE_A4,NOTE_AS4,NOTE_A4,
  NOTE_A4,NOTE_D5,NOTE_C5,NOTE_AS4,
  NOTE_AS4,NOTE_A4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_F4,NOTE_F4,NOTE_E4,

  NOTE_E4,NOTE_D4,NO_SOUND,NOTE_G4,NOTE_G4,
  NOTE_A4,NOTE_G4,NO_SOUND,NOTE_G4,NOTE_A4,NOTE_G4,
  NOTE_G4,NOTE_C5,NOTE_B4,NOTE_A4,
  NOTE_A4,NOTE_G4,NOTE_G4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_D4,
  NOTE_D4,NOTE_C4,NO_SOUND,NOTE_C4,NOTE_E4,NOTE_G4,
  NOTE_AS4,NOTE_C4,NOTE_E4,NOTE_G4,NOTE_AS4,NOTE_C4,NOTE_E4,NOTE_G4,

  NOTE_AS4,NOTE_AS4,NOTE_C4,
  NOTE_F4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_AS4,
  NOTE_B4,NOTE_C5,NOTE_F4,NOTE_C4,
  NOTE_F4,NOTE_E4,NOTE_G4,NOTE_F4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4,
  NOTE_FS4,NOTE_G4,NO_SOUND,NOTE_C4,
  NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_A4,NOTE_AS4,NOTE_A4,NOTE_AS4,NOTE_B4,

  NOTE_CS5,NOTE_D5,NOTE_G4,NOTE_C4,
  NOTE_G4,NOTE_FS4,NOTE_A4,NOTE_G4,NOTE_AS4,NOTE_A4,NOTE_C5,NOTE_AS4,
  NOTE_GS4,NOTE_A4,NO_SOUND,NO_SOUND,NOTE_F4,
  NOTE_G4,NOTE_F4,NOTE_E4,NOTE_F4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_F4,
  NOTE_F4,NOTE_AS4,NOTE_AS4,NO_SOUND,NOTE_G4,
  NOTE_A4,NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_FS4,NOTE_G4,NOTE_A4,NOTE_G4,//2ºFS4 
  
  NOTE_G4,NOTE_C5,NOTE_C5,NO_SOUND,NOTE_A4,
  NOTE_AS4,NOTE_A4,NOTE_GS4,NOTE_A4,NOTE_GS4,NOTE_A4,NOTE_AS4,NOTE_A4,//2ºGS4
  NOTE_A4,NOTE_D5,NOTE_C5,NOTE_AS4,NOTE_G4,
  NOTE_G4,NOTE_F4,NO_SOUND,NOTE_E4,NOTE_F4,NOTE_G4,
  NOTE_AS4,NOTE_A4,NOTE_E4,NOTE_F4,NOTE_CS4,NOTE_D4,NOTE_AS4,NOTE_G4,
  NOTE_G4,NOTE_F4,NO_SOUND,NOTE_G4,NOTE_A4,NOTE_AS4,
  
  NOTE_B4,NOTE_C5,NOTE_A4,NOTE_F4,NOTE_D4,NOTE_AS4,
  NOTE_A4,NOTE_F4,NOTE_D4,NOTE_C4,NOTE_D4,NOTE_E4,
  NOTE_F4
  
  
  
  
};

// Duração das Notas: Colcheia:8; Semínima: 4; Mínima:2; Semibreve:1
int tempoNotas[] = {
  4,
  6,16,6,16,6,16,6,16,
  3,8,4,4,
  6,16,6,16,6,16,6,16,
  4,4,4,16,8,
  6,16,6,16,6,16,6,16,

  3,8,4,4,
  6,16,6,16,6,16,6,16,
  4,4,4,6,16,
  4,4,8,8,6,16,
  4,2,8,8,
  8,8,8,8,8,8,8,8,

  4,4,4,6,16,
  4,4,8,8,6,16,
  4,2,8,8,
  8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,
  8,8,8,8,8,8,8,8,

  2,4,4,
  6,16,6,16,6,16,6,16,
  3,8,4,4,
  6,16,6,16,6,16,6,16,
  4,4,4,4,
  6,16,6,16,6,16,6,16,

  3,8,4,4,
  6,16,6,16,6,16,6,16,
  4,4,4,8,16,
  6,16,6,16,6,16,6,16,
  3,8,4,8,8,
  6,16,6,16,6,16,6,16,
  
  3,8,4,8,8,
  6,16,6,16,6,16,6,16,
  4,3,8,8,8,
  4,4,8,8,8,8,
  8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,
  
  8,8,8,8,4,4,
  4,6,16,4,6,16,
  2
};

const int compasso = 1500; // Altera o compasso da música 

void setup() {
  for (int Nota = 0; Nota < 230; Nota++) {//o número 80 indica quantas notas tem a nossa matriz.
    int tempo = compasso/tempoNotas[Nota]; //Tempo = compasso dividido pela indicação da matriz tempoNotas.
    tone(3, melodia[Nota],tempo); //Toca a nota indicada pela matriz melodia durante o tempo.
    // Para distinguir as notas adicionamos um tempo entre elas (tempo da nota + 20%).
    delay(tempo*1.2);
  }
}
void loop(){
  //Não é necessária a repetição pois a mesma será feita pelo botão Reset.
}
//Fim de Programa
