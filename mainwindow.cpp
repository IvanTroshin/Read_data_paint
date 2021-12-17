#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include "qstring.h"
#include <iostream>
#include "monitoringgraphs.h"


int step_SMB = -1; // Для определения шага в графиках

namespace ui
{
class MainWindow;
}

void Graf_start(QCustomPlot *customPlot)
{

    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, " ", QFont("sans", 12, QFont::Bold)));
    // move bars above graphs and grid below bars:
    customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
    customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
//    graph1->setLayer("abovemain");
    customPlot->xAxis->grid()->setLayer("belowmain");
    customPlot->yAxis->grid()->setLayer("belowmain");

//     set some pens, brushes and backgrounds:

    customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setTickLabelColor(Qt::white);

    customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridVisible(true);
    customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

//    customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    customPlot->yAxis->grid()->setSubGridVisible(true);
//    customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
//    customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    customPlot->axisRect()->setBackground(axisRectGradient);

    customPlot->rescaleAxes();
    customPlot->yAxis->setRange(0, 2);

    customPlot->replot();
    customPlot->update();
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->pushButton_open->setStyleSheet("* { background-color: rgb(97,78,78,100) }");
//    ui->Small_step->setStyleSheet("* { background-color: rgb(97,78,78,100) }");
//    ui->Middle_step->setStyleSheet("* { background-color: rgb(97,78,78,100) }");
//    ui->Big_step->setStyleSheet("* { background-color: rgb(97,78,78,100) }");
//    ui->comboBox->setStyleSheet("* { background-color: rgb(97,78,78,150) }");
//    ui->comboBox_2->setStyleSheet("* { background-color: rgb(97,78,78,150) }");

    ui->pushButton_offsets->setEnabled(false); // Зажим кнопки
    ui->Save->setEnabled(false); // Зажим кнопки

    ui->first_offset->setEnabled(false); // Зажим значения с числами
    ui->second_offset->setEnabled(false); // Зажим значения с числами

    ui->radioButton_first_line->setEnabled(false); // Зажим кнопки
    ui->radioButton_second_line->setEnabled(false); // Зажим кнопки
    ui->pushButton_left->setEnabled(false); // Зажим кнопки
    ui->pushButton_right->setEnabled(false); // Зажим кнопки
    ui->pushButton_sevf_offset->setEnabled(false); // Зажим кнопки

    Graf_start(ui->plot_time);
    for (int i=1; i<15; ++i) // В comboBox записать камеры
    {
        ui->comboBox->addItem(QString::number(i)+ " chamber");
    }


    threadRP = new QThread(this);
    connect(this, SIGNAL(destroyed()), threadRP, SLOT(quit()));

//    threadMG = new QThread(this);
//    connect(this, SIGNAL(destroyed()), threadMG, SLOT(quit()));

    RP = new ReadingProcessing();
    connect(this, &MainWindow::signalrunRP, RP, &ReadingProcessing::runRP);
    connect(this, &MainWindow::signalrunOffset, RP, &ReadingProcessing::read_table);

//    MG = new MonitoringGraphs();
//    connect(this, &MainWindow::signalrunMG, MG, &MonitoringGraphs::runMG);
//    connect(MG, &MonitoringGraphs::needT50ToGraph, RP, &ReadingProcessing::tabT50ToY);

    RP->moveToThread(threadRP);
    threadRP->start();

//    MG->moveToThread(threadMG);
//    threadMG->start();

    connect(RP, &ReadingProcessing::backupFinishid, this, &MainWindow::readyToStart); // Отжим кнопки
    connect(RP, &ReadingProcessing::text_to_edit_signal, this, &MainWindow::text_to_edit); // запись в textediter
    connect(RP, &ReadingProcessing::text_to_edit_del_delete, this, &MainWindow::text_to_edit_delete);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList files;
