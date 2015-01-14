#include "histogramme.h"
#include<stdlib.h>
#include <fstream>
#include "image.h"


using namespace std;

Histogramme::Histogramme()
{
    for(int i = 0; i < 256; i++)
    {
        m_tabHistOccu[i] = 0;
    }
}

void Histogramme::calculHist(Image image)
{
    for (int i = 0; i < image.getNbrLignes(); i++)
    {
        for (int j = 0; j < image.getNbrColones(); j++)
        {
                 m_tabHistOccu[image.getIntensity(i,j)] ++ ;
        }
    }

    /*for(int p=0; p < 256; p++)
    {
        cout << "i = " << p<< "val = "<< m_tabHisto[p] << endl;
    }*/

}

void Histogramme::calculHistCumule(Image image, int *tabHistCumule)
{
    if (tabHistCumule)
    {
        //cout << "t dans l'espace du pointeur" << endl;
        calculHist(image);
        tabHistCumule[0] = m_tabHistOccu[0];
        for(int i = 1; i < 256; i++)
        {
           tabHistCumule[i] = m_tabHistOccu[i] + tabHistCumule[i-1];
        }
    }
    else
    {

        m_tabHistCumule[0] = m_tabHistOccu[0];

        for(int i = 1; i < 256; i++)
        {
            m_tabHistCumule[i] = m_tabHistOccu[i] + m_tabHistCumule[i-1];
        }
    }
}


void Histogramme::sauveHisto(string chemainDeSauve ) const
{
    ofstream newHisto(chemainDeSauve.c_str());

    if (newHisto)
    {
        for(int intensity = 0; intensity < 256; intensity++)
        {
            newHisto << intensity << " "<< m_tabHistCumule[intensity] << endl;
        }


    }else cout << "ERREUR: Impossible d'ouvrir le fichier3" << endl;

   newHisto.close();
}

