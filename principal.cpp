#include "IPv4_ComClasse.h"

#include <iostream>
using namespace std;

int main() {
  IPv4_ComClasse p;
  setlocale(LC_ALL, "Portuguese");
  int opcao;
  string mascara;
  string ipv4;
  int cidr;
  do{
  cout<<"1. Enderecamento com classes."<<endl;
  cout<<"2. Enderecamento sem classe - mascara na notacao decimal"<<endl;
  cout<<"3. Enderecamento sem classe - mascara na notacao CIDR"<<endl;
  cout<<"0. Sair"<<endl;
  cout<<"Digite apcao: ";
    cin>>opcao;
  while(opcao <0|| opcao >3){cout<<"Opcao invalida Digite novamente: ";cin>>opcao;}
  switch (opcao)
  {
  case 1:
    cout << "Digite um endereço IPv4 (xxx.xxx.xxx.xxx): ";
    cin >> ipv4;
    cout<<endl;
    if (p.ValidarIPv4(ipv4) == false) {
      cout << "Endereco IPv4 invalido." << endl;
  }
    else{
      p.mostrarFinal();
  }
    cout<<endl;
    break;

  case 2:
  cout << "Digite um endereço IPv4 (xxx.xxx.xxx.xxx): ";
  cin >> ipv4;
  cout<<endl;
  if (p.ValidarIPv4(ipv4) == false) {
    cout << "Endereco IPv4 invalido!" << endl;
  }
  else{
  cout<<"Digite a Mascara (xxx.xxx.xxx.xxx): ";
  cin >> mascara;
    if (p.mascaraCIDR(mascara)) {
        p.mostrarFinal_SemClasse();
  }
    else{
      cout << "Mascara invalida!" << endl;
  } 
  }
  cout<<endl;break;

  case 3:
      cout << "Digite um endereço IPv4: ";
  cin >> ipv4;
  cout<<endl;
  if (p.ValidarIPv4(ipv4) == false) {
    cout << "Endereco IPv4 invalido." << endl;
  }
  else{
  cout<<"Digite a Mascara em CIDR (DECIMAL x): ";
  cin >> cidr;
    if (p.mascara_em_CIDR(cidr)) {
        p.set_Cidr_const(cidr);
        p.mostrar_SemClasse_CIDR();
  }
    else{
      cout << "Mascara invalida!" << endl;
  } 
  }
  cout<<endl;break;
  
  default:
    break;
  return 0;
  }  


  }while(opcao!= 0);

}