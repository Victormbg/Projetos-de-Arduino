
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();
int GreenLed = 4;
int RedLed = 5;
const int buzzer = 8;

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (YELLOW wire)

SoftwareSerial mySerial(2, 3);  //activates serial communication on pin 2 & 3

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  Serial.begin(9600);  // initialize the serial communications:
  pinMode(4, OUTPUT);  // set pin 4 as output. green LED connected
  pinMode(5, OUTPUT);  // set pin 5 as output. red LED connected
  finger.begin(57600);  // set the data rate for the sensor serial port
  digitalWrite(RedLed, HIGH);
  pinMode(buzzer, OUTPUT);  
}


void loop()  // run over and over again
{
  getFingerprintID();
  delay(100);
}

uint8_t getFingerprintID()
{
  uint8_t p = finger.getImage();

  switch (p)
  {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_NOFINGER:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      return p;
    case FINGERPRINT_IMAGEFAIL:
      return p;
    default:
      return p;
  }

  p = finger.image2Tz();
  switch (p)
  {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      return p;
    case FINGERPRINT_FEATUREFAIL:
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      return p;
    default:
      return p;
  }

  // match finger with stored ID#
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK)
  {
    digitalWrite(GreenLed, HIGH);  //turn on green LED and Relay if finger ID is match
    digitalWrite(RedLed, LOW);  //red LED is OFF
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(2000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
   
  }
  else if (p == FINGERPRINT_NOTFOUND)
  {
    digitalWrite(GreenLed, LOW); //turn off green LED and Relay if finger do not match
    digitalWrite(RedLed, HIGH);  //red LED is ON
    return p;
  }
  else
  {
    return p;
  }

}

// returns ID#
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

}
