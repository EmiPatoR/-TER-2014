#ifndef COULEUR_H
#define COULEUR_H

#include <SDL/SDL.h>

class Couleur {
public:
	/** Default constructor */
	Couleur(Uint8 R, Uint8 G, Uint8 B, SDL_PixelFormat* format);
	/** Default destructor */
	virtual ~Couleur();
	/** Getters */
	Uint32 getColor();
	SDL_Color getSDLColor();
	Uint8 getR();
	Uint8 getG();
	Uint8 getB();
	SDL_PixelFormat* getFormat();
	/** Setters */
	void setColor(Uint32 val);
	void setSDLColor(SDL_Color val);
	void setR(Uint8 val);
	void setG(Uint8 val);
	void setB(Uint8 val);
	void setRGB(Uint8 valR, Uint8 valG, Uint8 valB);
	void setFormat(SDL_PixelFormat* val);
	/** Static methods */
	static Uint32 Bleu(SDL_PixelFormat* format);
	static Uint32 Rouge(SDL_PixelFormat* format);
	static Uint32 Vert(SDL_PixelFormat* format);
	static Uint32 Noir(SDL_PixelFormat* format);
	static Uint32 Blanc(SDL_PixelFormat* format);
protected:
	Uint8 m_R;
	Uint8 m_G;
	Uint8 m_B;
	SDL_Color m_color;
	Uint32 m_color_uint32;
	SDL_PixelFormat* m_format;
private:
};

#endif // COULEUR_H