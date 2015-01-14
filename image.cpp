#include "image.h"
#include<stdlib.h>
#include <fstream>
#include <QString>

using namespace std;

void Image::LoadImage(string fileSource)
{
  string ligne ;
  ifstream imagePGM;
  imagePGM.open(fileSource.c_str());

  if(imagePGM)
    {
      imagePGM >> m_typeFile; // recupération du type de fichier
      getline(imagePGM, ligne);

      //igniore les ligne de commentaires
      do{
          getline(imagePGM, ligne);

        }while ( ligne[0] == '#' );

      std::sscanf(ligne.c_str(), "%d%d", &m_nbrColone, &m_nbrLigne);

      imagePGM >> m_niveauxDeGris;//initialisation du nbr des niveau de gris utilise de fichier

      for(int i = 0; i < m_nbrLigne; i++)//initialisation de vecteur
        {
          m_bufferImage.push_back( vector<int> (m_nbrColone) );
          for(int j = 0; j < m_nbrColone; j++)
            imagePGM >> m_bufferImage[i][j];
        }


    }
  else cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;

  imagePGM.close();

  //   for(int j=0; j<m_nbrLigne; j++){//teste de constructeur
  //         for(int i=0; i<m_nbrColone; i++){
  //             cout << m_bufferImage[j][i] <<" ";
  //         }
  //         cout << endl;
  //     }

}//Fin du constructeur

void Image::sauveImage (string chemainDeSauve) const
{
  ofstream newImage(chemainDeSauve.c_str());

  if(newImage)  //On teste si tout est OK
    {
      newImage << m_typeFile << endl;
      newImage << m_nbrLigne << "  "<< m_nbrColone << endl;
      newImage << m_niveauxDeGris << endl;//si tu enleve ça ça fait un effet de sursaturation

      for(int i = 0; i < m_nbrLigne; i++){
          for(int j = 0; j <m_nbrColone; j++){
              newImage << m_bufferImage[i][j] <<" ";
            }
          newImage << endl;
        }
    }
  else cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;

  newImage.close();
}//fin du sauvgardage

int Image::getIntensity (int ligneI, int coloneJ)const
{
  if( !m_bufferImage.empty())
    {
      return m_bufferImage[ligneI][coloneJ];//(y,x)
    }
  else
    {
      cout << "ta pas encore charger une image !"<<endl;
      return -1;
    }
}//fin de récuperation du niveau de gris

void Image::putIntensity (int ligneI, int coloneJ, int valIntensity)
{
  if (valIntensity <= 255)
    {
      if(valIntensity > m_niveauxDeGris) m_niveauxDeGris = valIntensity;

      m_bufferImage[ligneI][coloneJ] = valIntensity;

    }else cout << "ton intensity est supperieur a 255 désole" <<endl;
}

//int Image::getNbrLignes() const
//{
//    return m_nbrLigne;
//}

//int Image::getNbrColones() const
//{
//    return m_nbrColone;
//}
