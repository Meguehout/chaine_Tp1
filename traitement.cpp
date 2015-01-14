#include "traitement.h"
#include "histogramme.h"
#include <string.h>
#include <stdlib.h>
#include <cmath>
using namespace std;

ImageTraiter::ImageTraiter() : Image()
{}

void ImageTraiter::fctCorespondance(const int *tablDeCorespondance)
{
   //cout << "m_nbrLigne = "<< m_nbrLigne <<" m_nbrColone = "<< m_nbrColone <<endl;
        for (int i = 0; i < m_nbrLigne; i++)
        {
            for (int j = 0; j < m_nbrColone; j++)
            {//cout << "deja en NG1"<<endl;
             m_bufferImage[i][j] = tablDeCorespondance[m_bufferImage[i][j]];
            }
        }
      //  cout << "deja en NG"<<endl;
}


void ImageTraiter::egalisationHisto(int *tabEgalisation) const
{
    Histogramme histo;

    float n = m_nbrLigne * m_nbrColone;

    histo.calculHistCumule(*this , tabEgalisation);

    for(int i = 0; i < 256; i++)
    {
        tabEgalisation[i] = round(255.0 * (tabEgalisation[i]/n));//formul du prof
    }
}

void ImageTraiter::recadrageHisto(int *tabRecadrage, int min, int max)
{
    for(int i = 0; i < 256; i++)
    {
        tabRecadrage[i] = abs(round((255.0 * (i-min)) / (max - min)));
    }
}

void ImageTraiter::inverstionHisto(int *tabNegative) const
{
    int niv=255;

    for(int i = 0; i < 256; i++)
       {
            tabNegative[i]= niv;
            niv--;
       }
   // cout << "deja inverser"<<endl;
}

void ImageTraiter::seuillageHisto(int *tabBinarisation, int seuil) const
{

  for(int i = 0; i < 256; i++)
    {
       if (i < seuil) tabBinarisation[i]= 0;
       else tabBinarisation[i]= 255;
    }
}
//void ImageTraiter::ameliorationParHisto()
//{

//}

//void histogrammeCumule(Histogramme )
//{

//}
