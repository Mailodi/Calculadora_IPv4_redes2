#ifndef IPV4_COMCLASSE_H
#define IPV4_COMCLASSE_H
#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <math.h>
using namespace std;

class IPv4_ComClasse
{
private:
  int todasPartes[4] = {0};
  int todasParte_Mascara[4] = {0};
  int quant_1_Binarios = 0;
  int host = 0;
  int rede[4];
  int broadcast[4];
  int inicial[4], final[4];
  int cidr_const;
  string mascara3;
public:

bool ValidarIPv4(const string& ipv4) {
  // dividir a string do endereço em partes usando '.' como separador
  stringstream aux(ipv4);
  string umaParte;
  
  int i = 0;
  while (getline(aux, umaParte, '.')) {
    if (i >= 4) {
      // verifica se o endereço tem mais de 4 partes
      return false;
    }

    try {
    //Converte uma sequência de caracteres em um número inteiro.
      int uma_Parte = stoi(umaParte);
    //Verificar o valor de cada parte
      if (uma_Parte < 0 || uma_Parte > 255) {
        return false;
      }

      todasPartes[i] = uma_Parte;
      //Valida o Endereço
      if(todasPartes[0] == 255 ||todasPartes[0]== 127 ||todasPartes[0]== 0){return false;}

    } catch (invalid_argument e) {
      cout<<endl<<" A parte não é um número válido";
      return false;
    }
    i++;
  }
  if (i <= 3) {
    // Verifica se o endereço tem menos de 4 partes
    return false;
  }
  return true;
}

char classeIP(){
  if(todasPartes[0]>=1 && todasPartes[0]<=127){return 'A';}
  if(todasPartes[0]>=128 && todasPartes[0]<=191){return 'B';}
  if(todasPartes[0]>=192 && todasPartes[0]<=223){return 'C';}
  if(todasPartes[0]>=224 && todasPartes[0]<=239){return 'D';}
  if(todasPartes[0]>=240 && todasPartes[0]<=255){return 'E';}
  }

string mascaraIP(){
  switch (classeIP())
  {
  case 'A' : return "255.0.0.0";break;
  case 'B' : return "255.255.0.0";break;
  case 'C' : return "255.255.255.0";break;
  case 'D' : return "Mascara de Classe D reservado para Multicast";break;
  case 'E' : return "Mascara de Classe E endereco reservado";break;
  default: cout<<"Invalido";
    break;
  }
}

void mostraMascara(){
    for(int i=0;i<=3;i++){
    cout<<todasParte_Mascara[i];
    if(i!=3){cout<<".";}
    }
}

bool mascaraCIDR(const string& mascara){
stringstream aux2 (mascara);
string umaParte_Mascara;
int i = 0;
int cont_1 = 0;

while (getline(aux2, umaParte_Mascara, '.')) {
      if (i >= 4) {
      // A mascara tem mais de 4 partes
      return false;
    }

  try {
//Converte uma sequência de caracteres em um número inteiro.
  int uma_Parte_Mascara = stoi(umaParte_Mascara);
  todasParte_Mascara[i] = uma_Parte_Mascara;
//Verifica cada parte da mascara para ver se e valida
if(todasParte_Mascara[i] != 0){
    switch (todasParte_Mascara[i])
    {
    case 255 : cont_1 += 8;
      break;
    case 254 : cont_1 += 7;
      break;
    case 252 : cont_1 += 6;
      break;          
    case 248 : cont_1 += 5;
      break;
    case 240 : cont_1 += 4;
      break;
    case 224 : cont_1 += 3;
      break;
    case 192 : cont_1 += 2;
      break;   
    case 128 : cont_1 += 1;
      break;                          
    default: return false;
      break;
    }
}

  } catch (invalid_argument e) {
      cout<<endl<<" A parte não é um número válido";
      return false;
}
i++;
}
this->quant_1_Binarios = cont_1;
return true;
}


int retorna_Mascara(){
  mascaraCIDR(mascaraIP());
  return quant_1_Binarios;
}

int retorna_Mascara2(){
  return quant_1_Binarios;
}


void num_Host(){
  int aux ;
  int bits = 0;
  for(int i=0;i<=3;i++){
  aux = todasParte_Mascara[i] - 255;
  if(aux < 0){aux = aux * (-1);}
  if(aux!= 0){
  bitset<8> binario (aux);
  for (int i = 0; i < 8; i++) {
      if (binario[i] == 1) {
          bits++;
        }
    }
  }
  }
    this->host  = pow(2, bits) - 2;
}

int retorna_Host(){
  return host;
}


void num_rede(){
      // Calcular endereço de rede
    for (int i = 0; i < 4; i++) {
        rede[i] = todasPartes[i] & todasParte_Mascara[i];
    }
}

void num_broadcast(){
      // Calcular endereço de broadcast
    for (int i = 0; i < 4; i++) {
        broadcast[i] = todasPartes[i] | (~todasParte_Mascara[i] & 0xFF);
    }
}
void ipFinal_Inicial(){
  for (int i = 0; i < 4; i++) {
        if (i == 3) {
            inicial[i] = rede[i] + 1;
            final[i] = (rede[i] & todasParte_Mascara[i]) + (~todasParte_Mascara[i] & 0xFF) - 1;
        } else {
            inicial[i] = rede[i];
            final[i] = rede[i];
        }
    }
}

bool mascara_em_CIDR( int cidr){
  try{
  if(cidr < 0 || cidr>32){return false;}
  }catch(invalid_argument e){
    cout<<endl<<"Erro";
  }
  this->cidr_const = cidr;
  return true;
}

string mascara_Padrao_CIDR(){
      // Converte o CIDR para o formato de máscara padrão
    string mascara = "";
    int aux = this->cidr_const;
    for (int i = 0; i < 4; i++) {
        if (i > 0) {
            mascara += ".";
        }
        if (aux >= 8) {
            mascara += "255";
            aux -= 8;
        } else {
            int valor = 0;
            for (int j = 0; j < aux; j++) {
                valor += pow(2, 7 - j);
            }
            mascara += to_string(valor);
            aux= 0;
        }
    }  
    this->mascara3 = mascara;
    return mascara;
}

int retornar_CIDR_3(){
  return this->cidr_const;
}

void mover_Mascara(){
  string aux1 = mascara_Padrao_CIDR();
  stringstream aux(aux1);
  string umaParte;
  
  int i = 0;
  while (getline(aux, umaParte, '.')) {
    try {
      int uma_Parte = stoi(umaParte);
      todasParte_Mascara[i] = uma_Parte;
      } catch (invalid_argument e) {
      cout<<endl<<" A parte não é um número válido";
    }
    i++;
  }
    if (i <= 3) {
    cout<<"O endereço tem menos de 4 partes";
  }
}

void set_Cidr_const(int cidr){
  this->cidr_const = cidr;
}

void mostrarFinal(){
  //Mostra o menu endereço IP com classe
  cout<<"Endereco IP: ";
  for(int i=0;i<=3;i++){
    cout<<todasPartes[i];
    if(i!=3){cout<<".";}
    }
  
  cout << endl; 
  if(classeIP() == 'D' || classeIP() == 'E'){
     cout<<mascaraIP();
     cout<<endl;
  }
  else{
  cout<<"Classe: " << classeIP() << endl;
  cout<<"Mascara: " << mascaraIP() << endl;
  cout<<"Mascara CIDR: /" << retorna_Mascara() << endl;
  num_Host(); 
  cout<<"Numero de Host: "<<retorna_Host(); 
  cout << endl; 

  num_rede();cout<<"Rede: ";
    for(int i=0;i<=3;i++){
    cout<<rede[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 
  
  num_broadcast();
  cout<<"Brodcast: ";
    for(int i=0;i<=3;i++){
    cout<<broadcast[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  ipFinal_Inicial();

  cout<<"IP Inicial: ";
    for(int i=0;i<=3;i++){
    cout<<inicial[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  cout<<"IP Final: ";
    for(int i=0;i<=3;i++){
    cout<<final[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 
}
}

void mostrarFinal_SemClasse(){
  //Mostra menu do endereço IP sem classe
    cout<<"Endereco IP: ";

  for(int i=0;i<=3;i++){
    cout<<todasPartes[i];
    if(i!=3){cout<<".";}
    }
  
  cout << endl; 

  cout<<"Mascara: ";
  mostraMascara();
  cout<<endl;

  cout<<"Mascara CIDR: /"<<retorna_Mascara2() << endl;
  num_Host(); 
  cout<<"Numero de Host: "<<retorna_Host(); 
  cout << endl; 

    num_rede();cout<<"Rede: ";
    for(int i=0;i<=3;i++){
    cout<<rede[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  num_broadcast();
  cout<<"Brodcast: ";
    for(int i=0;i<=3;i++){
    cout<<broadcast[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  ipFinal_Inicial();

  cout<<"IP Inicial: ";
    for(int i=0;i<=3;i++){
    cout<<inicial[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  cout<<"IP Final: ";
    for(int i=0;i<=3;i++){
    cout<<final[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

}

void mostrar_SemClasse_CIDR(){
  //Mostra menu IP sem classe CIDR
  cout<<"Endereco IP: ";
  for(int i=0;i<=3;i++){
    cout<<todasPartes[i];
    if(i!=3){cout<<".";}
    }
  
  cout << endl; 

  cout<<"Mascara: ";
  mascara_Padrao_CIDR();
  cout<<this->mascara3<< endl;

  cout<<"Mascara CIDR: /" << retornar_CIDR_3() << endl;
  mover_Mascara();

  num_Host();
  cout<<"Numero de Host: "<<retorna_Host();

    cout << endl; 

    num_rede();cout<<"Rede: ";
    for(int i=0;i<=3;i++){
    cout<<rede[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  num_broadcast();
  cout<<"Brodcast: ";
    for(int i=0;i<=3;i++){
    cout<<broadcast[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  ipFinal_Inicial();

  cout<<"IP Inicial: ";
    for(int i=0;i<=3;i++){
    cout<<inicial[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 

  cout<<"IP Final: ";
    for(int i=0;i<=3;i++){
    cout<<final[i];
    if(i!=3){cout<<".";}
    }
  cout << endl; 
}

};

#endif