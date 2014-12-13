#include <coordonnes2d.h>

Coordonnes2D::Coordonnes2D()
{
    this->m_X = 0;
    this->m_Y = 0;
    //ctor
}

Coordonnes2D::Coordonnes2D(int X, int Y)
{
    this->m_X = X;
    this->m_Y = Y;
    //ctor
}

Coordonnes2D::Coordonnes2D(const Coordonnes2D& source){
	this->m_X = source.getX();
	this->m_Y = source.getY();
	this->m_cadran = source.getCadran();
}


Coordonnes2D::~Coordonnes2D()
{
    //dtor
}
