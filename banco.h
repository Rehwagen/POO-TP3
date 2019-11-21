#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <vector>
#include "conta.h"
#include "movimentacao.h"
#include "cliente.h"

using namespace std;

class Banco {
	public:
	Banco(string nome);
	
	Banco();
	
	void novoCliente(Cliente c);
	
	void novaConta(Cliente c);
	
	void novaConta(Conta c);
	
	void excluirCliente(string cpf_cnpj); //Nao exclui se o cliente tiver uma conta
	
	void excluirConta(int numeroConta);
	
	void deposito(int numeroConta, double valor);
	
	void saque(int numeroConta, double valor);
	
	void transferencia(int numeroContaOrigem, int numeroContaDestino, double valor);
	
	void cobrarTarifa();
	
	void cobrarCPMF();
	
	double saldo(int numeroConta);
	
	vector<Movimentacao> extrato(int numeroConta);
	
	vector<Movimentacao> extrato(int numeroConta, dataNow dataI);
	
	vector<Movimentacao> extrato(int numeroConta, dataNow dataI, dataNow dataF);
	
	vector<Cliente> listaClientes();
	
	vector<Conta> listaContas();
	
	void gravar();
	
	void ler();
	
	private:
	string nomeBanco;
	
	vector<Cliente> clientes;
	
	vector<Conta> contas;
};

#endif