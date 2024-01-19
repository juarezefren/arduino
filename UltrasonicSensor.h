
class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;

    static const int minDistance = 2; // Mínima distancia que lee el ultrasonico
    static const int maxDistance = 400; // Máxima distancia que lee el ultrasonico

  public:
    // Constructor
    UltrasonicSensor(int triggerPin, int echoPin) {
      this->triggerPin = triggerPin;
      this->echoPin = echoPin;
      pinMode(triggerPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    // Método para obtener una única distancia
    float getDistance() {
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      
      long duration = pulseIn(echoPin, HIGH);
      float distance = duration * 0.034 / 2; // Convertir a centímetros
      
      if (distance >= minDistance && distance <= maxDistance) return distance;
      else return -1;
    }

    // Método para obtener la distancia con precisión
    float getDistancePrecision(int N = 11) {
      float measurements[N]; // Arreglo para almacenar las mediciones
      int count = 0; // Contador para las lecturas válidas
      
      // Llenar el arreglo con las lecturas válidas de distancia
      for (int i = 0; i < N; ++i) {
        float distance = getDistance();
        if (distance != -1) {
          measurements[count++] = distance;
        }
      }
      
      // Si no hay lecturas válidas, regresa -1
      if (count == 0) return -1;

      // Calcular la media de las distancias
      float sum = 0;
      for (int i = 0; i < count; ++i) {
        sum += measurements[i];
      }
      float mean = sum / count;
      
      // Calcular la desviación estándar
      float variance = 0;
      for (int i = 0; i < count; ++i) {
        variance += pow(measurements[i] - mean, 2);
      }
      float stdDeviation = sqrt(variance / count);
      
      // Filtrar valores atípicos
      float filteredSum = 0;
      int filteredCount = 0;
      for (int i = 0; i < count; ++i) {
        if (abs(measurements[i] - mean) <= stdDeviation) {
          filteredSum += measurements[i];
          filteredCount++;
        }
      }
      
      // Si todos los valores son atípicos, no hay valor confiable, regresar -1
      if (filteredCount == 0) return -1;

      // Calcular el promedio de los valores filtrados
      return filteredSum / filteredCount;
    }
};
