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
#include "traitement.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  // ui->label->setPixmap(QPicture());
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionOuvrire_triggered()
{
  QFileDialog fd(this, tr("Ouvrir une image"));

  fd.setFileMode(QFileDialog::ExistingFile);
  fd.setNameFilter(tr("Fichiers images (*.pgm)"));

  if (fd.exec())
    {
      _source = fd.selectedFiles().first();

      QPixmap picture(_source);

      ui->label->setPixmap(picture);

      _image.LoadImage(_source.toStdString());

      string str = _source.toStdString();
    //  cout << "source" << str << endl;

      setWindowTitle(QUrl(_source).fileName());
      this->setFixedSize(picture.width() + ui->pushButton->width(),picture.height()+80);
      //activé les touche d'action
      ui->pushButton->setEnabled(true);
      ui->pushButton_2->setEnabled(true);
      ui->pushButton_3->setEnabled(true);
      ui->pushButton_4->setEnabled(true);
      ui->pushButton_5->setEnabled(true);
      ui->actionSauvegarde->setEnabled(true);
    }
}

void MainWindow::on_pushButton_clicked()
{
  QPixmap picture(_source);

  ui->label->setPixmap(picture);

  _image.LoadImage(_source.toStdString());
}

void MainWindow::on_pushButton_2_clicked()
{
  //négatife
  int *effet =new int[256];

  _image.inverstionHisto(effet);//negative

  _image.fctCorespondance(effet);

  UpdateView();
}

void MainWindow::UpdateView()
{
  QImage *pImage = new QImage(_image.getNbrColones(), _image.getNbrLignes(),QImage::Format_RGB888);

  //on_actionSauvegarde_triggered();
  int intensite;

for (int x = 0; x < _image.getNbrLignes(); x++)
    {
        for (int y = 0; y < _image.getNbrColones(); y++)
        {
           intensite =  _image.getIntensity(x,y);
           if (intensite > 255) intensite = 255;//ToDo Normlise
           pImage->setPixel(y,x, qRgb(intensite,intensite,intensite));
//          pImage->setPixel(y,x, qRgb(_image.getIntensity(x,y),_image.getIntensity(x,y),_image.getIntensity(x,y)));
        }
    }

  ui->label->setPixmap(QPixmap::fromImage(*pImage));
}

void MainWindow::on_pushButton_3_clicked()
{
  //contraste
  int *effet =new int[256];

  _image.egalisationHisto(effet);

  _image.fctCorespondance(effet);

  UpdateView();
}

void MainWindow::on_pushButton_4_toggled(bool checked)
{
  ui->horizontalSlider->setEnabled(checked);
  ui->spinBox->setEnabled(checked);
}

void MainWindow::Binarisation(int value)
{
  on_pushButton_clicked();

  int *effet =new int[256];

  _image.seuillageHisto(effet, value);

  _image.fctCorespondance(effet);

  UpdateView();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
  Binarisation(value);
}

void MainWindow::recadrage(int min, int max)
{
  on_pushButton_clicked();

  int *effet =new int[256];

  _image.recadrageHisto(effet, min, max);

  _image.fctCorespondance(effet);
  //_image.sauveImage("/home/meguehout/Qt_Project/TpPGM/teste222.pgm");
  UpdateView();//probleme avec update
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

void MainWindow::on_actionSauvegarde_triggered()
{
  QString savePath = QFileDialog::getSaveFileName(this,
                                                  "Enregistrer sous",
                                                  "",
                                                  tr("Fichiers images (*.pgm)"));
  if (!savePath.isEmpty())
    _image.sauveImage(savePath.toStdString());
}

void MainWindow::on_actionFermer_triggered()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::warning(this, "Fermer", "Voulez vous vraiment quitter ?", QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes)
    this->close();

}

//    MyDialog mDialoge;
//   // mDialoge.setModal(false);
//   // mDialoge.exec();
//    mDialoge.show();
