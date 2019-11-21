#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

using std::string;

class Cliente {
	public:
	Cliente(string n, string c, string e, string f);
	
	Cliente();
	
	string get_nomeCliente();
	
	string get_cpf_cnpj();
	
	string get_endereco();
	
	string get_fone();
	
	void set_nomeCliente(string n);
	
	void set_cpf_cnpj(string c);
	
	void set_endereco(string e);
	
	void set_fone(string f);
	
	bool operator==(Cliente b);
	
	private:
	string nomeCliente;
	string cpf_cnpj;
	string endereco;
	string fone;
};

#endif