void MainWindow::on_pushButton_open_clicked()
{
    files = QFileDialog::getOpenFileNames(this, "Open", "C://", "*.txt");       // Выбрать несколько файлов

    ui->pushButton_open->setEnabled(false); // Зажим кнопки  

//    ui->textEdit->setTextColor(QColor(0, 0, 0, 200));
    ui->textEdit->insertPlainText("--------------------\n");
    ui->textEdit->insertPlainText("Start read");
    ui->textEdit->insertPlainText("\r");
    ui->textEdit->insertPlainText("--------------------\n");

    ui->textEdit->insertPlainText("Number of files:");

    ui->textEdit->insertPlainText(QString::number(files.size()));
    ui->textEdit->insertPlainText("   read:");

    Sleep(500);
    signalrunRP(files);   // Испускание сигнала для потока

    ui->pushButton_offsets->setEnabled(true); // Зажим кнопки
    ui->Save->setEnabled(true); // Зажим кнопки

};


void MainWindow::on_pushButton_open_tables_clicked() // Мониторинг
{
    files = QFileDialog::getOpenFileNames(this, "Open", "C://", "*.txt");       // Выбрать несколько файлов

    emit signalrunOffset(files);


//    ui->pushButton_2->setEnabled(false); // Зажим кнопки

//    ui->Small_step->setEnabled(false); // Зажим кнопки
//    ui->Middle_step->setEnabled(false); // Зажим кнопки
//    ui->Big_step->setEnabled(false); // Зажим кнопки

//    emit signalrunMG(ui->plot_time, ui->comboBox, ui->comboBox_2);


    ui->pushButton_offsets->setEnabled(true); // Зажим кнопки
    ui->Save->setEnabled(true); // Зажим кнопки
}


void MainWindow::on_pushButton_offsets_clicked() // оффсет
{

    RP->Offset_rp(files);

}

bool moni_b = true;
void MainWindow::readyToStart()
{
    ui->pushButton_open->setEnabled(true);

    ui->Small_step->setEnabled(true); // Зажим кнопки
    ui->Middle_step->setEnabled(true); // Зажим кнопки
    ui->Big_step->setEnabled(true); // Зажим кнопки

//    ui->pushButton_2->setEnabled(false); // Зажим кнопки
    moni_b = false;
}

void MainWindow::on_Small_step_clicked()
{
    step_SMB = 2;

    int ch_num = ui->comboBox->currentIndex();
    int wr_num = ui->comboBox_2->currentIndex();

    //очистка графика
    ui->plot_time->clearPlottables();
    ui->plot_time->replot();
    ui->plot_time->update();

    QCustomPlot *customPlot = ui->plot_time;
    QVector<double> time_x3(401), time_y3(401);

    char layout[128];

    if (wr_num == 4)
        snprintf(layout, sizeof(layout), "Time. Chamber %d All wire", ch_num+1);
    else
        snprintf(layout, sizeof(layout), "Time. Chamber %d Wire %d", ch_num+1, wr_num+1);


    customPlot->plotLayout()->removeAt(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, layout, QFont("sans", 12, QFont::Bold)));  //Название графика

//    tab.t250[14][4][81];
//    tab.t100[14][4][201];
//    tab.t50[14][4][401];

    for (int i=0; i<time_x3.size(); ++i)
    {
        time_x3[i] = i/(double)(time_x3.size()-1)*20000;
        time_y3[i] = RP->tabT50ToY(ch_num,wr_num,i);
/*
        if (wr_num == 4)
            time_y3[i] = tab.t50[ch_num][0][i]+tab.t50[ch_num][1][i]+tab.t50[ch_num][2][i]+tab.t50[ch_num][3][i];
        else
            time_y3[i] = tab.t50[ch_num][wr_num][i];
*/

    }

    QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    bars1->setWidth(20000/(double)time_x3.size());
    bars1->setData(time_x3, time_y3);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 200));
//    bars1->setBrush(QColor(255, 0, 0));

    // move bars above graphs and grid below bars:
    customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
    customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
    customPlot->xAxis->grid()->setLayer("belowmain");
    customPlot->yAxis->grid()->setLayer("belowmain");

    customPlot->rescaleAxes();
    int maxY = 5;
    for (int i=0; i<time_y3.size(); ++i)
        if (maxY < time_y3[i])
            maxY = time_y3[i];

    customPlot->yAxis->setRange(0, maxY);



    if (RP->Offset_bool_fun())
    {
        QVector<double> x1_red(2), x2_red(2), y_red(2);
        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, 2);;
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, 2);;
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, 2);;
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, 2);;
        y_red[0]=maxY;
        y_red[1]=0;

        ui->first_offset->setValue(int(x1_red[0]+0.5));
        ui->second_offset->setValue(int(x2_red[0]+0.5));

        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(Qt::red)); // line color red for second graph
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }


    customPlot->replot();
    customPlot->update();
}


