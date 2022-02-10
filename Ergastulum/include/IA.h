#ifndef IA_H
#define IA_H

#include "SFML/System.hpp"

#include "Entidade.h"
#include "ManipuladorDeEntrada.h"

class Entidade;
class ManipuladorDeEntrada;

class IA
{
public:
	virtual void atualizar(Entidade *owner)=0; 
private:
};


class IAJogador : public IA
{
public:	
	IAJogador(ManipuladorDeEntrada* manipulador);
	IAJogador();

	void atualizar(Entidade* owner);
private:
	ManipuladorDeEntrada* m_manipulador;
};

#endif