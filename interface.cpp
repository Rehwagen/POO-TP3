#include "interface.h"
#include <iostream>
#include <string>
#include <vector>
#include "movimentacao.h"
#include "cliente.h"
#include "conta.h"
#include "banco.h"
#include <sstream>
#include <fstream>

using namespace std;

string nomeBanco = "POO";

Interface::Interface(Banco c){
	B = c;
}

void Interface::novoCliente(){
	string nome, cpf, endereco, fone;
	cout << "Digite o nome completo do cliente: ";
	getline(cin, nome);
	cout << "Digite o cpf do cliente (apenas numeros): ";
	cin >> cpf;
	cout << "Digite o endereco do cliente: ";
	cin.ignore();
	getline(cin, endereco);
	cout << "Digite o telefone do cliente (apenas numeros): ";
	cin >> fone;
	Cliente c(nome, cpf, endereco, fone);
	B.novoCliente(c);
	cout << endl;
	system("pause");
	menu();
}

void Interface::novaConta(){
	vector<Cliente> aux;
	aux = B.listaClientes();
	string cpf;
	cout << "Digite o cpf do cliente para o qual deseja-se criar uma conta (apenas numeros): ";
	cin >> cpf;
	for(vector<Cliente>::iterator it = aux.begin(); it != aux.end(); ++it){
		if(it->get_cpf_cnpj() == cpf){
			B.novaConta(*it);
			break;
		}
	}
	cout << endl;
	system("pause");
	menu();
}

void Interface::excluirCliente(){
	string cpf;
	cout << "Digite o cpf do cliente que deseja-se excluir (apenas numeros): ";
	cin >> cpf;
	B.excluirCliente(cpf);
	cout << endl;
	system("pause");
	menu();
}

void Interface::excluirConta(){
	int num;
	cout << "Digite o numero da conta a ser excluida: ";
	cin >> num;
	B.excluirConta(num);
	cout << endl;
	system("pause");
	menu();
}

void Interface::deposito(){
	int num;
	double val;
	cout << "Digite o numero da conta a ser depositado o valor: ";
	cin >> num;
	cout << "Digite o valor do deposito: ";
	cin >> val;
	B.deposito(num, val);
	cout << endl;
	system("pause");
	menu();
}

void Interface::saque(){
	int num;
	double val;
	cout << "Digite o numero da conta a ser sacada o valor: ";
	cin >> num;
	cout << "Digite o valor a ser sacado: ";
	cin >> val;
	B.saque(num, val);
	cout << endl;
	system("pause");
	menu();
}

void Interface::transferencia(){
	int numa, numb;
	double val;
	cout << "Digite o numero da conta de origem: ";
	cin >> numa;
	cout << "Digite o numero da conta de destino: ";
	cin >> numb;
	cout << "Digite o valor da transferencia: ";
	cin >> val;
	B.transferencia(numa, numb, val);
	cout << endl;
	system("pause");
	menu();
}

void Interface::tarifa(){
	B.cobrarTarifa();
	cout << "Tarifa cobrada!" << endl;
	cout << endl;
	system("pause");
	menu();
}

void Interface::CPMF(){
	B.cobrarCPMF();
	cout << "CPMF cobrada com sucesso!" << endl;
	cout << endl;
	system("pause");
	menu();
}

void Interface::saldo(){
	int num;
	cout << "Digite o numero da conta: ";
	cin >> num;
	cout << "R$" << B.saldo(num);
	cout << endl;
	system("pause");
	menu();
}