void MainWindow::on_Middle_step_clicked()
{
    step_SMB = 1;

    int ch_num = ui->comboBox->currentIndex();
    int wr_num = ui->comboBox_2->currentIndex();

    //очистка графика
    ui->plot_time->clearPlottables();
    ui->plot_time->replot();
    ui->plot_time->update();

    QCustomPlot *customPlot = ui->plot_time;
    QVector<double> time_x3(201), time_y3(201);

    char layout[128];

    if (wr_num == 4)
        snprintf(layout, sizeof(layout), "Time. Chamber %d All wire", ch_num+1);
    else
        snprintf(layout, sizeof(layout), "Time. Chamber %d Wire %d", ch_num+1, wr_num+1);


    customPlot->plotLayout()->removeAt(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, layout, QFont("sans", 12, QFont::Bold)));  //Название графика

//    tab.t250[14][4][81];
//    tab.t100[14][4][201];
//    tab.t50[14][4][401];

    for (int i=0; i<time_x3.size(); ++i)
    {
        time_x3[i] = i/(double)(time_x3.size()-1)*20000;
        time_y3[i] = RP->tabT100ToY(ch_num,wr_num,i);
/*
        if (wr_num == 4)
            time_y3[i] = tab.t50[ch_num][0][i]+tab.t50[ch_num][1][i]+tab.t50[ch_num][2][i]+tab.t50[ch_num][3][i];
        else
            time_y3[i] = tab.t50[ch_num][wr_num][i];
*/

    }

    QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    bars1->setWidth(20000/(double)time_x3.size());
    bars1->setData(time_x3, time_y3);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 200));
//    bars1->setBrush(QColor(255, 0, 0));

    // move bars above graphs and grid below bars:
    customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
    customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
    customPlot->xAxis->grid()->setLayer("belowmain");
    customPlot->yAxis->grid()->setLayer("belowmain");

    customPlot->rescaleAxes();
    int maxY = 5;
    for (int i=0; i<time_y3.size(); ++i)
        if (maxY < time_y3[i])
            maxY = time_y3[i];

    customPlot->yAxis->setRange(0, maxY);




    if (RP->Offset_bool_fun())
    {
        QVector<double> x1_red(2), x2_red(2), y_red(2);
        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, 1);;
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, 1);;
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, 1);;
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, 1);;
        y_red[0]=maxY;
        y_red[1]=0;

        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(Qt::red)); // line color red for second graph
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }


    customPlot->replot();
    customPlot->update();
}


void MainWindow::on_Big_step_clicked()
{
    step_SMB = 0;

    int ch_num = ui->comboBox->currentIndex();
    int wr_num = ui->comboBox_2->currentIndex();

    //очистка графика
    ui->plot_time->clearPlottables();
    ui->plot_time->replot();
    ui->plot_time->update();

    QCustomPlot *customPlot = ui->plot_time;
    QVector<double> time_x3(81), time_y3(81);

    char layout[128];

    if (wr_num == 4)
        snprintf(layout, sizeof(layout), "Time. Chamber %d All wire", ch_num+1);
    else
        snprintf(layout, sizeof(layout), "Time. Chamber %d Wire %d", ch_num+1, wr_num+1);


    customPlot->plotLayout()->removeAt(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, layout, QFont("sans", 12, QFont::Bold)));  //Название графика

//    tab.t250[14][4][81];
//    tab.t100[14][4][201];
//    tab.t50[14][4][401];

    for (int i=0; i<time_x3.size(); ++i)
    {
        time_x3[i] = i/(double)(time_x3.size()-1)*20000;
        time_y3[i] = RP->tabT250ToY(ch_num,wr_num,i);
/*
        if (wr_num == 4)
            time_y3[i] = tab.t50[ch_num][0][i]+tab.t50[ch_num][1][i]+tab.t50[ch_num][2][i]+tab.t50[ch_num][3][i];
        else
            time_y3[i] = tab.t50[ch_num][wr_num][i];
*/

    }

    QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    bars1->setWidth(20000/(double)time_x3.size());
    bars1->setData(time_x3, time_y3);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 200));
