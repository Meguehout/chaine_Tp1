#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QMessageBox>
#include <string.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image.h"
#include "qcustomplot.h"
#include "histogramme.h"
#include "ui_histogramme.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}
///**********Ouvertre D'image*********************//
void MainWindow::on_actionOuvrire_triggered()
{
  QFileDialog fd(this, tr("Ouvrir une image"));

  fd.setFileMode(QFileDialog::ExistingFile);
  fd.setNameFilter(tr("Fichiers images (*.pgm *.ppm)"));

  if (fd.exec())
    {
      _source = fd.selectedFiles().first();

      QPixmap picture(_source);

      ui->label->setPixmap(picture);

      _image.LoadImage(_source.toStdString());

      if(_image.getnbrCanaux() == Couleur) _image.rgb2yuv();

      setWindowTitle(QUrl(_source).fileName());
      this->setFixedSize(picture.width() + ui->pushButton->width(),picture.height()+80);

      //activé les touche d'action
      ui->pushButton->setEnabled(true);
      ui->pushButton_2->setEnabled(true);
      ui->pushButton_3->setEnabled(true);
      if(_image.getnbrCanaux() == NG)ui->pushButton_4->setEnabled(true);
      ui->pushButton_5->setEnabled(true);
      ui->histogramme->setEnabled(true);
      ui->cumule->setEnabled(true);
      ui->actionSauvegarde->setEnabled(true);
    }
}

///**********Rénisialisation*********************//
void MainWindow::on_pushButton_clicked()
{
  QPixmap picture(_source);

  ui->label->setPixmap(picture);

  _image.LoadImage(_source.toStdString());

  if(_image.getnbrCanaux() == Couleur) _image.rgb2yuv();
}

///**********Update View************************//
void MainWindow::UpdateView()
{
  QImage *pImage = new QImage(_image.getNbrColones(), _image.getNbrLignes(),QImage::Format_RGB888);

  int intensite;
  int width = _image.getNbrColones();

  if(_image.getnbrCanaux()== Couleur)_image.yuv2rgb();

  if (_image.getnbrCanaux() == Couleur)_image.normlaize();

  for(int x = 0; x < _image.getNbrLignes(); ++x)
    {
      for(int y = 0; y < _image.getNbrColones(); ++y)
        {
          if(_image.getnbrCanaux()==NG)
            {
              intensite = _image.getIntensity((x*width)+y, 0);
              pImage->setPixel(y,x,qRgb(intensite,intensite,intensite));
            }
          else
            {
              pImage->setPixel(y,x,qRgb(_image.getIntensity((x*width)+y, 0),
                                        _image.getIntensity((x*width)+y, 1),
                                        _image.getIntensity((x*width)+y, 2)));
            }
        }
    }

  ui->label->setPixmap(QPixmap::fromImage(*pImage));

  if(_image.getnbrCanaux()== Couleur) _image.rgb2yuv();
}

///**********Négatife***************************//
void MainWindow::on_pushButton_2_clicked()
{
  _image.fctCorespondance(ImageTraiter::inverstionHisto());

  UpdateView();
}

///**********Contraste***************************//
void MainWindow::on_pushButton_3_clicked()
{
  _image.fctCorespondance( _image.egalisationHisto(),Y);

  UpdateView();
}
///**********Binarisation***************************//
void MainWindow::on_pushButton_4_toggled(bool checked)
{
  ui->horizontalSlider->setEnabled(checked);
  ui->spinBox->setEnabled(checked);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
  Binarisation(value);
}

void MainWindow::Binarisation(int value)
{
  on_pushButton_clicked();

  _image.fctCorespondance(ImageTraiter::seuillageHisto(value));

  UpdateView();
}
///**************Recadrage************************/
void MainWindow::recadrage(int min, int max)
{
  on_pushButton_clicked();
  _image.fctCorespondance(ImageTraiter::recadrageHisto(min, max), Y);
  UpdateView();
}

void MainWindow::on_pushButton_5_toggled(bool checked)
{
  ui->spinBox_2->setEnabled(checked);
  ui->spinBox_3->setEnabled(checked);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
  recadrage(arg1, ui->spinBox_3->value());
}

void MainWindow::on_spinBox_3_valueChanged(int arg2)
{
  recadrage(ui->spinBox_2->value(), arg2);
}
///******************Sauvgarde************************//
void MainWindow::on_actionSauvegarde_triggered()
{
  QString savePath = QFileDialog::getSaveFileName(this,
                                                  "Enregistrer sous",
                                                  "",
                                                  tr("Fichiers images (*.pgm *.ppm)"));
  if (!savePath.isEmpty())
    {
      if(_image.getnbrCanaux()==Couleur) _image.yuv2rgb();
      _image.sauveImage(savePath.toStdString());
      if(_image.getnbrCanaux()==Couleur) _image.rgb2yuv();
    }
}
///*********************Close****************************//
void MainWindow::on_actionFermer_triggered()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::warning(this, "Fermer", "Voulez vous vraiment quitter ?", QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) this->close();
}
///**************Draw***************************//
void MainWindow::on_histogramme_clicked()
{
  Histogramme *_histo = new Histogramme(_image.getnbrCanaux());
  if(_image.getnbrCanaux() == Couleur)_image.yuv2rgb();
  _histo->calculHistOcc(_image,true);
  if(_image.getnbrCanaux() == Couleur)_image.rgb2yuv();
  _histo->setWindowTitle("histogramme d'occurence");
  _histo->show();
}

void MainWindow::on_cumule_clicked()
{
  Histogramme *_histo = new Histogramme(_image.getnbrCanaux());
  if(_image.getnbrCanaux() == Couleur)_image.yuv2rgb();
  _histo->calculHistCumule(_image, true);
  if(_image.getnbrCanaux() == Couleur)_image.rgb2yuv();
  _histo->setWindowTitle("histogramme cumulé");
  _histo->show();
}
