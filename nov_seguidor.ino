//definindo motores
#define motorEnableA 10
#define inMotorA1 2 
#define inMotorA2 3
#define motorEnableB 11
#define inMotorB3 4
#define inMotorB4 5

//velocidades dos motores
#define parada 0
#define velocidade1 130
#define velocidade2 155 
#define velocidade3 255

//definindo sensores seguidores de linha
#define sensor1 7
#define sensor2 6
#define sensor3 8
#define sensor4 9

unsigned long tempo = 22000 + 2000; // criada para tirar o delay do inicio da contagem

void setup() {
  // put your setup code here, to run once:

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"Setup" é onde ocorre a definição de (entrada) e (saída) de cada componente no nosso arduino~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  
  //motores
  pinMode(motorEnableA, OUTPUT);
  pinMode(inMotorA1, OUTPUT);
  pinMode(inMotorA2, OUTPUT);
  pinMode(motorEnableB, OUTPUT);
  pinMode(inMotorB3, OUTPUT);
  pinMode(inMotorB4, OUTPUT);
  
  //sensores seguidores de linha
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);

  //tempo até o carrinho começar a iniciar
  delay(2000);    
  }

void loop() {
// put your main code here, to run repeatedly:
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"Loop" é onde ás ações serão executadas repetidamente~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

  //leitura dos sensores
  //armazenei o valor lido pelos sensores em variáveis booleanas que retornam (true) ou (false)
  bool detSensor1 = digitalRead (sensor1);
  bool detSensor2 = digitalRead (sensor2);
  bool detAux1 = digitalRead (sensor3);
  bool detAux2 = digitalRead (sensor4);

    //ir para frente
    if ((detAux1 == true) and  (detSensor1 == true) and (detSensor2 == true) and (detSensor2 == true)){
      frente();
    }
    //curva para esquerda com os sensores principais
    if ((detAux1 == true) and (detSensor1 == false) and (detSensor2 == true) and (detSensor2 == true)){
      curva_e();
    }
    //curva para direita com os sensores principais
    if ((detAux1 == true) and (detSensor1 == true) and (detSensor2 == false) and (detAux2 == true)){
      curva_d();
    }
     //cruzamento de linhas com os sensores principais
    if ((detAux1 == true) and (detSensor1 == false) and (detSensor2 == false) and (detAux2 == true)){
      frente();
    }
    //curva para esquerda (sensores auxiliares) RÉ
    if ((detAux1 == false) and (detSensor1 == true) and (detSensor2 == true) and (detAux2 == true)){
       curva_e(); 
    }
    //curva para direita (sensores auxiliares)
    if ((detAux1 == true) and (detSensor1 == true) and (detSensor2 == true) and (detAux2 == false)){
      curva_d();
    }
    //cruzamento de linha (sensores auxiliares)
    if ((detAux1 == false) and (detSensor1 == true) and (detSensor2 == true) and (detAux2 == false)){
      frente();
    }
    //se caso todos estiverem sobre a faixa devem ignorar a mesma
    if ((detAux1 == false) and (detSensor1 == false) and (detSensor2 == false) and (detAux2 == false)){
      frente();
    }
    //caso os 2 sensores do lado direito (detSensor2) e (detAux2) estiverem sobre a linha devem ignorar a linha
    if ((detAux1 == true) and (detSensor1 == true) and (detSensor2 == false) and (detAux2 == false)){
      curva_d();
    }
    //caso os 2 sensores do lado esquerdo (detAux1) e (detSensor1) estiverem sobre a linha devem ignorar a linha
    if ((detAux1 == false) and (detSensor1 == false) and (detSensor2 == true) and (detAux2 == true)){
      curva_e();
    }
    // para que os 22 seg do inicio do código ao serem batidos pare o carrinho
    if (millis() >= tempo){
      parar();
    }
}


void frente(){
  analogWrite(motorEnableA, velocidade1); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, velocidade1); 
  digitalWrite(inMotorB3, HIGH);
  digitalWrite(inMotorB4, LOW);
}

void curva_d(){
  analogWrite(motorEnableA, velocidade1); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, parada); 
  digitalWrite(inMotorB3, HIGH);
  digitalWrite(inMotorB4, LOW);
}

void curva_e(){
  analogWrite(motorEnableA, parada); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, velocidade1); 
  digitalWrite(inMotorB3, HIGH);
  digitalWrite(inMotorB4, LOW);
}

void parar(){
  analogWrite(motorEnableA, parada); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, parada); 
  digitalWrite(inMotorB3, HIGH);
  digitalWrite(inMotorB4, LOW);
}
