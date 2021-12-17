#ifndef READINGPROCESSING_H
#define READINGPROCESSING_H

#include <QObject>
#include <QMainWindow>
#include <QDir>
#include "qcustomplot.h"

class Def_of_time//-------------Структура-----------
{
    public:
        int Event;
        double Time_global;
        QList<int> Wire;
        QList<int> Channel;
        QList<int> Time_drift;
        QList<int> Signal_duration;
        int accsident[14][4];                       // Сколько событий в каждой камере
        QList<double> NumXY[14][4];                 // Координаты точек ионизации 4*y
        QList<double> K_B_Sig[14][3];               // K, B и Sig для каждой камеры
};

class Table_time//-------------Структура-для-определения-offset-----------
{
    public:
        int t250[14][4][81];                 // шаг 250 нс, окно 20000 нс
        int t100[14][4][201];                // шаг 100 нс, окно 20000 нс
        int t50[14][4][401];                 // шаг 50 нс, окно 20000 нс

        void writen(QString fileway)
        {
            FILE * fi;
            char nameT[1200] = "";
            char nameT250[1200] = "";
            char nameT100[1200] = "";
            char nameT50[1200] = "";

            QByteArray ba = fileway.toLocal8Bit();
            const char *c_str2 = ba.data();

            strcat(nameT, c_str2);
            strcat(nameT, "/ImageAvto");

            QDir dir(nameT); // создание папки
            if (!dir.exists()) {
                dir.mkpath(".");
            }

            strcat(nameT250, nameT);
            strcat(nameT250, "/table_time_250.txt");
            fi = fopen(nameT250, "w");

            fprintf(fi, "Time\t");
            for (int i_ch = 0; i_ch < 14; i_ch++)
            {
                fprintf(fi, "Ch_%d\tWire_1\tWire_2\tWire_3\tWire_4\t", i_ch);
            }
            fprintf(fi, "\n");

            for (int i_step = 0; i_step < 81; i_step++)
            {
                int a = 250 * i_step;
                fprintf(fi, "%d\t", a);

                for (int i_ch = 0; i_ch < 14; i_ch++)
                {
                    fprintf(fi, "|\t%d\t%d\t%d\t%d\t", t250[i_ch][0][i_step], t250[i_ch][1][i_step], t250[i_ch][2][i_step], t250[i_ch][3][i_step]);
                }

                fprintf(fi, "\n");
            }
            fclose(fi);

            strcat(nameT100, nameT);
            strcat(nameT100, "/table_time_100.txt");
            fi = fopen(nameT100, "w");

            fprintf(fi, "Time\t");
            for (int i_ch = 0; i_ch < 14; i_ch++)
            {
                fprintf(fi, "Ch_%d\tWire_1\tWire_2\tWire_3\tWire_4\t", i_ch);
            }
            fprintf(fi, "\n");

            for (int i_step = 0; i_step < 201; i_step++)
            {
                int a = 100 * i_step;
                fprintf(fi, "%d\t", a);

                for (int i_ch = 0; i_ch < 14; i_ch++)
                {
                    fprintf(fi, "|\t%d\t%d\t%d\t%d\t", t100[i_ch][0][i_step], t100[i_ch][1][i_step], t100[i_ch][2][i_step], t100[i_ch][3][i_step]);
                }

                fprintf(fi, "\n");
            }
            fclose(fi);

            strcat(nameT50, nameT);
            strcat(nameT50, "/table_time_50.txt");
            fi = fopen(nameT50, "w");

            fprintf(fi, "Time\t");
            for (int i_ch = 0; i_ch < 14; i_ch++)
            {
                fprintf(fi, "Ch_%d\tWire_1\tWire_2\tWire_3\tWire_4\t", i_ch);
            }
            fprintf(fi, "\n");

            for (int i_step = 0; i_step < 401; i_step++)
            {
                int a = 50 * i_step;
                fprintf(fi, "%d\t", a);

                for (int i_ch = 0; i_ch < 14; i_ch++)
                {
                    fprintf(fi, "|\t%d\t%d\t%d\t%d\t", t50[i_ch][0][i_step], t50[i_ch][1][i_step], t50[i_ch][2][i_step], t50[i_ch][3][i_step]);
                }

                fprintf(fi, "\n");
            }
            fclose(fi);
        };
};

class ReadingProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ReadingProcessing(QObject *parent = nullptr);

//public:
//    explicit ReadingProcessing(QObject* parent = 0);

public slots:
    void runRP(QStringList files);
    void read_table(QStringList files);
    double tabT50ToY(int ch_num, int wr_num, int i);
    double tabT100ToY(int ch_num, int wr_num, int i);
    double tabT250ToY(int ch_num, int wr_num, int i);
    void Offset_rp(QStringList files);
    bool Offset_bool_fun();
    double Offset_fun(int q1, int q2, int q3, int q4);
    double Offset_add(int q1, int q2, int q3, int q4, double add_offset);   // Изменить офсет
    void Offset_save(QStringList files);                                  // Сохранение новых овсетов

private:
    void test();
    void read_data(QStringList files);
    void write_name_files_to_file(QString files);
    void before_start(QStringList files);
    void loadShow();


signals:
    void backupFinishid();

    void text_to_edit_signal(QString text); // запись в текст эдитор
    void text_to_edit_del_delete(); // Удаление элемента

};

#endif // READINGPROCESSING_H