void Interface::extrato(){
	dataNow dataI, dataF;
	vector<Movimentacao> mov;
	string s;
	int num;
	cout << "Digite o numero da conta: ";
	cin >> num;
	cout << "Digite a data de inicio e a data final. Caso nao queira especificar alguma data, digite um caracter inválido." << endl << "Data de inicio: ";
	cin >> s;
	if((s[0] < '0') || (s[0] > '9')){
		mov = B.extrato(num);
		for(vector<Movimentacao>::iterator it = mov.begin(); it != mov.end(); ++it){
			cout << it->get_dataMov().dia << "/" << it->get_dataMov().mes << "/" << it->get_dataMov().ano << "  -  " << it->get_descricao() << " -> R$" << it->get_valor() << endl;
		}
		cout << "Saldo: R$" << B.saldo(num) << endl;
		system("pause");
		menu();
	}
	stringstream h;
	h << s;
	getline(h, s, '/');
	dataI.dia = stoi(s);
	getline(h, s, '/');
	dataI.mes = stoi(s);
	getline(h, s, '/');
	dataI.ano = stoi(s);
	cout << "Data final: ";
	cin >> s;
	if((s[0] < '0') || (s[0] > '9')){
		mov = B.extrato(num, dataI);
		for(vector<Movimentacao>::iterator it = mov.begin(); it != mov.end(); ++it){
			cout << it->get_dataMov().dia << "/" << it->get_dataMov().mes << "/" << it->get_dataMov().ano << "  -  " << it->get_descricao() << " -> R$" << it->get_valor() << endl;
		}
		cout << "Saldo: R$" << B.saldo(num) << endl;
		system("pause");
		menu();
	}
	stringstream w;
	w << s;
	getline(w, s, '/');
	dataF.dia = stoi(s);
	getline(w, s, '/');
	dataF.mes = stoi(s);
	getline(w, s, '/');
	dataF.ano = stoi(s);
	mov = B.extrato(num, dataI, dataF);
	for(vector<Movimentacao>::iterator it = mov.begin(); it != mov.end(); ++it){
		cout << it->get_dataMov().dia << "/" << it->get_dataMov().mes << "/" << it->get_dataMov().ano << "  -  " << it->get_descricao() << " -> R$" << it->get_valor() << endl;
	}
	cout << "Saldo: R$" << B.saldo(num) << endl;
	system("pause");
	menu();
}

void Interface::listaClientes(){
	vector<Cliente> aux;
	aux = B.listaClientes();
	for(vector<Cliente>::iterator it = aux.begin(); it != aux.end(); ++it){
		cout << it->get_nomeCliente() << "    CPF/CNPJ: " << it->get_cpf_cnpj() << "    Endereco: " << it->get_endereco() << "    Telefone: " << it->get_fone() << endl;
	}
	system("pause");
	menu();
}

void Interface::listaContas(){
	vector<Conta> aux;
	aux = B.listaContas();
	for(vector<Conta>::iterator it = aux.begin(); it != aux.end(); ++it){
		cout << it->get_numConta() << "  -  R$" << it->get_saldo() << endl;
	}
	system("pause");
	menu();
}

void Interface::gravar(){
	B.gravar();
}

void Interface::menu(){
	gravar();
	system("cls");
	cout << endl;
	string s;
	cout << "Boas vindas ao banco " << nomeBanco << ". O que voce deseja fazer? Opcoes:" << endl;
	cout << "EXTRATO || CADASTRAR CLIENTE || CRIAR CONTA || EXCLUIR CLIENTE || EXCLUIR CONTA || DEPOSITAR || SAQUE ||" << endl << "TRANSFERIR || TARIFA || CPMF || SALDO || EXTRATO || LISTAR CLIENTES || LISTAR CONTAS || SAIR" << endl;
	getline(cin, s);
	cout << endl;
	if((s == "extrato") || (s == "EXTRATO")){
		extrato();
	}
	if((s == "cadastrar cliente") || (s == "CADASTRAR CLIENTE")){
		novoCliente();
	}
	if((s == "criar conta") || (s == "CRIAR CONTA")){
		novaConta();
	}
	if((s == "excluir cliente") || (s == "CRIAR CONTA")){
		excluirCliente();
	}
	if((s == "saque") || (s == "SAQUE")){
		saque();
	}
	if((s == "transferir") || (s == "TRANSFERIR")){
		transferencia();
	}
	if((s == "tarifa") || (s == "TARIFA")){
		tarifa();
	}
	if((s == "cpmf") || (s == "CPMF")){
		CPMF();
	}
	if((s == "saldo") || (s == "SALDO")){
		saldo();
	}
	if((s == "excluir conta") || (s == "EXCLUIR CONTA")){
		excluirConta();
	}
	if((s == "depositar") || (s == "DEPOSITAR")){
		deposito();
	}
	if((s == "listar clientes") || (s == "LISTAR CLIENTES")){
		listaClientes();
	}
	if((s == "listar contas") || (s == "LISTAR CONTAS")){
		listaContas();
	}
	if((s == "sair") || (s == "SAIR")){
		B.gravar();
		exit(0);
	}
	else{
		menu();
	}
}

int main(){
	Banco c(nomeBanco);
	c.ler();
	Interface I(c);
	I.menu();
	return 0;
}