#include <string>

using namespace std;



class Part
{
	string nome;
	string fornecedor;
	double preco;


public:

	Part(string nome = "", string fornecedor = "", double preco = 0) : nome(nome) , fornecedor(fornecedor),preco(preco)
	{};
	bool operator< (const Part & p1) const;
	bool operator==( const  Part &p2) const;
	string getNome();
	string getFornecedor();
	double getPreco();


};