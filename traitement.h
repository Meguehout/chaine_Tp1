#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include "image.h"

class ImageTraiter : public Image
{
public:

  ImageTraiter();

  void fctCorespondance(int *tablDeCorespondance, int canaux = 0);

  static int *inverstionHisto();
  int *egalisationHisto () const;
  static int *recadrageHisto(int min=0, int max=255);
  static int *seuillageHisto (int seuil = 128);

  void rgb2yuv();
  void yuv2rgb();
};

#endif // TRAITEMENT_H

