/**
 * Clase CMillis
 * Autor: Efrén Juárez Castillo
 * Permite ejecutar una función cada determinado tiempo
 * usando millis, es una alternativa a Ticker
 */

class CMillis {
  private:
    unsigned long interval;
    unsigned long previousMillis;
    bool running;
    void (*callback)();

  public:
    CMillis(unsigned long interval, void (*callback)()) {
      this->interval = interval;
      this->previousMillis = 0;
      this->running = false;
      this->callback = callback;
    }

    void start() {
      running = true;
      previousMillis = millis();
    }

    void stop() {
      running = false;
    }

    void update() {
      if (!running) {
        return;
      }

      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        callback();
      }
    }
};
