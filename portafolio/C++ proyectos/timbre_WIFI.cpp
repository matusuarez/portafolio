
// se incluye la libreria para poder conectarnos por WiFi
#include <ESP8266WiFi.h>

// Constantes para configuración de WIFI SSID Y PASSWORD
const char* ssid = "Fibertel WiFi697 2.4GHz";
const char* password = "01429105824";
const char* apiKey = "o.j3z2I30BjpjbNMhyd1q01R1J6irExYL5";
const char* host = "api.pushbullet.com";

//se define la variable del pulsador,  del LED y del parlante
int pinBoton = D1;
int pinLed = D8;
int ZumbadorPin = 14;

// se define las variables de las notas musicales

int c=261; 
int d=294;
int e=329;
int f=349;
int g=391;
int gS=415;
int a=440;
int aS=455;
int b=466;
int cH=523;
int cSH=554;
int dH=587;
int dSH=622;
int eH=659;
int fH=698;
int fSH=740;
int gH=783;
int gSH=830;
int aH=880;

void setup() {
  
// se define el pin del led, del parlante y el pulsador como entrada ( se utiliza la resistencia interna del microprocesador )
  pinMode(pinBoton,INPUT_PULLUP);
  pinMode(pinLed,OUTPUT);
  pinMode(ZumbadorPin, OUTPUT);
  digitalWrite(pinLed, LOW);
  
// petición a la API de Pushbullet

// comunicacion serial para saber el estado del programa
  Serial.begin(115200);

// Función que inicia la conexión WIFI
  WiFi.begin(ssid,password);

// se imprime el estado de la conexión
  Serial.print("Conectando");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
// si se logra conecta con exito se imprime en pantalla los siguientes datos:
  Serial.println("Conectado");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {

// leer el valor del pin
  if(digitalRead(pinBoton) == LOW) {
    
    //funcion para emitir sonido 
    tone(ZumbadorPin, a, 500);
    delay(500+50);
    tone(ZumbadorPin, a, 500);
    delay(500+50);     
    tone(ZumbadorPin, a, 500); 
    delay(500+50);
    tone(ZumbadorPin, f, 350);  
    delay(350+50);
    tone(ZumbadorPin, cH, 150);
    delay(150+50); 
    
    tone(ZumbadorPin, a, 500);
    delay(500+50);
    tone(ZumbadorPin, f, 350);
    delay(350+50);
    tone(ZumbadorPin, cH, 150);
    delay(150+50);
    tone(ZumbadorPin, a, 1000);   
    delay(1000+50);
   
    tone(ZumbadorPin, eH, 500);
    delay(500+50);
    tone(ZumbadorPin, eH, 500);
    delay(500+50);
    tone(ZumbadorPin, eH, 500); 
    delay(500+50);   
    tone(ZumbadorPin, fH, 350);
    delay(350+50); 
    tone(ZumbadorPin, cH, 150);
    delay(150+50);
    
    tone(ZumbadorPin, gS, 500);
    delay(500+50);
    tone(ZumbadorPin, f, 350);
    delay(350+50);
    tone(ZumbadorPin, cH, 150);
    delay(150+50);
    tone(ZumbadorPin, a, 1000);
    
    
    Serial.println("Presionado");

// mensaje que aparecera en nuestro celular
    enviarMensaje("Puerta Principal","Han tocado el timbre");
    delay(2000);
    
  }

  delay(100);
  
// funcion para activar el led segun el estado del pulsador
while(digitalRead(pinBoton) == LOW);
  digitalWrite(pinLed, HIGH);
  delay(200);
  digitalWrite(pinLed, LOW);
  while(digitalRead(pinLed) == HIGH);
}


// conectarse al host
 
void enviarMensaje(String titulo,String mensaje) {
  
  WiFiClientSecure client;
  client.setInsecure();
  if(!client.connect(host,443)) {
    Serial.println("No se pudo conectar con el servidor");
    return;
  }

// definir a que url nos vamos a conectar
String url = "/v2/pushes";

// imprimir en pantalla el estado del programa
  String message = "{\"type\": \"note\", \"title\": \""+titulo+"\", \"body\": \""+mensaje+"\"}\r\n";
  Serial.print("requesting URL: ");
  Serial.println(url);
  
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + apiKey + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " +
               String(message.length()) + "\r\n\r\n");
  client.print(message);

  delay(2000);
  while (client.available() == 0);

// respuesta del servidor
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }  
}