//Sensor de luz com LDR
 
int ledPin = 7; //Led no pino 7
int ldrPin = 0;//LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR
const int buzzer = 3;

void setup() {
 pinMode(ledPin,OUTPUT);//define a porta 7 como saída
 pinMode(buzzer, OUTPUT); 
 Serial.begin(9600); //Inicia a comunicação serial
}
 
void loop() {
 ///ler o valor do LDR
 ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
 
 //se o valor lido for maior que 500, liga o led
 if (ldrValor>= 1015){
  digitalWrite(ledPin,HIGH);
  tone(buzzer, 1000); 
  delay(1000);        
  noTone(buzzer);     
  delay(1000);  
 }
  
 // senão, apaga o led
 else digitalWrite(ledPin,LOW);
 
 //imprime o valor lido do LDR no monitor serial
 Serial.println(ldrValor);
 delay(100);
}