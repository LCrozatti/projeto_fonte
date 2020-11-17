/*-------------------------------------------------------------------------\
|UNIVERSIDADE ESTADUAL DE MARINGÁ                                          |
|CTC - DEQ - UEM                                                           |
|CURSO: ENGENHARIA ELÉTRICA                                                |
|DISCIPLINA: CIRCUITOS ELETRONICOS I                                       |
|--------------------------------------------------------------------------|
|GRUPO:                                                                    |
|Gabreiel Gumiero Dias         / RA: 106994                                |       
|Gabriel Vinicius Brandão      / RA: 107760				   |
|Luis Felipe Taboni            / RA: 106975                                |
|Luan Silveira Piffer Crozatti / RA: 107828                                |
|--------------------------------------------------------------------------|
|                                                                          |
|Descricao: Programa de controle de carga e tensão das baterias com        |
|visualizacao dos dados nos displays OLED, com a utilização do protocolo   |
|I2C.                                                                      |
|--------------------------------------------------------------------------|
|Passos para fazer antes de rodar esse codigo na placa.                    |                
|                                                                          |
|1. Carregar o bootloader com outro Arduino antes de rodar o programa,     | 
|utilizando o codigo Arduino ISP, vide guia(ISP.md) no repositorio.        |
|                                                                          |
|                                                                          |
|2. Antes de inicializar o códico conferir com o I2C Scanner               |
|os endereços dos displays.                                                |
|                                                                          |
\-------------------------------------------------------------------------*/

// Incluir biblioteca do display

#include <Adafruit_SSD1306.h>

// Definir botao de reset do display

#define OLED_RESET     -1 // -1 mesmo reset do arduino

// Declara os displays com seus respectivos botoes de reset

Adafruit_SSD1306 Display1(OLED_RESET); 
Adafruit_SSD1306 Display2(OLED_RESET);

float bat1;
float bat2;
float bat3;
float bat4;

void setup() {
  
  //Serial.begin(9600); // Caso queira realizar alguns testes

  // Portas digitais para o controle de carga da bateria feito pelo Rele
  for(int i=2;i<5;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,1);
  }
  
  // Botao para alternar entre posicao de ajuste e carregamento
  pinMode(5,INPUT);

  // Endereco I2C do display1
  Display1.begin(SSD1306_SWITCHCAPVCC, 0X3D);// Verificar endereço com o I2C Scanner
  Display1.clearDisplay();
  Display1.display();
  
  // Endereco I2C do display2
  Display2.begin(SSD1306_SWITCHCAPVCC, 0X3C);// Verificar endereço com o I2C Scanner
  Display2.clearDisplay();
  Display2.display();

}

// Ajuste de tensao regulada
// Rele eh ativado --> baterias nao estao sendo carregadas
void ajuste(){
  
  digitalWrite(2,1);
  digitalWrite(3,1);
  digitalWrite(4,1);
  digitalWrite(5,1);
  
  Display1.setTextSize(2);
  Display1.setTextColor(WHITE);
  Display1.setCursor(0,0);
  Display1.println("Tensao de Alimentacao");
  Display1.setCursor(0,10);
  bat1 = analogRead(A0)*5.0*100000.0/255.0*10000.0;
  Display1.print(bat1);
  Display1.print(" V");
  
  Display1.display();
  Display1.clearDisplay();
  
}
void loop(){

  if(!digitalRead(5)){
    ajuste();
  }
  
  else{
    Display1.setTextSize(1);
    Display1.setTextColor(WHITE);
    Display1.setCursor(0,0);
    Display1.println("BAT1");
    Display1.setCursor(0,10);
    bat1 = analogRead(A0)*5.0*100000.0/255.0*10000.0;
    Display1.print(bat1);
    Display1.print(" V");
    Display1.print(" / ");
    
    if(bat1 < 12.0){
      Display1.print((bat1/12.0)*100.0);
      Display1.println(" %");
      digitalWrite(2,0);
    }
    else{
      digitalWrite(2,1);
      Display1.println("100 %");
    }
  
    Display1.setCursor(0,35);
    Display1.println("BAT2");
    Display1.setCursor(0,45);
    bat2 = analogRead(A1)*5.0*100000.0/255.0*10000.0;
    Display1.print(bat2);
    Display1.print(" V");
    Display1.print(" / ");
    if(bat2 < 12.0){
      Display1.print((bat2/12.0)*100.0);
      Display1.println(" %");
      digitalWrite(2,0);
    }
    else{
      digitalWrite(2,1);
      Display1.println("100 %");
    }
  
    Display1.display();
    Display1.clearDisplay();
  
    Display2.setTextSize(1);
    Display2.setTextColor(WHITE);
    Display2.setCursor(0,0);
    Display2.println("BAT3");
    Display2.setCursor(0,10);
    bat3 = analogRead(A2)*5.0*100000.0/255.0*10000.0;
    Display2.print(bat3);
    Display2.print(" V");
    Display2.print(" / ");
    if(bat3 < 12.0){
      Display2.print((bat3/12.0)*100.0);
      Display2.println(" %");
      digitalWrite(2,0);
    }
    else{
      digitalWrite(2,1);
      Display2.println("100 %");
    }
    Display2.setCursor(0,35);
    Display2.println("BAT4");
    Display2.setCursor(0,45);
    bat4 = analogRead(A3)*5.0*100000.0/255.0*10000.0;
    Display2.print(bat4);
    Display2.print(" V");
    Display2.print(" / ");
    if(bat4 < 12.0){
      Display2.print((bat4/12.0)*100.0);
      Display2.println(" %");
      digitalWrite(2,0);
    }
    else{
      digitalWrite(2,1);
      Display2.println("100 %");
    }
  
    Display2.display();
    Display2.clearDisplay();
  }

}
