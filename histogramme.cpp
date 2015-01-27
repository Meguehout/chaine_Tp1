#include "histogramme.h"
#include "ui_histogramme.h"
#include "qcustomplot.h"
#include <stdlib.h>
#include <fstream>


Histogramme::Histogramme(int typeImage, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Histogramme)
{
  ui->setupUi(this);

  m_tabHistOccu = new int[256*typeImage];
  m_tabHistCumule = new int[256*typeImage];

  for(int i = 0; i < 256*typeImage; i++)
    {
      m_tabHistOccu[i] = 0;
      m_tabHistCumule[i] = 0;
    }
}

///*********Histogramme D'occurence**************************//
void Histogramme::calculHistOcc(Image image, bool draw)
{
  for (int j = 0; j < image.getnbrCanaux(); ++j)
    for (int i = 0; i < image.getTailleImage(); ++i)
      m_tabHistOccu[image.getIntensity(i,j)+(256 * j)]++ ;

  if(draw) DrawHisto(ui->customPlot, m_tabHistOccu,image.getnbrCanaux(),"Histogramme d'occurence");
}

///*********Histogramme Cumule*****************************//
void Histogramme::calculHistCumule(Image image, bool draw)
{
  calculHistOcc(image);

  for(int j = 0; j < image.getnbrCanaux(); ++j)
    {
      m_tabHistCumule[j+(256*j)] = m_tabHistOccu[j+(256*j)];
      for(int i = 1; i < 256; ++i)
        {
          m_tabHistCumule[i+(256*j)] = m_tabHistOccu[i+(256*j)] + m_tabHistCumule[(i+(256*j))-1];
        }
    }
  if(draw)DrawHisto(ui->customPlot, m_tabHistCumule,image.getnbrCanaux(),"Histogramme cumulé");
}
///**********************************************************//
void Histogramme::sauveHisto(std::string chemainDeSauve ) const
{
  std::ofstream newHisto(chemainDeSauve.c_str());

  if (newHisto)
    {
      for(int intensity = 0; intensity < 256; intensity++)
        newHisto << intensity << " "<< m_tabHistCumule[intensity] << std::endl;
    }
  else std::cout << "ERREUR: Impossible d'ouvrir le fichier3" << std::endl;

  newHisto.close();
}
///**********************Draw Histogramme********************//
void Histogramme::DrawHisto(QCustomPlot *customPlot, int *data, int nbrGraphe, QString name)
{
  QVector<double> x(256), y(256);
  for (int i=0; i<256; ++i) x[i] = i;

  for (int gi = 0; gi < nbrGraphe; gi++)
    {
      for (int i=0; i<256; ++i)
        {
          y[i] = data[i + (256*gi)];
        }
      customPlot->addGraph();

      if(nbrGraphe == 1)
        {
          customPlot->graph(gi)->setPen(QPen(Qt::black));
          customPlot->graph(gi)->setBrush(QBrush(QColor(128, 128, 128, 150)));
          customPlot->graph(gi)->setName("niveaux de gris");
        }
      else
        {
          switch (gi) {
            case 0:
              customPlot->graph(gi)->setPen(QPen(Qt::red));
              customPlot->graph(gi)->setBrush(QBrush(QColor(255, 0, 0, 150)));
              customPlot->graph(gi)->setName("rouge");
              break;
            case 1:
              customPlot->graph(gi)->setPen(QPen(Qt::green));
              customPlot->graph(gi)->setBrush(QBrush(QColor(0, 255, 0, 150)));
              customPlot->graph(gi)->setName("vert");
              break;
            case 2:
              customPlot->graph(gi)->setPen(QPen(Qt::blue));
              customPlot->graph(gi)->setBrush(QBrush(QColor(0, 0, 255, 150)));
              customPlot->graph(gi)->setName("bleu");
              break;
            };
        }

      customPlot->graph(gi)->setData(x, y);
    }

  customPlot->legend->setVisible(true);

  customPlot->plotLayout()->insertRow(0);
  customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, name));

  customPlot->xAxis->setLabel("intensité");

  customPlot->graph(0)->rescaleAxes();
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

  customPlot->replot();
}

Histogramme::~Histogramme()
{
  delete ui;
}
