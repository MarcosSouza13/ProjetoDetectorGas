#include <Servo.h> //Biblioteca do servo motor
#include <Keypad.h> //Biblioteca do teclado matricial

int Pino_Servo = 13; //Porta Servo Motor
int Pino_Led = 12; //PINO Led
int Pino_Buzzer = 11; // Pino Buzina
int Pino_SensorGas = A0; // Pino do Sensor de Gás
int nivel_sensor = 250; // Nivel do
int condicao = 1; // Variável de controle do sensor

char* senha = "1#2#"; //Definição da senha(6 DIGITOS)
int var_senha_armazenada = 0;

const byte LINHAS = 4; // Quantidade de linhas do teclado
const byte COLUNAS = 4; // Quantidade de colunas do teclado

// Objeto mapeado pelo teclado matricial
char digitos[LINHAS][COLUNAS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinosLinha[LINHAS] = {9, 8, 7, 6}; // pinos de conexão das linhas no arduino
byte pinosColuna[COLUNAS] = {5, 4, 3, 2}; // pinos de conexão das colunas no arduino

Keypad keypad = Keypad( makeKeymap(digitos), pinosLinha, pinosColuna, LINHAS, COLUNAS ); // objeto de leitura das teclas com os parâmetros lidos
Servo s; //Objeto do Servo motor

void setup() {
  pinMode(Pino_Servo, OUTPUT); //Definindo o Servo como Saída
  pinMode(Pino_Led, OUTPUT);  //Definindo o Led como Saída
  pinMode(Pino_Buzzer, OUTPUT); //Definindo o Buzina como Saída
  pinMode(Pino_SensorGas, INPUT);  //Definindo o Sensor de Gás como Entrada
  Serial.begin(115200); //Inicializando o Serial Monitor
  s.attach(Pino_Servo); // Inicializando o Servo Motor
  s.write(0); // Colocando o Servo Motor na posição 0°
}

void loop() {

  char digito = keypad.getKey(); // faz a leitura das teclas
  Serial.write("0"); //Escreve 1 no serial monitor

  //Se a leitura analógica for maior que 250
  if (analogRead(Pino_SensorGas) >= nivel_sensor) {
    digitalWrite(Pino_Led, HIGH); //Liga o led
    digitalWrite(Pino_Buzzer, HIGH); //Liga a buzina
    s.write(100); //Colocando o Servo Motor na posição 100°
    Serial.write("1"); //Escreve 0 no serial monitor
  }

  if (digito != 0) {
    if (digito == senha[var_senha_armazenada]) var_senha_armazenada ++;
    else var_senha_armazenada = 0;

    if (var_senha_armazenada == 4)  {
      digitalWrite(Pino_Led, LOW); //Desliga o led
      digitalWrite(Pino_Buzzer, LOW); //Desliga a buzina
      s.write(0); //Colocando o Servo Motor na posição 0°
      Serial.write("0"); //Escreve 1 no serial monitor
    }
  }
}
