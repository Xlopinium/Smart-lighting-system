#define Tone 8
const int ledCount = 6;
int ledPins[] = {
  12, 11, 10, 9, 3, 2
};   // массив пинов светодиодов
int  start = 0;
int pre = 0;

void setup() {
  Serial.begin(9600);
  // проходим через все элементы массива и устанавливаем режим для вывода
  for (int thisLed = 0; thisLed <= ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
  pinMode(13, INPUT_PULLUP);
  pinMode(Tone, OUTPUT);


}
void loop() {
  bool btnStan = digitalRead(13);
  if (btnStan == 1 and start == 0 and pre == 0) {
    pre = 1;
    start = 1;
    Serial.print("on");
  }

  else if (btnStan == 1 and start == 1 and pre == 0) {
    start = 0;
    pre = 1;

    Serial.print("off");
  }
  if (btnStan == 0) pre = 0;
  if (start == 1 ) {
    int pwm = analogRead(A0); // считываем сигнал с датчика
    // трансформируем результат в диапазон от 0 до 6
    const int ledLevel = map(pwm, 0, 1023, 0, 10);
    for (int thisTone = 1; thisTone < 4; thisTone++) { 
      if (thisTone < ledLevel) {            	//////////////////////////////
        tone(Tone, 1000, 100);            		/////////////////////////////
      }                       					////////////////////////////
      if (thisTone < ledLevel) {          		// Немного магии вне стен//
        tone(Tone, 256, 1000);             		//Хогвартса////////////////
      } else {                    		 		//////////////////////////
        noTone(Tone);                		 	//////////////////////////
      }											 //////////////////////////
    }                        

    // проходим через массив светодиодов
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      // если индекс элемента массива меньше чем ledLevel,
      // включаем порт для данного элемента:

      if (thisLed < ledLevel) {
        digitalWrite(ledPins[thisLed], LOW);
      }
      // Выключаем все порты, которые выше чем ledLevel:
      else {
        digitalWrite(ledPins[thisLed], HIGH);
      }
    }
  }
  else {
    noTone(Tone);
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }
}