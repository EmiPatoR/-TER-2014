#include <couleur.h>

Couleur::Couleur(Uint8 R, Uint8 G, Uint8 B)
{

	this->m_color.r = R;
	this->m_R = R;

	this->m_color.g = G;
	this->m_G = G;

	this->m_color.b = B;
	this->m_B = B;
	//ctor
}

Couleur::~Couleur()
{
	//dtor
}

/** Getters */
Uint32 Couleur::getColor(){return this->m_color_uint32;}
Uint8 Couleur::getR(){return this->m_R;}
Uint8 Couleur::getG(){return this->m_G;}
Uint8 Couleur::getB(){return this->m_B;}
SDL_Color Couleur::getSDLColor(){return this->m_color;}


/** Setters */
void Couleur::setColor(Uint32 val){
	this->m_color.r = this->m_R;
	this->m_color.g = this->m_G;
	this->m_color.b = this->m_B;
}

void Couleur::setSDLColor(SDL_Color val){
	this->m_color.r = val.r;
	this->m_color.g = val.g;
	this->m_color.b = val.b;
}

void Couleur::setR(Uint8 val){
	this->m_R = val;
	this->m_color.r = this->m_R;
}

void Couleur::setG(Uint8 val){
	this->m_G = val;
	this->m_color.g = this->m_G;
}

void Couleur::setB(Uint8 val){
	this->m_B = val;
	this->m_color.b = this->m_B;
}

void Couleur::setRGB(Uint8 valR, Uint8 valG, Uint8 valB){
	this->m_R = valR;
	this->m_G = valG;
	this->m_B = valB;
	this->m_color.r = this->m_R;
	this->m_color.g = this->m_G;
	this->m_color.b = this->m_B;
}
