#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "image.h"

class Histogramme
{
public:
    Histogramme();

    void calculHist(Image image);

    void calculHistCumule(Image image, int * tabHistCumule = NULL);



    void sauveHisto (std::string chemainDeSauve) const;

private:
    int m_tabHistOccu [256];
    int m_tabHistCumule [256];
};

#endif // HISTOGRAMME_H
