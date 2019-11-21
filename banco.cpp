#include <string>
#include <vector>
#include "banco.h"
#include "conta.h"
#include "movimentacao.h"
#include "cliente.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Banco::Banco(string nome){
	nomeBanco = nome;
	clientes.clear();
	contas.clear();
}

Banco::Banco(){}

void Banco::novoCliente(Cliente c){
	clientes.push_back(c);
}

void Banco::novaConta(Cliente c){
	Conta x(c);
	contas.push_back(x);
}

void Banco::novaConta(Conta c){
	contas.push_back(c);
}

void Banco::excluirCliente(string cpf_cnpj){
	for(vector<Cliente>::iterator it = clientes.begin(); it != clientes.end(); ++it){
		if(it->get_cpf_cnpj() == cpf_cnpj){
			for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
				if(itc->get_cliente() == *it){
					return;
				}
			}
			clientes.erase(it);
		}
	}
}
	
void Banco::excluirConta(int numeroConta){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroConta){
			contas.erase(itc);
			return;
		}
	}
}

void Banco::deposito(int numeroConta, double valor){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroConta){
			itc->creditar(valor, "Depósito");
			return;
		}
	}
}

void Banco::saque(int numeroConta, double valor){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroConta){
			itc->debitar(valor, "Saque");
			return;
		}
	}
}

void Banco::transferencia(int numeroContaOrigem, int numeroContaDestino, double valor){
	string a, b;
	a = to_string(numeroContaOrigem);
	b = to_string(numeroContaDestino);
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroContaOrigem){
			for(vector<Conta>::iterator itc2 = contas.begin(); itc2 != contas.end(); ++itc2){
				if(itc2->get_numConta() == numeroContaDestino){
					itc->debitar(valor, "Transferencia para a conta " + b);
					itc2->creditar(valor, "Transferencia da conta " + a);
				}
			}
		}
	}
}

void Banco::cobrarTarifa(){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		itc->debitar(15, "Cobranca de tarifa");
	}
}

void Banco::cobrarCPMF(){
	double total = 0;
	vector<Movimentacao> aux1;
	int aux;
	dataNow x;
	time_t t = time(0);
	tm* now = localtime(&t);
	x.dia = now->tm_mday;
	x.mes = now->tm_mon + 1;
	x.ano = now->tm_year + 1900;
	aux = x.dia + (x.mes*100) + (x.ano*10000) - 7;
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		aux1 = itc->get_movimentacoes();
		for(vector<Movimentacao>::iterator ita = aux1.begin(); ita != aux1.end(); ++ita){
			if((aux <= (ita->get_dataMov().dia + (ita->get_dataMov().mes * 100) + (ita->get_dataMov().ano * 10000))) && ita->get_debitoCredito() == 'D'){
				total += ita->get_valor();
			}
		}
		itc->debitar(total * 0.0038, "Cobranca de CPMF");
		total = 0;
	}
}

double Banco::saldo(int numeroConta){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroConta){
			return itc->get_saldo();
		}
	}
}

vector<Movimentacao> Banco::extrato(int numeroConta){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroConta){
			return itc->extrato();
		}
	}
}

vector<Movimentacao> Banco::extrato(int numeroConta, dataNow dataI){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroConta){
			return itc->extrato(dataI);
		}
	}
}

vector<Movimentacao> Banco::extrato(int numeroConta, dataNow dataI, dataNow dataF){
	for(vector<Conta>::iterator itc = contas.begin(); itc != contas.end(); ++itc){
		if(itc->get_numConta() == numeroConta){
			return itc->extrato(dataI, dataF);
		}
	}
}

vector<Cliente> Banco::listaClientes(){
	return clientes;
}

vector<Conta> Banco::listaContas(){
	return contas;
}

void Banco::gravar(){
	vector<Movimentacao> aux;
	ofstream contass;
	contass.open(nomeBanco + ".txt");
	ofstream movimentacao;
	for(vector<Cliente>::iterator itc = clientes.begin(); itc != clientes.end(); ++itc){
		contass << itc->get_nomeCliente() << "," << itc->get_cpf_cnpj() << "," << itc->get_endereco() << "," << itc->get_fone();
		for(vector<Conta>::iterator its = contas.begin(); its != contas.end(); ++its){
			if(its->get_cliente() == *itc){
				contass << "," << its->get_numConta() << "," << its->get_saldo();
			}
		}
		contass << "\n";
	}
	contass.close();
	for(vector<Conta>::iterator its = contas.begin(); its != contas.end(); ++its){
		aux = its->get_movimentacoes();
		movimentacao.open(its->get_cliente().get_nomeCliente() + ".txt");
		for(vector<Movimentacao>::iterator ita = aux.begin(); ita != aux.end(); ++ita){
			movimentacao << to_string(ita->get_dataMov().dia) << "," << ita->get_dataMov().mes << "," << ita->get_dataMov().ano << "," << ita->get_descricao() << "," << ita->get_debitoCredito() << "," << ita->get_valor() << "\n";
		}
		movimentacao.close();
	}
}

void Banco::ler(){
	char sig;
	int diaa, mess, anoo;
	vector<Movimentacao> movi;
	string nc, cpf, end, fon, nu, va, dia, mes, ano, desc, val, sigla, orig;
	ifstream contass;
	ifstream mov;
	contass.open(nomeBanco + ".txt");
	if(!contass.is_open()){
		return;
	}
	while(true){
		getline(contass, orig);
		if(contass.eof()){
			break;
		}
		stringstream h;
		h << orig;
		getline(h, nc, ',');
		getline(h, cpf, ',');
		getline(h, end, ',');
		getline(h, fon, ',');
		getline(h, nu, ',');
		getline(h, va, ',');
		Cliente cl(nc, cpf, end, fon);
		mov.open(nc + ".txt");
		while(true){
			getline(mov, orig);
			if(mov.eof()){
				break;
			}
			stringstream w;
			w << orig;
			getline(w, dia, ',');
			getline(w, mes, ',');
			getline(w, ano, ',');
			getline(w, desc, ',');
			getline(w, sigla, ',');
			getline(w, val, ',');
			sig = sigla[0];
			Movimentacao M(stoi(dia), stoi(mes), stoi(ano), desc, sig, stod(val));
			movi.push_back(M);
		}
		if(!mov.is_open()){
			movi.clear();
			novoCliente(cl);
		}
		else{
			Conta co(cl, stoi(nu), stod(va), movi);
			movi.clear();
			novoCliente(cl);
			novaConta(co);
			mov.close();
		}
	}
	contass.close();
	
}