#ifndef MONITORINGGRAPHS_H
#define MONITORINGGRAPHS_H

#include <QObject>
#include "qcustomplot.h"
#include "readingprocessing.h"

class MonitoringGraphs : public QObject
{
    Q_OBJECT
public:
    explicit MonitoringGraphs(QObject *parent = nullptr);

public slots:
    void runMG(QCustomPlot *customPlot, QComboBox *ComboBox, QComboBox *ComboBox_2);
//    void tabT50ToGraph(QCustomPlot *customPlot);
//    void tabT100ToGraph(QCustomPlot *customPlot);
//    void tabT250ToGraph(QCustomPlot *customPlot);

signals:
        double needT50ToGraph(int ch_num, int wr_num, int i);
//        double needT100ToGraph(int ch_num, int wr_num, int i);
//        double needT250ToGraph(int ch_num, int wr_num, int i);

private:
    ReadingProcessing *RP;

};

#endif // MONITORINGGRAPHS_H
