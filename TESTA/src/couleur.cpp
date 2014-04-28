#include <couleur.h>

Couleur::Couleur(Uint8 R, Uint8 G, Uint8 B, SDL_PixelFormat* format)
{
	this->m_format = format;

	this->m_color.r = R;
	this->m_R = R;

	this->m_color.g = G;
	this->m_G = G;

	this->m_color.b = B;
	this->m_B = B;

	this->m_color_uint32 = SDL_MapRGB(this->m_format,R,G,B);

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
SDL_PixelFormat* Couleur::getFormat(){return this->m_format;}

/** Setters */
void Couleur::setColor(Uint32 val){
	SDL_GetRGB(val,this->m_format,&(this->m_R),&(this->m_G),&(this->m_B));
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
	this->m_color_uint32 = SDL_MapRGB(this->m_format,this->m_R,this->m_G,this->m_B);
	this->m_color.r = this->m_R;
}

void Couleur::setG(Uint8 val){
	this->m_G = val;
	this->m_color_uint32 = SDL_MapRGB(this->m_format,this->m_R,this->m_G,this->m_B);
	this->m_color.g = this->m_G;
}

void Couleur::setB(Uint8 val){
	this->m_B = val;
	this->m_color_uint32 = SDL_MapRGB(this->m_format,this->m_R,this->m_G,this->m_B);
	this->m_color.b = this->m_B;
}

void Couleur::setRGB(Uint8 valR, Uint8 valG, Uint8 valB){
	this->m_R = valR;
	this->m_G = valG;
	this->m_B = valB;
	this->m_color_uint32 = SDL_MapRGB(this->m_format,this->m_R,this->m_G,this->m_B);
	this->m_color.r = this->m_R;
	this->m_color.g = this->m_G;
	this->m_color.b = this->m_B;
}

void Couleur::setFormat(SDL_PixelFormat* val){
	this->m_format = val;
}

/** Static methods */
Uint32 Couleur::Bleu(SDL_PixelFormat* format){return SDL_MapRGB(format,0,0,255);}
Uint32 Couleur::Rouge(SDL_PixelFormat* format){return SDL_MapRGB(format,255,0,0);}
Uint32 Couleur::Vert(SDL_PixelFormat* format){return SDL_MapRGB(format,0,255,0);}
Uint32 Couleur::Noir(SDL_PixelFormat* format){return SDL_MapRGB(format,0,0,0);}
Uint32 Couleur::Blanc(SDL_PixelFormat* format){return SDL_MapRGB(format,255,255,255);}
