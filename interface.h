#ifndef INTERFACE_H
#define INTERFACE_H

#include "banco.h"
#include <string>
#include <vector>
#include "conta.h"
#include "movimentacao.h"
#include "cliente.h"

using namespace std;

class Interface {
	public:
	Interface(Banco c);
	
	void menu();
	
	void novoCliente();
	
	void novaConta();
	
	void excluirCliente();
	
	void excluirConta();
	
	void deposito();
	
	void saque();
	
	void transferencia();
	
	void tarifa();
	
	void CPMF();
	
	void saldo();
	
	void extrato();
	
	void gravar();
	
	void listaClientes();
	
	void listaContas();
	
	private:
	Banco B;
	
};


#endif