//    bars1->setBrush(QColor(255, 0, 0));

    // move bars above graphs and grid below bars:
    customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
    customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
    customPlot->xAxis->grid()->setLayer("belowmain");
    customPlot->yAxis->grid()->setLayer("belowmain");

    customPlot->rescaleAxes();
    int maxY = 5;
    for (int i=0; i<time_y3.size(); ++i)
        if (maxY < time_y3[i])
            maxY = time_y3[i];

    customPlot->yAxis->setRange(0, maxY);

    if (RP->Offset_bool_fun())
    {
        QVector<double> x1_red(2), x2_red(2), y_red(2);
        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, 0);;
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, 0);;
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, 0);;
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, 0);;
        y_red[0]=maxY;
        y_red[1]=0;

        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(Qt::red)); // line color red for second graph
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }

    customPlot->replot();
    customPlot->update();
}



MonitoringGraphs::MonitoringGraphs(QObject *parent) : QObject(parent)
{

}


void MonitoringGraphs::runMG(QCustomPlot *customPlot, QComboBox *ComboBox, QComboBox *ComboBox_2)
{
    qDebug() << "MG";

    time_t timer_mon = time(NULL);

//    Sleep(500);
    while (moni_b)
    {
//        Sleep(500);
        if(time(NULL) - timer_mon > 1)
        {
            timer_mon = time(NULL);
            const int ch_num = ComboBox->currentIndex();
            const int wr_num = ComboBox_2->currentIndex();
            qDebug() << ch_num;
            qDebug() << wr_num;

            //очистка графика
            customPlot->clearPlottables();
            customPlot->replot();
            customPlot->update();

            QVector<double> time_x3(201), time_y3(201);

            char layout[128];

            if (wr_num == 4)
                snprintf(layout, sizeof(layout), "Time. Chamber %d All wire", ch_num+1);
            else
                snprintf(layout, sizeof(layout), "Time. Chamber %d Wire %d", ch_num+1, wr_num+1);


            customPlot->plotLayout()->removeAt(0);
            customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, layout, QFont("sans", 12, QFont::Bold)));  //Название графика

            for (int i=0; i<time_x3.size(); ++i)
            {
                time_x3[i] = i/(double)(time_x3.size()-1)*20000;
//                time_y3[i] = emit needT50ToGraph(ch_num,wr_num,i);
                time_y3[i] = RP->tabT100ToY(ch_num,wr_num,i);
            }

            QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
            bars1->setWidth(20000/(double)time_x3.size());
            bars1->setData(time_x3, time_y3);
            bars1->setPen(Qt::NoPen);
            bars1->setBrush(QColor(10, 140, 70, 200));
        //    bars1->setBrush(QColor(255, 0, 0));

            // move bars above graphs and grid below bars:
            customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
            customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
            customPlot->xAxis->grid()->setLayer("belowmain");
            customPlot->yAxis->grid()->setLayer("belowmain");

            customPlot->rescaleAxes();
            int maxY = 5;
            for (int i=0; i<time_y3.size(); ++i)
                if (maxY < time_y3[i])
                    maxY = time_y3[i];

            customPlot->yAxis->setRange(0, maxY);

            customPlot->replot();
            customPlot->update();
        }
    }
}



void MainWindow::on_Save_clicked()
{
    char nameImag[1200] = "";


    QByteArray ba = QFileInfo(files[0]).absolutePath().toLocal8Bit();
    const char *c_str2 = ba.data();

    strcat(nameImag, c_str2);
    strcat(nameImag, "/ImageAvto");

    QDir dir(nameImag); // создание папки
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    strcat(nameImag, "/Image_all");

    QDir dir1(nameImag); // создание папки
    if (!dir1.exists()) {
        dir1.mkpath(".");
    }
    int i_size = ui->comboBox->count();
    for (int i=0; i<i_size; ++i)
        for (int j=0; j<5; ++j)
        {
            char nameImag_all[1200] = "";
            strcat(nameImag_all, nameImag);
            char nameImag_buff[50] = "";
            sprintf(nameImag_buff, "/Ima_ch%d_wire%d.png", i, j);
            strcat(nameImag_all, nameImag_buff);
//            strcat(nameImag_all, "/Test.png");

            save_print(ui->plot_time, i, j);

            ui->plot_time->savePng(nameImag_all, 1280, 720);
        }

}


