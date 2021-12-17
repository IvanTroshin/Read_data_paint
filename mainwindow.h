#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "qcustomplot.h"
#include "readingprocessing.h"
#include "monitoringgraphs.h"
#include <QObject>
#include <QThread>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_open_clicked();

    void readyToStart();

    void text_to_edit(QString text);    // запись в текст эдитор
    void text_to_edit_delete();         // Удаление элемента

    int print_graphs(QCustomPlot *customPlot, int ch_num, int wr_num, int step_i);  // нарисовать график без овсетов
    void save_print(QCustomPlot *customPlot, int ch_num, int wr_num);               // сохранение графиков всех


signals:
    void signalrunRP(QStringList files);
    void signalrunOffset(QStringList files);
    void signalrunMG(QCustomPlot *customPlot, QComboBox *ComboBox, QComboBox *ComboBox_2);

signals:
    void signalFromButton();    // Сигнал для передачи номер нажатой кнопки


private slots:
    void on_Small_step_clicked();

    void on_Middle_step_clicked();

    void on_Big_step_clicked();

    void on_Save_clicked();

    void on_pushButton_open_tables_clicked();

    void on_pushButton_offsets_clicked();

    void on_checkBox_offset_stateChanged(int arg1);

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_sevf_offset_clicked();

    void on_radioButton_first_line_clicked();

    void on_radioButton_second_line_clicked();

private:
    Ui::MainWindow *ui;
    ReadingProcessing *RP;
    MonitoringGraphs *MG;
    QThread *threadRP;
    QThread *threadMG;

};

#endif // MAINWINDOW_H
