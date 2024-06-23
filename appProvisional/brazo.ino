#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "NETLIFE-VEGA";       // Nombre de tu red WiFi
const char* password = "A99n&G90t#";     // Contraseña de tu red WiFi

WebServer server(80);                     // Objeto para el servidor web

// Definición de pines para cada servo
int baseServoPin = 18;
int brazoServoPin = 19;
int codoServoPin = 21;
int munecaServoPin = 22;
int pinzaServoPin = 23;

// Objetos para controlar cada servo
Servo baseServo;
Servo brazoServo;
Servo codoServo;
Servo munecaServo;
Servo pinzaServo;

void setup() {
    Serial.begin(115200);

    // Conexión a la red WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    Serial.println("Conectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP()); // Imprime la dirección IP asignada

    // Inicialización de todos los servos
    baseServo.attach(baseServoPin);
    baseServo.write(270); // Establece la posición inicial

    brazoServo.attach(brazoServoPin);
    brazoServo.write(180);

    codoServo.attach(codoServoPin);
    codoServo.write(180);

    munecaServo.attach(munecaServoPin);
    munecaServo.write(180);

    pinzaServo.attach(pinzaServoPin);
    pinzaServo.write(45);

    // Configuración del servidor web
    server.on("/", HTTP_GET, [](){
        server.send(200, "text/html", "<h1>Servidor ESP32</h1><p>Control de Servos</p>");
    });

    // Rutas para controlar los servos individualmente
    server.on("/setBaseServo", HTTP_GET, [](){
        handleServoControl(baseServo, "base_brazo");
    });

    server.on("/setBrazoServo", HTTP_GET, [](){
        handleServoControl(brazoServo, "brazo_brazo");
    });

    server.on("/setCodoServo", HTTP_GET, [](){
        handleServoControl(codoServo, "codo_brazo");
    });

    server.on("/setMunecaServo", HTTP_GET, [](){
        handleServoControl(munecaServo, "muneca_brazo");
    });

    server.on("/setPinzaServo", HTTP_GET, [](){
        handleServoControl(pinzaServo, "pinza_brazo");
    });

    server.begin();
    Serial.println("Servidor web iniciado");
}

void loop() {
    server.handleClient(); // Maneja las solicitudes entrantes
}

// Función para manejar el control de los servos
void handleServoControl(Servo& servo, const char* sliderId) {
    if (server.hasArg("angle")) {
        int angle = server.arg("angle").toInt();
        servo.write(angle); // Ajusta el ángulo del servo
        server.send(200, "text/plain", String(sliderId) + " ajustado a: " + String(angle));
    } else {
        server.send(400, "text/plain", "Petición inválida");
    }
}