void MainWindow::save_print(QCustomPlot *customPlot, int ch_num, int wr_num)
{
    //очистка графика
    customPlot->clearPlottables();
    customPlot->replot();
    customPlot->update();

    QVector<double> time_x3(401), time_y3(401);

    char layout[128];

    if (wr_num == 4)
        snprintf(layout, sizeof(layout), "Time. Chamber %d All wire", ch_num+1);
    else
        snprintf(layout, sizeof(layout), "Time. Chamber %d Wire %d", ch_num+1, wr_num+1);


    customPlot->plotLayout()->removeAt(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, layout, QFont("sans", 12, QFont::Bold)));  //Название графика

    for (int i=0; i<time_x3.size(); ++i)
    {
        time_x3[i] = i/(double)(time_x3.size()-1)*20000;
        time_y3[i] = RP->tabT50ToY(ch_num,wr_num,i);
    }

    QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    bars1->setWidth(20000/(double)time_x3.size());
    bars1->setData(time_x3, time_y3);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 200));
//    bars1->setBrush(QColor(255, 0, 0));

    // move bars above graphs and grid below bars:
    customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
    customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
    customPlot->xAxis->grid()->setLayer("belowmain");
    customPlot->yAxis->grid()->setLayer("belowmain");

    customPlot->rescaleAxes();
    int maxY = 5;
    for (int i=0; i<time_y3.size(); ++i)
        if (maxY < time_y3[i])
            maxY = time_y3[i];

    customPlot->yAxis->setRange(0, maxY);

    if (RP->Offset_bool_fun())
    {
        QVector<double> x1_red(2), x2_red(2), y_red(2);
        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, 2);;
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, 2);;
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, 2);;
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, 2);;
        y_red[0]=maxY;
        y_red[1]=0;

        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(Qt::red)); // line color red for second graph
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }


    customPlot->replot();
    customPlot->update();
}

void MainWindow::text_to_edit(QString text)
{
    ui->textEdit->insertPlainText(text);
}

void MainWindow::text_to_edit_delete()
{
    ui->textEdit->textCursor().deletePreviousChar();
}

void MainWindow::on_checkBox_offset_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->first_offset->setEnabled(true);                 // Зажим значения с числами
        ui->second_offset->setEnabled(true);                // Зажим значения с числами

        ui->radioButton_first_line->setEnabled(true);        // Зажим кнопки
        ui->radioButton_second_line->setEnabled(true);       // Зажим кнопки
        ui->pushButton_left->setEnabled(true);              // Зажим кнопки
        ui->pushButton_right->setEnabled(true);             // Зажим кнопки
        ui->pushButton_sevf_offset->setEnabled(true);       // Зажим кнопки

        ui->checkBox_offset->setEnabled(false);
    }
    else
    {
        ui->first_offset->setEnabled(false);                // Зажим значения с числами
        ui->second_offset->setEnabled(false);               // Зажим значения с числами

        ui->radioButton_first_line->setEnabled(false);       // Зажим кнопки
        ui->radioButton_second_line->setEnabled(false);      // Зажим кнопки
        ui->pushButton_left->setEnabled(false);             // Зажим кнопки
        ui->pushButton_right->setEnabled(false);            // Зажим кнопки
        ui->pushButton_sevf_offset->setEnabled(false);      // Зажим кнопки
    }
}

