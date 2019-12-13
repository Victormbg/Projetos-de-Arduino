#include <Adafruit_Fingerprint.h>

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\CADASTRAR DIGITAL ISERJ - SESUTI");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("SENSOR DETECTADO COM SUCESSO");
  } else {
    Serial.println("SENSOR NAO FOI DETECTADO:(");
    while (1) { delay(1); }
  }
}

uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop()                     // run over and over again
{
  Serial.println("PRONTO PARA LER UMA NOVA DIGITA: ");
  Serial.println("ESCOLHA UM ID PARA A DIGITAL # (ENTRE 1 to 127): ");
  id = readnumber();
  if (id == 0) {// ID #0 NAO E PERMITIDO, ESCOLHA OUTRO!
     return;
  }
  Serial.print("LENDO ID #");
  Serial.println(id);
  
  while (!  getFingerprintEnroll() );
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("ESPERANDO PARA VALIDAR O #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("IMAGEM TIRADA");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("ERROR");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("ERRO NA IMAGEM");
      break;
    default:
      Serial.println("ERRO DESCONHECIDO");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("IMAGEM CONVERTIDA");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("IMAGEM MUITO CONFUSA");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("ERRO DE COMUNICACAO");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("NAO FOI POSSIVEL ACHAR OS RECUSOS DE IMPRESSOA DIGITAL");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("NAO FOI ACHADO UMA IMPRESSAO DIGITAL");
      return p;
    default:
      Serial.println("ERRO DESCONHECIDO");
      return p;
  }
  
  Serial.println("TIRE O DEDO: ");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("RECOLOQUE O DEDO NOVAMENTE: ");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("IMAGEM TIRADA");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("ERRO DE COMUNICACAO");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("ERRO NA IMAGEM");
      break;
    default:
      Serial.println("ERRO DESCONHECIDO");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("IMAGEM CONVERTIDA");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("ERRO DE COMUNICACAO");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("ERRO DESCONHECIDO");
      return p;
  }
  
  // OK converted!
  Serial.print("CRIANDO MODELO PARA #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("IMPRESSOES COMBINADAS COM SUCESSO");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("ERRO DE COMUNICAÇÂO");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("IMPRESSÂO DIGITAL NAO COMBINA");
    return p;
  } else {
    Serial.println("ERRO DESCONHECIDO");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("IMPRESSAO ARMAZENADA");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("ERRO DE COMUNICACAO");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("NAO FOI POSSIVEL ARMAZENA NESSE LOCAL");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}
