#ifndef CONTA_H
#define CONTA_H

#include <string>
#include <vector>
#include <ctime>
#include "movimentacao.h"
#include "cliente.h"

using std::string;
using std::vector;

class Conta {
	public:
	Conta(Cliente c);
	
	Conta(Cliente c, int num, double sal, vector<Movimentacao> mov);
	
	int get_numConta();
	
	double get_saldo();
	
	Cliente get_cliente();
	
	vector<Movimentacao> get_movimentacoes();
	
	void debitar(double valor, string descricao);
	
	void creditar(double valor, string descricao);
	
	vector<Movimentacao> extrato();
	
	vector<Movimentacao> extrato(dataNow dataI);
	
	vector<Movimentacao> extrato(dataNow dataI, dataNow dataF);
	
	private:
	int numConta;
	
	double saldo;
	
	Cliente cliente;
	
	vector<Movimentacao> movimentacoes;
	
	static int proximoNumConta;
};

#endif