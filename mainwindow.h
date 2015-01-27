#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "image.h"
#include "traitement.h"
#include "histogramme.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionOuvrire_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_4_toggled(bool checked);

    void on_pushButton_5_toggled(bool checked);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg2);

    void on_actionSauvegarde_triggered();

    void on_actionFermer_triggered();

    void on_histogramme_clicked();

    void on_cumule_clicked();

private:
    Ui::MainWindow *ui;
    ImageTraiter _image;
    QString _source;

    void UpdateView();
    void Binarisation(int value);
    void recadrage(int min=0, int max=255);

};

#endif // MAINWINDOW_H
