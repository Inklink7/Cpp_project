#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_InserisciIMG_clicked();

    void on_RimuoviIMG_clicked();

    void on_IstorgrmRGB_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:

    Ui::MainWindow *ui;

    QMap<QRgba64, int> rgbMap;
    unsigned int img_pixels;
    void GeneraGrafico(QMap<QRgba64, int>);


};
#endif // MAINWINDOW_H
