#ifndef FENETRE_H
#define FENETRE_H

#include <string>
#include <SDL2/SDL.h>

class Fenetre
{
    public:
        /** Default constructor */
        Fenetre(std::string titre,boost::mpi::communicator *world, unsigned int longueur = 320, unsigned int hauteur = 320);
        /** Default destructor */
        virtual ~Fenetre();

        void main_loop();

        void runTER(std::string propsFile, int argc, char ** argv);

        /** Getters and setters */
        unsigned int getLongueur();
        unsigned int getHauteur();
        SDL_Window* getScreen();

    protected:
        boost::mpi::communicator *world;
        unsigned int m_largeur;
        unsigned int m_hauteur;
        std::string m_titre;
        SDL_Window *m_ecran;
        Uint32 m_bg_color;
    private:

};

#endif // FENETRE_H
