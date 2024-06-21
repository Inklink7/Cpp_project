#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <QtCharts>
#include <QList>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Slot per gestire il click sul pulsante InserisciIMG.
 * Apre un file dialog per selezionare un'immagine, la visualizza e aggiorna lo stato dei pulsanti.
 * Inoltre, salva le occorrenze di ciascun colore RGB in una struttura QMap.
 */
void MainWindow::on_InserisciIMG_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Apri file"), QDir::homePath(), tr("*.png *.jpg *.jpeg"));
    if (!file_name.isEmpty())
    {
        QPixmap pm(file_name);
        ui->label->setPixmap(pm);
        ui->label->setScaledContents(true);
        ui->InserisciIMG->setEnabled(false);
        ui->RimuoviIMG->setEnabled(true);
        ui->IstorgrmRGB->setEnabled(true);

        // Carica l'immagine e memorizza le triplette RGB in rgbMap
        QImage img(file_name);
        int rows = img.height();
        int column = img.width();
        img_pixels = rows * column;

        QRgba64 pixelv;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < column; j++)
                if (rgbMap.contains(pixelv = img.pixelColor(j, i).rgba64()))
                    rgbMap.insert(pixelv, rgbMap.value(pixelv) + 1);
                else
                    rgbMap.insert(pixelv, 1);
    }
}

/**
 * Slot per gestire il click sul pulsante RimuoviIMG.
 * Rimuove l'immagine visualizzata e ripristina lo stato iniziale dell'interfaccia.
 */
void MainWindow::on_RimuoviIMG_clicked()
{
    if (!ui->label->pixmap()->isNull())
    {
        ui->label->clear();
        img_pixels = 0;

        ui->RimuoviIMG->setEnabled(false);
        ui->IstorgrmRGB->setEnabled(false);
        ui->InserisciIMG->setEnabled(true);
        rgbMap.clear();
    }
}

/**
 * Slot per gestire il click sul pulsante IstorgrmRGB.
 * Genera un istogramma RGB in base alla selezione corrente del combo box.
 * Modifica la struttura dati se necessario in modo da mantenere le intensità per un solo canale.
 */
void MainWindow::on_IstorgrmRGB_clicked()
{
    QMap<QRgba64, int> RGB_singlech;
    QMap<QRgba64, int>::iterator its, ite;
    switch (ui->comboBox->currentIndex())
    {
        case 0:
            // Genera istogramma RGB completo
            GeneraGrafico(rgbMap);
            break;
        case 1: // Istogramma canale rosso
            for (its = rgbMap.begin(), ite = rgbMap.end(); its != ite; its++)
                RGB_singlech.insert(QColor(its.key().red8(), 0, 0).rgba64(), its.value());
            if (ui->checkBox->isChecked())
                for (int k = 0; k < 256; k++)
                    if (!RGB_singlech.contains(QColor(k, 0, 0).rgba64()))
                        RGB_singlech.insert(QColor(k, 0, 0).rgba64(), 0);
            GeneraGrafico(RGB_singlech);
            break;
        case 2: // Istogramma canale verde
            for (its = rgbMap.begin(), ite = rgbMap.end(); its != ite; its++)
                RGB_singlech.insert(QColor(0, its.key().green8(), 0).rgba64(), its.value());
            if (ui->checkBox->isChecked())
                for (int k = 0; k < 256; k++)
                    if (!RGB_singlech.contains(QColor(0, k, 0).rgba64()))
                        RGB_singlech.insert(QColor(0, k, 0).rgba64(), 0);
            GeneraGrafico(RGB_singlech);
            break;
        case 3: // Istogramma canale blu
            for (its = rgbMap.begin(), ite = rgbMap.end(); its != ite; its++)
                RGB_singlech.insert(QColor(0, 0, its.key().blue8()).rgba64(), its.value());
            if (ui->checkBox->isChecked())
                for (int k = 0; k < 256; k++)
                    if (!RGB_singlech.contains(QColor(0, 0, k).rgba64()))
                        RGB_singlech.insert(QColor(0, 0, k).rgba64(), 0);
            GeneraGrafico(RGB_singlech);
            break;
    }
}

/**
 * Genera un grafico a barre per rappresentare la distribuzione dei colori.
 * Riceve una _rgbMap Mappa dei colori e delle loro occorrenze.
 */
void MainWindow::GeneraGrafico(QMap<QRgba64, int> _rgbMap)
{
    QMap<QRgba64, int>::ConstIterator its = _rgbMap.begin(), ite = _rgbMap.end();
    QList<QBarSeries*> barseries_list;
    QList<QBarSet*> barset_list;
    auto *chart = new QChart();
    QStringList categories;

    for (; its != ite; its++)
    {
        QRgba64 rgbcol = its.key();
        QBarSet *tmp = new QBarSet("");
        QBarSeries *tmp_series = new QBarSeries();

        categories << QColor(rgbcol).name();
        *tmp << ((float)(its.value()) / img_pixels) * 100;

        tmp->setColor(QColor(rgbcol));
        tmp_series->append(tmp);

        barset_list.append(tmp);
        barseries_list.append(tmp_series);

        chart->addSeries(tmp_series);
    }

    QtCharts::QBarCategoryAxis *X_axis = new QtCharts::QBarCategoryAxis();
    X_axis->append(categories);
    X_axis->setLabelsAngle(-90);

    chart->createDefaultAxes();
    chart->removeAxis(chart->axisX());

    chart->addAxis(X_axis, Qt::AlignBottom);
    chart->legend()->setVisible(false);
    chart->setTitle("Percentuale occorrenze per colore");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setMinimumSize(QSize(750, 400));
    chartView->show();
}

/**
 * Slot per gestire il cambio dell'indice del combo box.
 * Abilita o disabilita la checkbox in base alla selezione corrente.
 */
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->checkBox->setEnabled(index != 0);
}