int MainWindow::print_graphs(QCustomPlot *customPlot, int ch_num, int wr_num, int step_i) // нарисовать график без овсетов
{
    //очистка графика
    customPlot->clearPlottables();
    customPlot->replot();
    customPlot->update();

    int size_xy = 0;

    if (step_i == 2)
    {
        size_xy = 401;
    }
    else if (step_i == 1)
    {
        size_xy = 201;
    }
    else if (step_i == 0)
    {
        size_xy = 81;
    }

    QVector<double> time_x3(size_xy), time_y3(size_xy);

    char layout[128];

    if (wr_num == 4)
        snprintf(layout, sizeof(layout), "Time. Chamber %d All wire", ch_num+1);
    else
        snprintf(layout, sizeof(layout), "Time. Chamber %d Wire %d", ch_num+1, wr_num+1);

    customPlot->plotLayout()->removeAt(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, layout, QFont("sans", 12, QFont::Bold)));  //Название графика

    if (step_i == 2)
    {
        for (int i=0; i<time_x3.size(); ++i)
        {
            time_x3[i] = i/(double)(time_x3.size()-1)*20000;
            time_y3[i] = RP->tabT50ToY(ch_num,wr_num,i);
        }
    }
    else if  (step_i == 1)
    {
        for (int i=0; i<time_x3.size(); ++i)
        {
            time_x3[i] = i/(double)(time_x3.size()-1)*20000;
            time_y3[i] = RP->tabT100ToY(ch_num,wr_num,i);
        }
    }
    else if  (step_i == 0)
    {
        for (int i=0; i<time_x3.size(); ++i)
        {
            time_x3[i] = i/(double)(time_x3.size()-1)*20000;
            time_y3[i] = RP->tabT250ToY(ch_num,wr_num,i);
        }
    }

    QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    bars1->setWidth(20000/(double)time_x3.size());
    bars1->setData(time_x3, time_y3);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 200));
//    bars1->setBrush(QColor(255, 0, 0));

    // move bars above graphs and grid below bars:
    customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
    customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
    customPlot->xAxis->grid()->setLayer("belowmain");
    customPlot->yAxis->grid()->setLayer("belowmain");

    customPlot->rescaleAxes();
    int maxY = 5;
    for (int i=0; i<time_y3.size(); ++i)
        if (maxY < time_y3[i])
            maxY = time_y3[i];

    customPlot->yAxis->setRange(0, maxY);

    customPlot->replot();
    customPlot->update();

    return maxY;
}

void MainWindow::on_radioButton_first_line_clicked()
{
    int ch_num = ui->comboBox->currentIndex();
    int wr_num = ui->comboBox_2->currentIndex();

    QCustomPlot *customPlot = ui->plot_time;

    int maxY = print_graphs(customPlot, ch_num, wr_num, step_SMB);

    if (RP->Offset_bool_fun())
    {
        QVector<double> x1_red(2), x2_red(2), y_red(2);
        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        y_red[0]=maxY;
        y_red[1]=0;

        ui->first_offset->setValue(int(x1_red[0]+0.5));
        ui->second_offset->setValue(int(x2_red[0]+0.5));

        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(Qt::red, 3)); // line color red for second graph
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }

    customPlot->replot();
    customPlot->update();
}


void MainWindow::on_radioButton_second_line_clicked()
{
    int ch_num = ui->comboBox->currentIndex();
    int wr_num = ui->comboBox_2->currentIndex();

    QCustomPlot *customPlot = ui->plot_time;

    int maxY = print_graphs(customPlot, ch_num, wr_num, step_SMB);

    if (RP->Offset_bool_fun())
    {
//        double Offset[14][5][2][3];                 // Камера, проволока+all, передний задний офсет, три таблицы B M S
        QVector<double> x1_red(2), x2_red(2), y_red(2);
        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        y_red[0]=maxY;
        y_red[1]=0;

        ui->first_offset->setValue(int(x1_red[0]+0.5));
        ui->second_offset->setValue(int(x2_red[0]+0.5));

        customPlot->addGraph();
        customPlot->graph(0)->setPen(QPen(Qt::red)); // line color red for second graph
        customPlot->addGraph();
        customPlot->graph(1)->setPen(QPen(Qt::red, 3)); // line color red for second graph

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }

    customPlot->replot();
    customPlot->update();
}


