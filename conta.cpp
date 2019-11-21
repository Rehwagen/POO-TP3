#include "conta.h"
#include "movimentacao.h"
#include "cliente.h"
#include <string>
#include <vector>
#include <ctime>

using namespace std;

Conta::Conta(Cliente c){
	cliente = c;
	saldo = 0;
	numConta = this->proximoNumConta;
	movimentacoes.clear();
	this->proximoNumConta++;
}

int Conta::proximoNumConta = 1;

Conta::Conta(Cliente c, int num, double sal, vector<Movimentacao> mov){
	cliente = c;
	numConta = num;
	saldo = sal;
	movimentacoes = mov;
}

int Conta::get_numConta(){
	return numConta;
}

double Conta::get_saldo(){
	return saldo;
}

Cliente Conta::get_cliente(){
	return cliente;
}

vector<Movimentacao> Conta::get_movimentacoes(){
	return movimentacoes;
}

void Conta::debitar(double valor, string descricao){
	if(((saldo - valor) < 0) || (valor == 0)){}
	else{
		Movimentacao x(descricao, 'D', valor);
		movimentacoes.push_back(x);
		saldo -= valor;
	}
}

void Conta::creditar(double valor, string descricao){
	if(valor == 0){}
	else{
		Movimentacao x(descricao, 'C', valor);
		movimentacoes.push_back(x);
		saldo += valor;
	}
}

vector<Movimentacao> Conta::extrato(){
	dataNow aux;
	vector<Movimentacao> mov;
	time_t t = time(0);
	tm* now = localtime(&t);
	aux.dia = now->tm_mday;
	aux.mes = now->tm_mon + 1;
	aux.ano = now->tm_year + 1900;
	for(vector<Movimentacao>::iterator it = movimentacoes.begin(); it != movimentacoes.end(); ++it){
		if((it->get_dataMov().mes == aux.mes) && (it->get_dataMov().ano == aux.ano)){
			mov.push_back(*it);
		}
	}
	return mov;
}

vector<Movimentacao> Conta::extrato(dataNow I){
	int di = I.dia + (I.mes*100) + (I.ano * 10000);
	vector<Movimentacao> mov;
	for(vector<Movimentacao>::iterator it = movimentacoes.begin(); it != movimentacoes.end(); ++it){
		if(di <= (it->get_dataMov().dia + (it->get_dataMov().mes * 100) + (it->get_dataMov().ano * 10000))){
			mov.push_back(*it);
		}
	}
	return mov;
}

vector<Movimentacao> Conta::extrato(dataNow I, dataNow F){
	int di = I.dia + (I.mes*100) + (I.ano * 10000);
	int df = F.dia + (F.mes*100) + (F.ano * 10000);
	vector<Movimentacao> mov;
	for(vector<Movimentacao>::iterator it = movimentacoes.begin(); it != movimentacoes.end(); ++it){
		if((di <= (it->get_dataMov().dia + (it->get_dataMov().mes * 100) + (it->get_dataMov().ano * 10000))) && (df >= (it->get_dataMov().dia + (it->get_dataMov().mes * 100) + (it->get_dataMov().ano * 10000)))){
			mov.push_back(*it);
		}
	}
	return mov;
}