class PushButton {
   private:
    int _buttonState;
    int _pinButton;
    std::function<void(void)> _callback;

  public:
    /**
     * Constructor de la clase PushButton
     * recibe como parámetro el PIN al
     * cual se encuentra conectado el botón
     */
    PushButton(int pinButton) : _pinButton(pinButton) {
      pinMode(_pinButton, INPUT_PULLUP); // Lo configura de salida
    }

    /**
     * Esta función recibe como parámetro la función fp()
     * y la asigna a una función lambda, será la función que se
     * ejecute cuando se presione el botón
     */
    void attachFunction(std::function<void(void)> callback) {
      _callback = callback;
    }

    /**
     * Esta función actualiza el estado del botón y
     * ejecuta la función asociada si el botón es presionado
     */
    void update() {
      int newState = digitalRead(_pinButton);
      if (newState == LOW && _buttonState == HIGH) {
        _callback();
      }
      _buttonState = newState;
    }
};



/*
#include "PushButton.h"

int cont=0;
PushButton boton(D0);

void funcion(){
  cont++;
  Serial.println("Se presiono el botón: " + String(cont));
}

void setup() {
  Serial.begin(9600);
  while(!Serial);  
  boton.attachFunction(funcion);
}

void loop() {
  boton.update();
}
  
 */
