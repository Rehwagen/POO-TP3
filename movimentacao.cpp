#include "movimentacao.h"
#include <string>
#include <ctime>

using namespace std;

Movimentacao::Movimentacao(){}

Movimentacao::Movimentacao(string d, char dc, double v){
	time_t t = time(0);
	tm* now = localtime(&t);
	descricao = d;
	debitoCredito = dc;
	valor = v;
	dataMov.dia = now->tm_mday;
	dataMov.mes = now->tm_mon + 1;
	dataMov.ano = now->tm_year + 1900;
}

Movimentacao::Movimentacao(int dia, int mes, int ano, string d, char dc, double v){
	dataMov.dia = dia;
	dataMov.mes = mes;
	dataMov.ano = ano;
	descricao = d;
	debitoCredito = dc;
	valor = v;
}

dataNow Movimentacao::get_dataMov(){
	return dataMov;
}

string Movimentacao::get_descricao(){
	return descricao;
}

char Movimentacao::get_debitoCredito(){
	return debitoCredito;
}

double Movimentacao::get_valor(){
	return valor;
}