void MainWindow::on_pushButton_left_clicked()
{
    int check_LR = 0; // 1-первый офсет 2-второй офсет

    if (ui->radioButton_first_line->isChecked())
        check_LR = 1;
    else if (ui->radioButton_second_line->isChecked())
        check_LR = 2;
    else
        return;


    int ch_num = ui->comboBox->currentIndex();
    int wr_num = ui->comboBox_2->currentIndex();

    QCustomPlot *customPlot = ui->plot_time;

    int maxY = print_graphs(customPlot, ch_num, wr_num, step_SMB);

    if (RP->Offset_bool_fun())
    {
        QVector<double> x1_red(2), x2_red(2), y_red(2);

        double step_buff = 0;

        if (step_SMB == 2)
            step_buff = -50;
        else if (step_SMB == 1)
            step_buff = -100;
        else if (step_SMB == 0)
            step_buff = -250;

        if (ui->radioButton_first_line->isChecked())
        {
           RP->Offset_add(ch_num, wr_num, 0, step_SMB, step_buff);
        }
        else if (ui->radioButton_second_line->isChecked())
        {
            RP->Offset_add(ch_num, wr_num, 1, step_SMB, step_buff);
        }

        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        y_red[0]=maxY;
        y_red[1]=0;

        ui->first_offset->setValue(int(x1_red[0]+0.5));
        ui->second_offset->setValue(int(x2_red[0]+0.5));

        if (check_LR == 1)
        {
            customPlot->addGraph();
            customPlot->graph(0)->setPen(QPen(Qt::red, 3));     // line color red for second graph
            customPlot->addGraph();
            customPlot->graph(1)->setPen(QPen(Qt::red));        // line color red for second graph
        }
        if (check_LR == 2)
        {
            customPlot->addGraph();
            customPlot->graph(0)->setPen(QPen(Qt::red));        // line color red for second graph
            customPlot->addGraph();
            customPlot->graph(1)->setPen(QPen(Qt::red, 3));     // line color red for second graph
        }

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }

    customPlot->replot();
    customPlot->update();

}


void MainWindow::on_pushButton_right_clicked()
{
    int check_LR = 0; // 1-первый офсет 2-второй офсет

    if (ui->radioButton_first_line->isChecked())
        check_LR = 1;
    else if (ui->radioButton_second_line->isChecked())
        check_LR = 2;
    else
        return;


    int ch_num = ui->comboBox->currentIndex();
    int wr_num = ui->comboBox_2->currentIndex();

    QCustomPlot *customPlot = ui->plot_time;

    int maxY = print_graphs(customPlot, ch_num, wr_num, step_SMB);

    if (RP->Offset_bool_fun())
    {
        QVector<double> x1_red(2), x2_red(2), y_red(2);

        double step_buff = 0;

        if (step_SMB == 2)
            step_buff = 50;
        else if (step_SMB == 1)
            step_buff = 100;
        else if (step_SMB == 0)
            step_buff = 250;

        if (ui->radioButton_first_line->isChecked())
        {
           RP->Offset_add(ch_num, wr_num, 0, step_SMB, step_buff);
        }
        else if (ui->radioButton_second_line->isChecked())
        {
            RP->Offset_add(ch_num, wr_num, 1, step_SMB, step_buff);
        }

        x1_red[0]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x1_red[1]=RP->Offset_fun(ch_num, wr_num, 0, step_SMB);
        x2_red[0]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        x2_red[1]=RP->Offset_fun(ch_num, wr_num, 1, step_SMB);
        y_red[0]=maxY;
        y_red[1]=0;

        ui->first_offset->setValue(int(x1_red[0]+0.5));
        ui->second_offset->setValue(int(x2_red[0]+0.5));

        if (check_LR == 1)
        {
            customPlot->addGraph();
            customPlot->graph(0)->setPen(QPen(Qt::red, 3));     // line color red for second graph
            customPlot->addGraph();
            customPlot->graph(1)->setPen(QPen(Qt::red));        // line color red for second graph
        }
        if (check_LR == 2)
        {
            customPlot->addGraph();
            customPlot->graph(0)->setPen(QPen(Qt::red));        // line color red for second graph
            customPlot->addGraph();
            customPlot->graph(1)->setPen(QPen(Qt::red, 3));     // line color red for second graph
        }

        customPlot->graph(0)->setData(x1_red, y_red);
        customPlot->graph(1)->setData(x2_red, y_red);
    }

    customPlot->replot();
    customPlot->update();

}


void MainWindow::on_pushButton_sevf_offset_clicked()
{

    ui->checkBox_offset->setEnabled(true);      // Отжим галочки
    ui->checkBox_offset->setChecked(false);     // Убрать галочку

    RP->Offset_save(files);

}



