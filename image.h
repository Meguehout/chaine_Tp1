#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QString>
#include <stdlib.h>

#define NG 1
#define Couleur 3

class Image
{
public:
  Image(): m_nbrLigne(0), m_nbrColone(0), m_imageSize(0), m_nbrCanaux(0), m_niveauxDeGris(0){}
  void LoadImage(std::string fileSource);
  void sauveImage (std::string chemainDeSauve);
  int getIntensity (int pixel, int canal) const;
  void setIntensity (int pixel, int canal, int valIntensity);
  void setIntensityMax(int valeur){m_niveauxDeGris = valeur;}
  int getNbrLignes (){return m_nbrLigne;}
  int getNbrColones (){return m_nbrColone;}
  int getTailleImage (){return m_imageSize;}
  int getnbrCanaux (){return m_nbrCanaux;}
  std::vector<std::vector <int> > &getBuffer(){return m_bufferImage;}
  void normlaize();

  ~Image();

protected:

  std::string m_typeFile;
  int m_nbrLigne;//hauteur
  int m_nbrColone;//largeur
  int m_imageSize;//W*H
  int m_nbrCanaux;
  int m_niveauxDeGris;
  std::vector <std::vector <int> > m_bufferImage;
};

#endif // IMAGE_H
