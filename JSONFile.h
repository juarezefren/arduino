#include <FS.h>
#include <ArduinoJson.h>

class JSONFile {
 public:
  JSONFile(const char* fileName) {
    SPIFFS.begin();
    this->fileName = fileName;
  }

  bool save(const char* key, const char* value) {
    DynamicJsonDocument doc(1024);

    File file = SPIFFS.open(fileName, "r");
    if (!file) {
      doc[key] = value;
    } else {
      DeserializationError error = deserializeJson(doc, file);
      if (error) {
        return false;
      }
      doc[key] = value;
      file.close();
    }

    file = SPIFFS.open(fileName, "w");
    if (!file) {
      return false;
    }
    serializeJson(doc, file);
    file.close();

    return true;
  }

  const char* read(const char* key) {
    File file = SPIFFS.open(fileName, "r");
    if (!file) {
      return NULL;
    }

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
      return NULL;
    }

    file.close();

    return doc[key].as<char*>();
  }

  bool remove(const char* key) {
    File file = SPIFFS.open(fileName, "r");
    if (!file) {
      return false;
    }

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
      return false;
    }

    file.close();

    doc.remove(key);

    file = SPIFFS.open(fileName, "w");
    if (!file) {
      return false;
    }
    serializeJson(doc, file);
    file.close();

    return true;
  }

 private:
  const char* fileName;
};


/*
 * 
 * #include "JSONFile.h"

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  JSONFile file("data.json");
  
  file.save("Nombre", "Efren Juarez Castillo");
  file.save("Edad", "47");
    
  String value = file.read("Nombre");
  Serial.println("Nombre: " + value);

  value = file.read("Edad");
  int edad = value.toInt();
  Serial.println("Edad: " + String(edad));
  
  file.remove("Edad");
  
}

void loop() {
 
}
 * */
 */
