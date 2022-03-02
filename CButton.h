/**
 * Clase CButton
 * Autor: Efrén Juárez Castillo
 * Permite gestionar el funcionamiento de un push button
 * Conexión: Un push button tiene 2 terminales (patitas) A y B  
 * Conecte A a GND  
 * Conecte B a VCC (3 o 5 V) con una resistencia de 2K ohms
 * Entre la resistencia de 2K y B conecte un cable hacia un PIN digital de entrada
 */

class CButton{
  
  private:
    int _newButtonStatate;
    int _oldButtonStatate;
    int _pinButton;
    void (* fptr)();

  public:

  /**
   * Constructor de la clase CButton
   * recibe como parámetro el PIN al
   * cual se encuentra conectado el boton
   */
  CButton(int pinButton){
    _newButtonStatate = 1;
    _oldButtonStatate = 1;
    _pinButton=pinButton;        
     
  }
/**
 * Esta funcion recibe como parametro la función fp()
 * y la asigna a fptr(), será la funcion que se
 * ejecute cuando se presione el boton
 */

void attachFunction(void (* fp)()){ 
  fptr = fp; 
}


/**
 * Esta función ejecuta llama a la función fptr()
 * cuando se presiona el boton
 */
  void isPressed(){ 
    
      _newButtonStatate = digitalRead(_pinButton);
      if (_newButtonStatate != _oldButtonStatate){ 
        _oldButtonStatate=_newButtonStatate;
        //Serial.println("ejecutar");         
          if(_newButtonStatate == LOW){
             //myCode_buttonPressed();
             fptr();
          }        
      }
  }
  
};
