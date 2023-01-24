//definindo motores
#define motorEnableA 10
#define inMotorA1 2 
#define inMotorA2 3
#define motorEnableB 11
#define inMotorB3 4
#define inMotorB4 5

//velocidades dos motores
#define parada 0
#define velocidade1 80
#define velocidade_motorB 90

//definindo sensores seguidores de linha
#define sensor1 7
#define sensor2 6
#define sensor3 8
#define sensor4 9

#define trigger 12
#define echo 13

#define led 14

  float cm;
  float duracao; //variável de tempo

void setup() {
  // put your setup code here, to run once:
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

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(led, OUTPUT);

  delay(2000);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  cm = calcula_dist();

  Serial.print("Distância = ");
  Serial.println(cm);

  //leitura dos sensores
  //armazenei o valor lido pelos sensores em variáveis booleanas que retornam (true) ou (false)
  bool detSensor1 = digitalRead (sensor1);
  bool detSensor2 = digitalRead (sensor2);
  bool detAux1 = digitalRead (sensor3);
  bool detAux2 = digitalRead (sensor4);
  
  if (cm < 15){
    parar();  
  }  
    //curva para direita (sensores auxiliares)
    else if ((detAux1 == true) and (detSensor1 == true) and (detSensor2 == true) and (detAux2 == false)){
      curva_d();
    }
    //ir para frente
    else if ((detAux1 == true) and  (detSensor1 == true) and (detSensor2 == true) and (detSensor2 == true)){
      frente();
    }
  
    //curva para esquerda com os sensores principais
    else if ((detAux1 == true) and (detSensor1 == false) and (detSensor2 == true) and (detSensor2 == true)){
      curva_e();
    }
  
    //curva para direita com os sensores principais
    else if ((detAux1 == true) and (detSensor1 == true) and (detSensor2 == false) and (detAux2 == true)){
      curva_d();
   }

    //cruzamento de linhas com os sensores principais
    else if ((detAux1 == true) and (detSensor1 == false) and (detSensor2 == false) and (detAux2 == true)){
      frente();
    }
    //curva para esquerda (sensores auxiliares)
    else if ((detAux1 == false) and (detSensor1 == true) and (detSensor2 == true) and (detAux2 == true)){
      curva_e();
    }
    //cruzamento de linha (sensores auxiliares)
    else if ((detAux1 == true) and (detSensor1 == false) and (detSensor2 == false) and (detAux2 == true)){
      frente();
    }
    //se caso todos estiverem sobre a faixa devem ignorar a mesma
    else if ((detAux1 == false) and (detSensor1 == false) and (detSensor2 == false) and (detAux2 == false)){
      frente();
    }
    //caso os 2 sensores do lado direito (detSensor2) e (detAux2) estiverem sobre a linha devem ignorar a linha
    else if ((detAux1 == true) and (detSensor1 == true) and (detSensor2 == false) and (detAux2 == false)){
      frente();
    }
    //caso os 2 sensores do lado esquerdo (detAux1) e (detSensor1) estiverem sobre a linha devem ignorar a linha
    else if ((detAux1 == false) and (detSensor1 == false) and (detSensor2 == true) and (detAux2 == true)){
      frente();
    }
  } 
  
  // função para enviar e receber ás ondas de informações
float calcula_dist(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duracao = pulseIn(echo, HIGH);    

  float di = (duracao/2) * 0.0343;
    if (di >= 300){ // se a distância for maior que 3M, coloque-a em 26cm
      di = 26;
    }
  return di;    
}

void frente(){
  analogWrite(motorEnableA, velocidade1); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, velocidade_motorB); 
  digitalWrite(inMotorB3, LOW);
  digitalWrite(inMotorB4, HIGH);

  digitalWrite(led, LOW);
}

void curva_d(){
  analogWrite(motorEnableA, velocidade1); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, parada); 
  digitalWrite(inMotorB3, LOW);
  digitalWrite(inMotorB4, HIGH);

  digitalWrite(led, LOW);
}

void curva_e(){
  analogWrite(motorEnableA, parada); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, velocidade_motorB); 
  digitalWrite(inMotorB3, LOW);
  digitalWrite(inMotorB4, HIGH);

  digitalWrite(led, LOW);
}

// função ao parar os motores pisca o led
void parar(){
  analogWrite(motorEnableA, parada); 
  digitalWrite(inMotorA1, LOW); 
  digitalWrite(inMotorA2, HIGH);

  analogWrite(motorEnableB, parada); 
  digitalWrite(inMotorB3, LOW);
  digitalWrite(inMotorB4, HIGH);

  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}
