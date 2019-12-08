#include "Part.h"

using namespace std;


bool Part::operator<(const Part &p1) const
{

	if (nome == p1.nome)
		return preco < p1.preco;

	return nome < p1.nome;

}

bool Part::operator==(const Part &p1) const
{


	return nome == p1.nome;


}


string Part::getNome()
{
	return nome;
}
string Part::getFornecedor()
{
	return fornecedor;
}

double Part::getPreco()
{
	return preco;
}