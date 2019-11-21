#include "cliente.h"
#include <string>

using namespace std;

Cliente::Cliente(string n, string c, string e, string f){
	nomeCliente = n;
	cpf_cnpj = c;
	endereco = e;
	fone = f;
}

Cliente::Cliente(){}

string Cliente::get_nomeCliente(){
	return nomeCliente;
}

string Cliente::get_cpf_cnpj(){
	return cpf_cnpj;
}

string Cliente::get_endereco(){
	return endereco;
}

string Cliente::get_fone(){
	return fone;
}

void Cliente::set_nomeCliente(string n){
	nomeCliente = n;
}

void Cliente::set_cpf_cnpj(string c){
	cpf_cnpj = c;
}

void Cliente::set_endereco(string e){
	endereco = e;
}

void Cliente::set_fone(string f){
	fone = f;
}

bool Cliente::operator==(Cliente b){
	if((nomeCliente == b.nomeCliente) && (cpf_cnpj == b.cpf_cnpj) && (endereco == b.endereco) && (fone == b.fone)){
		return true;
	}
	else{
		return false;
	}
}