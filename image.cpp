#include "image.h"
#include "traitement.h"
#include<stdlib.h>
#include <fstream>
#include <QString>

void Image::LoadImage(std::string fileSource)
{
  std::string ligne ;
  std::ifstream imagePGM;
  imagePGM.open(fileSource.c_str());

  if(imagePGM)
    {
      imagePGM >> m_typeFile;
      if(m_typeFile == "P2") m_nbrCanaux = NG;
      else m_nbrCanaux = Couleur;

      std::getline(imagePGM, ligne);

      //igniore les ligne de commentaires
      do{
          getline(imagePGM, ligne);

        }while ( ligne[0] == '#' );

      std::sscanf(ligne.c_str(), "%d%d", &m_nbrColone, &m_nbrLigne);
      m_imageSize = m_nbrColone * m_nbrLigne;

      imagePGM >> m_niveauxDeGris;//initialisation du nbr des niveau de gris utilise de fichier

      for(int i = 0; i < m_imageSize; i++)//initialisation de vecteur
        {
          m_bufferImage.push_back( std::vector<int> (m_nbrCanaux) );
          for(int j = 0; j < m_nbrCanaux; ++j)
            imagePGM >> m_bufferImage[i][j];
        }
    }
  else std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;

  imagePGM.close();
}//Fin du constructeur

void Image::sauveImage (std::string chemainDeSauve)
{
  std::ofstream newImage(chemainDeSauve.c_str());

  if(newImage)  //On teste si tout est OK
    {
      newImage << m_typeFile << std::endl;
      newImage <<m_nbrColone<< "  "<<m_nbrLigne<< std::endl;
      newImage << m_niveauxDeGris << std::endl;

      for(int i = 0; i < m_imageSize; ++i)
        {
          for(int j = 0; j <m_nbrCanaux; ++j)
            {
              newImage << m_bufferImage[i][j] <<" ";
            }
          if((i % m_nbrColone) == 0) newImage << std::endl;
        }
    }
  else std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;

  newImage.close();
}//fin du sauvgardage

int Image::getIntensity (int pixel, int canal)const
{
  if( !m_bufferImage.empty())
    return m_bufferImage[pixel][canal];
  else
    {
      std::cout << "ta pas encore charger une image !"<<std::endl;
      return -1;
    }
}//fin de récuperation du niveau de gris

void Image::setIntensity (int pixel, int canal, int valIntensity)
{
  if (valIntensity <= 255)
    {
      if(valIntensity > m_niveauxDeGris) m_niveauxDeGris = valIntensity;

      m_bufferImage[pixel][canal] = valIntensity;

    }else std::cout << "ton intensity est supperieur a 255 désole" <<std::endl;
}

void Image::normlaize()
{
  int max=0, newIntensity;

  for(int i = 0; i < this->getTailleImage(); ++i)
    for(int j = 0; j < this->getnbrCanaux(); ++j)
      if(this->getIntensity(i,j) > max) max = this->getIntensity(i,j);


  for(int i = 0; i < this->getTailleImage(); i++)
    for(int j = 0; j < this->getnbrCanaux(); j++)
      {
        newIntensity = (this->getIntensity(i,j)*255)/max;

        this->setIntensity(i,j, newIntensity);
      }
  this->setIntensityMax(255);
}

Image::~Image()
{

}
