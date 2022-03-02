
#include "FS.h" // incluir librería FS.h para manejar archivos

//VER EJEMPLO AL FINAL

class FileCon{
  private:  
  
  static const int numKeys=2;
  String keys[numKeys] = {"start","calibracion",};
  String values[numKeys] = {"",""};
  
  String initialValues[numKeys] = {"1","23000"};
  
  
  
  String fileName="config.txt"; //nombre del archivo de configuración
  

  String createStringFromValues(String val[]){
    String cad ="";
    for(int i=0;i<numKeys;i++){
      cad = cad + val[i];
      if(i < numKeys-1) cad = cad + ",";    
    } 
    return cad;
  }

  void getValuesFromString(String cad){
    int tam,pos,i=0;  
    String sub;
    tam = cad.length(); 
      while(tam>0){    
        pos = cad.indexOf(',');
        if(pos<0){ 
          sub = cad;
          cad="";
        }
        else{
          sub = cad.substring(0,pos);
          cad = cad.substring(pos+1);
        }        
        values[i]=sub;
        i++;
        tam = cad.length();        
    }
  }
    
  public:

  FileCon(){          
    bool result = SPIFFS.begin(); // Siempre usa esto para "montar" el sistema de archivos
    Serial.println("SPIFFS opened: ");
    Serial.println(result); // si result es 1 si pudo montar el sistema    
    File f = SPIFFS.open("/"+fileName, "r"); // esto abre el archivo  en modo lectura
    if (!f) {
      Serial.println("El archivo NO existe");
      File f = SPIFFS.open("/"+fileName, "w"); //crea el archivo en modo de escritura
      if (!f) {
        Serial.println("Error al crear el archivo");
      }
      else{
        String cad=createStringFromValues(initialValues);
        f.println(cad);          
        f.close();
        for(int i=0;i<numKeys;i++){
          values[i]=initialValues[i];
        }        
        Serial.println("Archivo creado correctamente");      
      }
    }
    else{
      Serial.println("El archivo SI existe");
      String data="";
      while(f.available()) {        
        data = data + f.readStringUntil('\n'); // Permite leer línea por línea desde el archivo
     }   
     f.close();
     Serial.println(data);
     getValuesFromString(data);
    }
  }

  String getValueKey(String key){
    for(int i=0;i<numKeys;i++){
      if(key.compareTo(keys[i])==0){
       return values[i]; 
      }      
    }
    return "";
  }

  boolean setKeyValue(String key,String value){
    for(int i=0;i<numKeys;i++){
      if(key.compareTo(keys[i])==0){
        values[i] = value;                
        String cad=createStringFromValues(values);
        //hay que guardarel archivo
        File f = SPIFFS.open("/"+fileName, "w"); //crea el archivo en modo de escritura
        if (!f) {
          Serial.println("Error al crear el archivo");
          return false;
        }
        else{
          f.println(cad);          
          f.close();
          return true;
        }                
      }      
    }
    return false;
  }
    
};

/*
  FileCon arch;

  // da una clave (key)  y busca su valor    
  String key = "nombreClave";
  String value = arch.getValueKey(key);
  if(value.length()>0){//si existe, el valor está en r
    Serial.println(key + " : " + value); 
  }
  else{
   Serial.println("La clave: " + key + " no existe..");
  }

  // para modificar el valor de una clave
  if(arch.setKeyValue(key,"nuevoValor")==true){
    Serial.println("modificado correctamente");
  }
  else{
    Serial.println("Error al mofificar");
  }
 
 */
