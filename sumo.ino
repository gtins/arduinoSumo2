#define leftRev 5
#define leftFow 6

#define rightFow 10
#define rightRev 9

#define rightDef 11
#define leftDef 7

#define frente A2
#define direita A1
#define esquerda A0

#define LUZ 500 // THRESHOLD DA LINHA BRANCA
#define DISTANCIA 120 // THRESHOLD DA DISTANCIA PRO SENSOR FRONTAL

class Sumo {
private:
  int motor_left_pinF;
  int motor_left_pinR;
  int motor_right_pinF;
  int motor_right_pinR;
  int motor_def_right_pin;
  int motor_def_left_pin;
  int frente_pin;
  int direito_pin;
  int esquerdo_pin;
  int luzThreshold;
  int distanciaThreshold;

public:
  Sumo(int motorEsquerdoTras, int motorEsquerdoFrente, int motorDireitoFrente, int motorDireitoTras, int motorDireitoDefine, int motorEsquerdoDefine, int sensorFrente, int sensorDireito, int sensorEsquerdo, int luz, int distancia) {
    motor_left_pinF = motorEsquerdoTras;
    motor_left_pinR = motorEsquerdoFrente;
    motor_right_pinF = motorDireitoFrente;
    motor_right_pinR = motorDireitoTras;
    motor_def_right_pin = motorDireitoDefine;
    motor_def_left_pin = motorEsquerdoDefine;
    frente_pin = sensorFrente;
    direito_pin = sensorDireito;
    esquerdo_pin = sensorEsquerdo;
    luzThreshold = luz;
    distanciaThreshold = distancia;
  }

  void setup() {
    Serial.begin(9600);
    motorSetup(motor_def_right_pin, motor_def_left_pin);
  }

  void loop() {
    Serial.println(linha(readSensor(direito_pin), luzThreshold));
    Serial.println(linha(readSensor(esquerdo_pin), luzThreshold));
    girar_detect(detecta_frente(readSensor(frente_pin), distanciaThreshold), motor_right_pinF, motor_left_pinF);
    parar_linha(linha(readSensor(direito_pin), luzThreshold), motor_right_pinF, motor_left_pinF);
    parar_linha(linha(readSensor(esquerdo_pin), luzThreshold), motor_right_pinF, motor_left_pinF);
  }

private:
  int readSensor(int sensorPin) {
    return analogRead(sensorPin);
  }

  void motorSetup(int motorENA, int motorENB) {
    digitalWrite(motorENA, HIGH);
    digitalWrite(motorENB, HIGH);
  }

  void motorOn(int motorPin) {
    digitalWrite(motorPin, HIGH);
  }

  void motorOff(int motorPin) {
    digitalWrite(motorPin, LOW);
  }

  bool linha(int leituraSensor, int luz) {
    return leituraSensor <= luz;
  }

  bool detecta_frente(int leituraSensor, int distancia) {
    return leituraSensor >= distancia;
  }

  void girarOn(int motorFrente, int motorTras) {
    motorOn(motorFrente);
    motorOn(motorTras);
  }

  void girarOff(int motorFrente, int motorTras) {
    motorOff(motorFrente);
    motorOff(motorTras);
  }

  void girar_detect(bool detecta_frente, int motorFrente, int motorTras) {
    if (detecta_frente == 1) {
      girarOff(motorFrente, motorTras);
      motorOn(rightFow);
      motorOn(leftFow);
    }
    else {
      motorOff(rightFow);
      motorOff(leftFow);
      girarOn(motorFrente, motorTras);
    }
  }

  void parar_linha(bool linha, int motorFrente, int motorTras) {
    if (linha == 1) {
      girarOff(motorFrente, motorTras);
      motorOff(motorFrente);
      motorOff(motorTras);
    }
    else {
      motorOn(motorFrente);
      motorOn(motorTras);
    }
  }
};

Sumo robo(leftRev, leftFow, rightFow, rightRev, rightDef, leftDef, frente, direita, esquerda, LUZ, DISTANCIA);

void setup() {
  robo.setup();
}

void loop() {
  robo.loop();
}
