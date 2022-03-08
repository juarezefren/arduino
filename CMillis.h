/**
 * Clase CMillis
 * Autor: Efrén Juárez Castillo
 * Permite ejecutar una función cada determinado tiempo
 * usando millis, es una alternativa a Ticker
 */
class CMillis{
  
  private:
    unsigned long tiempoAnterior;
    unsigned long pausa;   
    void (* fptr)();

  public:

  /**
   * Constructor de la clase CMillis
   * recibe como parámetro _pausa y fp()
   * _pausa indica un tiempo en milisegundos,
   * fp es la función que se ejecutara cada 
   * cierto (_pausa) tiempo
   */
  CMillis(int _pausa, void (* fp)()){
    pausa = _pausa;    
    tiempo1=millis();  
    fptr = fp;      
  }

/**
 * Esta función ejecuta o llama a la función fptr()
 * cada cierto tiempo indicado en la variable pausa 
 */
  void ejecutar(){     
     if(millis() > tiempoAnterior+pausa){
         fptr();
         tiempoAnterior=millis();
      }
  }
  
};
