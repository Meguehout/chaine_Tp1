#include "traitement.h"
#include "histogramme.h"
#include <string.h>
#include <stdlib.h>
#include <cmath>

ImageTraiter::ImageTraiter() : Image()
{}

void ImageTraiter::fctCorespondance(int *tablDeCorespondance , int canaux)
{
  if(canaux == 0)canaux = m_nbrCanaux;

  for (int i = 0; i < m_imageSize; ++i)
    {
      for (int j = 0; j < canaux; ++j)
          m_bufferImage[i][j] = tablDeCorespondance[m_bufferImage[i][j]];
    }

  delete (tablDeCorespondance);
}

///***************************************************************/
int *ImageTraiter::egalisationHisto() const
{
  Histogramme histo(m_nbrCanaux);

  float n = m_imageSize;

  int *tabEgalisation =  new int[256];

  histo.calculHistCumule(*this);

  tabEgalisation = histo.getHistCumule();

  for(int i = 0; i < 256; ++i)
      tabEgalisation[i] = round(255.0 * (tabEgalisation[i]/n));

  return tabEgalisation;
}

///*********************************************************/
int *ImageTraiter::recadrageHisto(int min, int max)
{
  int *tabRecadrage = new int[255];
  for(int i = 0; i < 256; ++i)
    {
     if((min <= i)&&(i <= max))
       tabRecadrage[i] = round((255.0 * (i-min)) / (max - min));
     else if (i < min)
       tabRecadrage[i] = 0;
     else
       tabRecadrage[i] = 255;
    }
  return tabRecadrage;
}
///**********************************************************/
int *ImageTraiter::inverstionHisto()
{
  int niv=255;
  int *tabNegative = new int[256];

  for(int i = 0; i < 256; i++)
    {
      tabNegative[i]= niv;
      niv--;
    }
  return tabNegative;
}

int *ImageTraiter::seuillageHisto(int seuil)
{
  int *tabBinarisation = new int[256];
  for(int i = 0; i < 256; i++)
    {
      if (i < seuil) tabBinarisation[i]= 0;
      else tabBinarisation[i]= 255;
    }
  return tabBinarisation;
}
///**********RGB -> YUV ****************//
void ImageTraiter::rgb2yuv()
{
  int R,G,B;

  for(int i = 0; i < this->m_imageSize; i++)
    {
      R = this->m_bufferImage[i][0];
      G = this->m_bufferImage[i][1];
      B = this->m_bufferImage[i][2];

      this->m_bufferImage[i][0] = 0.299*R + 0.587*G + 0.114*B;
      this->m_bufferImage[i][1] = abs(-(0.169*R) - (0.331*G) + (0.500*B) + 128.0);
      this->m_bufferImage[i][2] = abs((0.500*R) - (0.419*G) - (0.081*B) + 128.0);
    }

}
///***************YUV -> RGB*************//
void ImageTraiter::yuv2rgb()
{
  int y,u,v;

  for(int i = 0; i < this->m_imageSize; i++)
    {
      y = this->m_bufferImage[i][0];
      u = this->m_bufferImage[i][1];
      v = this->m_bufferImage[i][2];

      this->m_bufferImage[i][0] = abs(1 * y -  0.0009267*(u-128) + 1.4016868*(v-128));
      this->m_bufferImage[i][1] = abs(1 * y -  0.3436954*(u-128) - 0.7141690*(v-128));
      this->m_bufferImage[i][2] = abs(1 * y +  1.7721604*(u-128) + 0.0009902*(v-128));
    }
}
