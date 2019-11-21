#ifndef MOVIMENTACAO_H
#define MOVIMENTACAO_H

#include <string>

using namespace std;

typedef struct dataNow {
	int dia;
	int mes;
	int ano;
}dataNow;

class Movimentacao {
	public:
	Movimentacao(string d, char dc, double v);
	
	Movimentacao();
	
	Movimentacao(int dia, int mes, int ano, string d, char dc, double v);
	
	dataNow get_dataMov();
	
	string get_descricao();
	
	char get_debitoCredito();
	
	double get_valor();
	
	private:
	dataNow dataMov;
	string descricao;
	char debitoCredito;
	double valor;
};

#endif