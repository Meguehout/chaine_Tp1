#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include <QDialog>
#include "image.h"
#include "qcustomplot.h"

#define Y 1

namespace Ui {
  class Histogramme;
}

class Histogramme : public QDialog
{
  Q_OBJECT

public:
  explicit Histogramme(int typeImage, QWidget *parent = 0);

  void calculHistOcc(Image image, bool draw = false);
  void calculHistCumule(Image image, bool draw = false);
  void sauveHisto (std::string chemainDeSauve) const;
  int *getHistCumule (){return m_tabHistCumule;}

  void DrawHisto(QCustomPlot *customPlot, int *data, int nbrGraphe, QString name);

  ~Histogramme();

private:
  Ui::Histogramme *ui;

  int *m_tabHistOccu;// [256];
  int *m_tabHistCumule; //[256];
};

#endif // HISTOGRAMME_H
