#ifndef COORDONNES2D_H
#define COORDONNES2D_H


class Coordonnes2D
{
    public:
        /** Default constructor */
        Coordonnes2D();
        Coordonnes2D(int X, int Y);
        /** Default destructor */
        virtual ~Coordonnes2D();
        int getX();
        int getY();
    protected:
        int m_X;
        int m_Y;
    private:
};

#endif // COORDONNES2D_H
