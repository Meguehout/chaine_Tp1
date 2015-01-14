#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QString>
#include<stdlib.h>

class Image
{
public:
    Image(): m_nbrLigne(0), m_nbrColone(0), m_niveauxDeGris(0){}
    void LoadImage(std::string fileSource);
    void sauveImage (std::string chemainDeSauve) const;
    int getIntensity (int ligneI, int coloneJ) const;
    void putIntensity (int ligneI, int coloneJ, int valIntensity);
    int getNbrLignes (){return m_nbrLigne;}
    int getNbrColones (){return m_nbrColone;}

protected:

    std::string m_typeFile;
    int m_nbrLigne;//hauteur
    int m_nbrColone;//largeur
    int m_niveauxDeGris;
    std::vector <std::vector <int> > m_bufferImage;
};

#endif // IMAGE_H
