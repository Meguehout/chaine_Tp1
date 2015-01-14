#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include "image.h"

class ImageTraiter : public Image
{
public:

    ImageTraiter();

    void fctCorespondance(const int *tablDeCorespondance);

    void egalisationHisto (int *tabEgalisation) const;

    void recadrageHisto (int *tabRecadrage, int min=0, int max=150);

    void inverstionHisto (int *tabNegative) const;

    void seuillageHisto (int *tabBinarisation, int seuil = 128) const;

//    void ameliorationParHisto();



};

#endif // TRAITEMENT_H

