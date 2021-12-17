#include "readingprocessing.h"
#include <QWidget>
#include <QObject>
#include <dos.h>
#include <time.h>

Table_time tab; // Для записи времени в таблицу

double Offset[14][5][2][3];                 // Камера, проволока+all, передний задний офсет, три таблицы B M S
bool Offset_bool = false;                   // Для отрисовки оффсетов

QStringList file_already_read;


ReadingProcessing::ReadingProcessing(QObject *parent) : QObject(parent)
{

};


bool ReadingProcessing::Offset_bool_fun()
{
    return Offset_bool;
}

double ReadingProcessing::Offset_fun(int q1, int q2, int q3, int q4)
{
    return Offset[q1][q2][q3][q4];
}


void ReadingProcessing::runRP(QStringList files)
{
//    test(TextEdit); // Проверка

    before_start(files); // Запись последних файлов

    read_data(files); // Чтение файлов

    emit backupFinishid(); // отжим кнопки
}

void ReadingProcessing::test()
{
    for (int i = 0; i < 10; ++i)    // Проверка
    {
        emit text_to_edit_signal(QString::number(i));
        emit text_to_edit_signal("\n");
//        TextEdit ->insertPlainText(QString::number(i));
//        TextEdit ->insertPlainText("\n");
    }
}

int witen_i = 0;
void table_time(int chamber, int wire, int time_drift, QString fileway)
{
    int t = time_drift;
    tab.t250[chamber][wire][t/250]++;
    tab.t100[chamber][wire][t/100]++;
    tab.t50[chamber][wire][t/50]++;

    witen_i++;
    if (witen_i == 1000)
    {
        tab.writen(fileway);
        witen_i = 0;
    }

}

int loadShow_n = 0;
void ReadingProcessing::loadShow()
{
    emit text_to_edit_del_delete();
//    TextEdit ->textCursor().deletePreviousChar();
    if (loadShow_n == 0)
    {
        emit text_to_edit_signal("┛");
//        TextEdit ->insertPlainText("┛");
        loadShow_n++;
    }
    else if (loadShow_n == 1)
    {
        emit text_to_edit_signal("┗");
//        TextEdit ->insertPlainText("┗");
        loadShow_n++;
    }
    else if (loadShow_n == 2)
    {
        emit text_to_edit_signal("┏");
//        TextEdit ->insertPlainText("┏");
        loadShow_n++;
    }
    else if (loadShow_n == 3)
    {
        emit text_to_edit_signal("┓");
//        TextEdit ->insertPlainText("┓");
        loadShow_n = 0;
    }
}

void ReadingProcessing::read_data(QStringList files)
{

    time_t timer1 = time(NULL);

    Sleep(500);

    emit text_to_edit_signal("X");
    emit text_to_edit_signal("X");
//    TextEdit ->insertPlainText("X");
//    TextEdit ->insertPlainText("X");

    for (int i_F = 0; i_F < files.size(); i_F++)
    {

        QString fileway = QFileInfo(files[i_F]).absolutePath();

        QString base_buff = QFileInfo(files[i_F]).baseName();

        if (file_already_read.contains(base_buff))
        {
            continue;
        }

        emit text_to_edit_del_delete();
        emit text_to_edit_del_delete();
//        TextEdit ->textCursor().deletePreviousChar();
//        TextEdit ->textCursor().deletePreviousChar();

        if (i_F+1 > 10)
            emit text_to_edit_del_delete();
//            TextEdit ->textCursor().deletePreviousChar();
        if (i_F+1 > 100)
            emit text_to_edit_del_delete();
//            TextEdit ->textCursor().deletePreviousChar();


        emit text_to_edit_signal(QString::number(i_F+1));
        emit text_to_edit_signal("X");
//        TextEdit ->insertPlainText(QString::number(i_F+1));
//        TextEdit ->insertPlainText("X");

        write_name_files_to_file(files[i_F]);

        QFile file(files[i_F]);
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {

            while(!file.atEnd())
            {

                if(time(NULL) - timer1 > 0.5)
                {
                    loadShow(); // Загрузка
                    timer1 = time(NULL);
                }

                // Чтение строки
                QString read_str = QString::fromUtf8(file.readLine());

                QString numb_str="";                        // Чтение числа
                Def_of_time data;                           // Структура для всех точек ионизации

                int i_way = -2;
                int chamber, wire, time_to_front, time_signal; // Камера, проволока, время до заднего фронта, длительность сигнала


//                //------Проверка--------
//                FILE * fi;
//                char nameT[1200] = "";

//                QByteArray ba = fileway.toLocal8Bit();
//                const char *c_str2 = ba.data();

//                strcat(nameT, c_str2);
//                strcat(nameT, "/time_test.txt");

                for (int i_r = 0; i_r < read_str.size(); i_r++)
                {

                    if (read_str[i_r] != '\t' && read_str[i_r] != '\n' && read_str[i_r] != '\r')
                    {
                        numb_str = numb_str + read_str[i_r];
                    }
                    else if (read_str[i_r] == '\r')
                    {
                        break;
                    }
                    else
                    {

                        if (i_way == -2)
                        {
                            data.Event = numb_str.toInt();
//                            fi = fopen(nameT, "at");                    //------Проверка--------
//                            fprintf(fi, "\nw%d\t", numb_str.toInt());   //------Проверка--------
//                            fclose(fi);                                 //------Проверка--------
                        }

                        if (i_way == -1)
                        {
                            data.Time_global = numb_str.toDouble();
//                            fi = fopen(nameT, "at");                    //------Проверка--------
//                            fprintf(fi, "q%f\t", numb_str.toDouble());  //------Проверка--------
//                            fclose(fi);                                 //------Проверка--------
                        }
                        if (i_way == 0)
                        {
//                            fi = fopen(nameT, "at");                    //------Проверка--------
//                            fprintf(fi, "a%d\t", numb_str.toInt());     //------Проверка--------
//                            fclose(fi);                                 //------Проверка--------
                            data.Channel.push_back(numb_str.toInt()/4);                         // Проволока
                            data.Wire.push_back(numb_str.toInt()-numb_str.toInt()/4*4);         // Канал
                            chamber = numb_str.toInt()/4;
                            wire = numb_str.toInt()-numb_str.toInt()/4*4;

                        }

                        if (i_way == 1)
                        {
//                            fi = fopen(nameT, "at");                    //------Проверка--------
//                            fprintf(fi, "b%d\t", numb_str.toInt());     //------Проверка--------
//                            fclose(fi);                                 //------Проверка--------
                            data.Time_drift.push_back(5*numb_str.toInt());                      // Время до заднего фронта
                            time_to_front = 5*numb_str.toInt();
                        }
                        if (i_way == 2)
                        {
//                            fi = fopen(nameT, "at");                    //------Проверка--------
//                            fprintf(fi, "c%d\t", numb_str.toInt());     //------Проверка--------
//                            fclose(fi);                                 //------Проверка--------
                            data.Signal_duration.push_back(5*numb_str.toInt());                 // Длительность сигнала
                            time_signal = 5*numb_str.toInt();

                            if (time_signal > 10)
                            {
                                int time_table = time_to_front + time_signal;
                                table_time(chamber, wire, time_table, fileway);
                            }

                        }

                        if (i_way == 3)
                        {
//                            fi = fopen(nameT, "at");                    //------Проверка--------
//                            fprintf(fi, "d%d\t", numb_str.toInt());     //------Проверка--------
//                            fclose(fi);                                 //------Проверка--------
                            i_way = -1;
                        }

                        i_way++;
                        numb_str="";


                    }

                }

            }

            file.close();
            tab.writen(fileway);
        }
    }

    emit text_to_edit_signal("\n");
    emit text_to_edit_signal("Finished");
    emit text_to_edit_signal("\n");

//    TextEdit ->insertPlainText("\n");
//    TextEdit ->insertPlainText("Finished");
//    TextEdit ->insertPlainText("\n");
};

double ReadingProcessing::tabT50ToY(int ch_num, int wr_num, int i)
{
    if (wr_num == 4)
        return tab.t50[ch_num][0][i]+tab.t50[ch_num][1][i]+tab.t50[ch_num][2][i]+tab.t50[ch_num][3][i];
    else
        return tab.t50[ch_num][wr_num][i];
}

double ReadingProcessing::tabT100ToY(int ch_num, int wr_num, int i)
{
    if (wr_num == 4)
        return tab.t100[ch_num][0][i]+tab.t100[ch_num][1][i]+tab.t100[ch_num][2][i]+tab.t100[ch_num][3][i];
    else
        return tab.t100[ch_num][wr_num][i];
}

double ReadingProcessing::tabT250ToY(int ch_num, int wr_num, int i)
{
    if (wr_num == 4)
        return tab.t250[ch_num][0][i]+tab.t250[ch_num][1][i]+tab.t250[ch_num][2][i]+tab.t250[ch_num][3][i];
    else
        return tab.t250[ch_num][wr_num][i];

}

void ReadingProcessing::Offset_rp(QStringList files)
{
    for (int q1 = 0; q1 < 14; q1++)
        for (int q2 = 0; q2 < 5; q2++)
            for (int q3 = 0; q3 < 2; q3++)
                for (int q4 = 0; q4 < 3; q4++)
                    Offset[q1][q2][q3][q4] = 0;

    Offset_bool = true;
    QVector<double> time_small(401), time_middle(201), time_big(81);

    for (int ch_num = 0; ch_num < 14; ch_num++)
        for (int wr_num = 0; wr_num < 5; wr_num++)
        {
            for (int i=0; i<time_big.size(); ++i)
            {
//                time_x3[i] = i/(double)(time_x3.size()-1)*20000;
                time_big[i] = tabT250ToY(ch_num,wr_num,i);
            }

            int maxY = 5;
            for (int i=0; i<time_big.size(); ++i)
                if (maxY < time_big[i])
                    maxY = time_big[i];

            int buff_tabl[20]={0};

            for (int i=0; i<time_big.size(); ++i)
            {
                int i_index = time_big[i]/maxY*20;
                buff_tabl[i_index]++;
            }

            int max_buff = 0;
            int max_buff_ind = 0;
            for (int i=0; i<15; ++i) // до 15
                if (max_buff < buff_tabl[i])
                {
                    max_buff = buff_tabl[i];
                    max_buff_ind = i;
                }

            max_buff = max_buff_ind*maxY/20;

            for (int i=0; i<time_big.size(); ++i)
                if ((maxY-max_buff)/3 < (time_big[i]-max_buff) && max_buff < time_big[i])
                {
                    Offset[ch_num][wr_num][0][0] = i/(double)(time_big.size()-1)*20000;
                    break;
                }

            for (int i=time_big.size()-1; i>0; i--)
                if ((maxY-max_buff)/3 < (time_big[i]-max_buff) && max_buff < time_big[i])
                {
                    Offset[ch_num][wr_num][1][0] = i/(double)(time_big.size()-1)*20000;
                    break;
                }

//---------------------------------------------------------------------------------------------


            for (int i=0; i<time_middle.size(); ++i)
            {
//                time_x3[i] = i/(double)(time_x3.size()-1)*20000;
                time_middle[i] = tabT100ToY(ch_num,wr_num,i);
            }

             maxY = 5;
            for (int i=0; i<time_middle.size(); ++i)
                if (maxY < time_middle[i])
                    maxY = time_middle[i];

//            buff_tabl[20]={0};
            for (int i=0; i<20; ++i)
                buff_tabl[i]=0;

            for (int i=0; i<time_middle.size(); ++i)
            {
                int i_index = time_middle[i]/maxY*20;
                buff_tabl[i_index]++;
            }

            max_buff = 0;
            max_buff_ind = 0;
            for (int i=0; i<15; ++i) // до 15
                if (max_buff < buff_tabl[i])
                {
                    max_buff = buff_tabl[i];
                    max_buff_ind = i;
                }

            max_buff = max_buff_ind*maxY/20;


            for (int i=0; i<time_middle.size(); ++i)
                if ((maxY-max_buff)/3 < (time_middle[i]-max_buff) && max_buff < time_middle[i])
                {
                    Offset[ch_num][wr_num][0][1] = i/(double)(time_middle.size()-1)*20000;
                    break;
                }

            for (int i=time_middle.size()-1; i>0; i--)
                if ((maxY-max_buff)/3 < (time_middle[i]-max_buff) && max_buff < time_middle[i])
                {
                    Offset[ch_num][wr_num][1][1] = i/(double)(time_middle.size()-1)*20000;
                    break;
                }

//---------------------------------------------------------------------------------------------

            for (int i=0; i<time_small.size(); ++i)
            {
//                time_x3[i] = i/(double)(time_x3.size()-1)*20000;
                time_small[i] = tabT50ToY(ch_num,wr_num,i);
            }

            maxY = 5;                                   // писать тут
            for (int i=0; i<time_small.size(); ++i)
                if (maxY < time_small[i])
                    maxY = time_small[i];

//            buff_tabl[20]={0};
            for (int i=0; i<20; ++i)
                buff_tabl[i]=0;

            for (int i=0; i<time_small.size(); ++i)
            {
                int i_index = time_small[i]/maxY*20;
                buff_tabl[i_index]++;
            }

            max_buff = 0;
            max_buff_ind = 0;
            for (int i=0; i<15; ++i) // до 15
                if (max_buff < buff_tabl[i])
                {
                    max_buff = buff_tabl[i];
                    max_buff_ind = i;
                }

            max_buff = max_buff_ind*maxY/20;

            for (int i=0; i<time_small.size(); ++i)
                if ((maxY-max_buff)/3 < (time_small[i]-max_buff) && max_buff < time_small[i])
                {
                    Offset[ch_num][wr_num][0][2] = i/(double)(time_small.size()-1)*20000;
                    break;
                }

            for (int i=time_small.size()-1; i>0; i--)
                if ((maxY-max_buff)/3 < (time_small[i]-max_buff) && max_buff < time_small[i])
                {
                    Offset[ch_num][wr_num][1][2] = i/(double)(time_small.size()-1)*20000;
                    break;
                }

        }

    char nameOffset[1200] = "";
    char nameOffset_all[1200] = "";
    QByteArray ba = QFileInfo(files[0]).absolutePath().toLocal8Bit();
    const char *c_str2 = ba.data();

    strcat(nameOffset, c_str2);
    strcat(nameOffset, "/ImageAvto");

    QDir dir(nameOffset); // создание папки
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    strcat(nameOffset_all, nameOffset);
    FILE * fi;
    strcat(nameOffset_all, "/Offset_all.txt");
    fi = fopen(nameOffset_all, "w");

    fprintf(fi, "Offset");

    fprintf(fi, "\tBig_step\t\tMiddle_step\t\tSmall_step\t\tResult\t\n");

    for (int ch_num = 0; ch_num < 14; ch_num++)
        for (int wr_num = 0; wr_num < 5; wr_num++)
        {
            if(wr_num == 4)
                fprintf(fi, "Ch_%dWire_All\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\n",
                        ch_num,
                        Offset[ch_num][wr_num][0][0], Offset[ch_num][wr_num][1][0],
                        Offset[ch_num][wr_num][0][1], Offset[ch_num][wr_num][1][1],
                        Offset[ch_num][wr_num][0][2], Offset[ch_num][wr_num][1][2],
                        (Offset[ch_num][wr_num][0][0]+Offset[ch_num][wr_num][0][1]+Offset[ch_num][wr_num][0][2])/3,
                        (Offset[ch_num][wr_num][1][0]+Offset[ch_num][wr_num][1][1]+Offset[ch_num][wr_num][1][2])/3);
            else
                fprintf(fi, "Ch_%dWire_%d\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\n",
                        ch_num, wr_num,
                        Offset[ch_num][wr_num][0][0], Offset[ch_num][wr_num][1][0],
                        Offset[ch_num][wr_num][0][1], Offset[ch_num][wr_num][1][1],
                        Offset[ch_num][wr_num][0][2], Offset[ch_num][wr_num][1][2],
                        (Offset[ch_num][wr_num][0][0]+Offset[ch_num][wr_num][0][1]+Offset[ch_num][wr_num][0][2])/3,
                        (Offset[ch_num][wr_num][1][0]+Offset[ch_num][wr_num][1][1]+Offset[ch_num][wr_num][1][2])/3);
        }
    fclose(fi);


    FILE * fi_off;
    strcat(nameOffset, "/Offset.txt");
    fi_off = fopen(nameOffset, "w");

    fprintf(fi_off, "Offset");

    fprintf(fi_off, "\tThe_first(ns)\tThe_second(ns)\tVelocity(mm/ns)\n");

    for (int ch_num = 0; ch_num < 14; ch_num++)
    {
        fprintf(fi_off, "Ch_%d\t"
                    "%d\t%d\t%f\n",
                ch_num,
                int((Offset[ch_num][4][0][0]+Offset[ch_num][4][0][1]+Offset[ch_num][4][0][2])/3+0.5),
                int((Offset[ch_num][4][1][0]+Offset[ch_num][4][1][1]+Offset[ch_num][4][1][2])/3+0.5),
                250.0/((Offset[ch_num][4][1][0]+Offset[ch_num][4][1][1]+Offset[ch_num][4][1][2])/3-
                    (Offset[ch_num][4][0][0]+Offset[ch_num][4][0][1]+Offset[ch_num][4][0][2])/3));
    }
    fclose(fi_off);
}


void ReadingProcessing::read_table(QStringList files)
{

//    time_t timer1 = time(NULL);

//    tab.t250[14][4][81];                 // шаг 250 нс, окно 20000 нс
//    tab.t100[14][4][201];                // шаг 100 нс, окно 20000 нс
//    tab.t50[14][4][401];                 // шаг 50 нс, окно 20000 нс

    Offset_bool = true;


    emit text_to_edit_signal("Read tables");
//    TextEdit ->insertPlainText("Read tables");


    for (int i_F = 0; i_F < files.size(); i_F++)
    {

        QString base = QFileInfo(files[i_F]).baseName();

        if (base == "table_time_250" || base == "table_time_100" || base == "table_time_50")
        {
            QFile file(files[i_F]);
            if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
            {

                while(!file.atEnd())
                {

    //                if(time(NULL) - timer1 > 0.5)
    //                {
    //                    loadShow(TextEdit); // Загрузка
    //                    timer1 = time(NULL);
    //                }

                    // Чтение строки
                    QString read_str = QString::fromUtf8(file.readLine());

                    QString numb_str="";                        // Чтение числа


                    int i_way = -1;
                    int time_tab = 0;
                    for (int i_r = 0; i_r < read_str.size(); i_r++)
                    {

                        if (read_str[i_r] != '\t' && read_str[i_r] != '\n' && read_str[i_r] != '\r')
                        {
                            numb_str = numb_str + read_str[i_r];
                        }
                        else if (read_str[i_r] == '\r')
                        {
                            break;
                        }
                        else if (numb_str == "Time")
                        {
                            break;
                        }
                        else
                        {
                            if (i_way == -1)
                                time_tab = numb_str.toInt();
                            if (i_way>=0)
                            {
                                int ch = i_way/5;
                                int wr = i_way-ch*5-1;
                                if (wr >= 0 && wr < 4)
                                {
                                    if (base == "table_time_250")
                                    {
                                        tab.t250[ch][wr][time_tab/250] = numb_str.toInt();
                                    }
                                    else if (base == "table_time_100")
                                    {
                                        tab.t100[ch][wr][time_tab/100] = numb_str.toInt();
                                    }
                                    else if (base == "table_time_50")
                                    {
                                        tab.t50[ch][wr][time_tab/50] = numb_str.toInt();
                                    }
                                }
                            }

                            i_way++;
                            numb_str="";
                        }

                    }

                }

                file.close();
            }

        }

        if (base == "Offset_all")
        {
            QFile file(files[i_F]);
            if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
            {

                int i_way_column = -1;

                while(!file.atEnd())
                {

                    // Чтение строки
                    QString read_str = QString::fromUtf8(file.readLine());

                    QString numb_str="";                        // Чтение числа

                    int i_way = -1;

                    for (int i_r = 0; i_r < read_str.size(); i_r++)
                    {

                        if (read_str[i_r] != '\t' && read_str[i_r] != '\n' && read_str[i_r] != '\r')
                        {
                            numb_str = numb_str + read_str[i_r];
                        }
                        else if (read_str[i_r] == '\r')
                        {
                            break;
                        }
                        else if (numb_str == "Offset")
                        {
                            break;
                        }

                        else
                        {
                            if (i_way >= 0 && i_way < 6)
                            {
                                int ch = i_way_column/5;
                                int wr = i_way_column-ch*5;
                                int BMS = i_way/2;
                                int fs = i_way - BMS*2;

                                Offset[ch][wr][fs][BMS] = numb_str.toDouble(); // Камера, проволока+all, передний задний офсет, три таблицы B M S

                            }

                            i_way++;
                            numb_str="";
                        }


                    }

                    i_way_column++;

                }

                file.close();
            }

        }

    }


//    TextEdit ->insertPlainText("\n");
//    TextEdit ->insertPlainText("Finished");
//    TextEdit ->insertPlainText("\n");

};



void ReadingProcessing::write_name_files_to_file(QString files)
{
    FILE * fi;
    char nameF[1200] = "";

    QString fileway = QFileInfo(files).absolutePath();

    QByteArray ba = fileway.toLocal8Bit();
    const char *c_str2 = ba.data();

    strcat(nameF, c_str2);
    strcat(nameF, "/ImageAvto");

    QDir dir(nameF); // создание папки
    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    strcat(nameF, "/fils_read.txt");

    if ((fi = fopen(nameF, "at"))==NULL)
        fi = fopen(nameF, "w");

    QString base = QFileInfo(files).baseName();

    QByteArray ba3 = base.toLocal8Bit();
    const char *c_str3 = ba3.data();
    fprintf(fi, "%s\n", c_str3);

    fclose(fi);

}

void ReadingProcessing::before_start(QStringList files)
{

    FILE * fi;
    char nameF_way[1200] = "";
    char nameF[1200] = "";

    QString fileway = QFileInfo(files[0]).absolutePath();

    QByteArray ba = fileway.toLocal8Bit();
    const char *c_str2 = ba.data();

    strcat(nameF_way, c_str2);
    strcat(nameF_way, "/ImageAvto");

    QDir dir(nameF_way); // создание папки
    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    strcat(nameF, nameF_way);
    strcat(nameF, "/fils_read.txt");

    if ((fi = fopen(nameF, "rt"))==NULL)
        return;

    char item[50];

    while (true)
    {
        int ret = fscanf(fi, "%s", item);

        file_already_read << item;

        if(ret == EOF)
        {
            break;
        }

    }

    fclose(fi);

    QStringList tabl_time = { "/table_time_250.txt", "/table_time_100.txt", "/table_time_50.txt" };

    for (int i=0; i<3; ++i)
    {
        char nameF_tab[1200] = "";

        strcat(nameF_tab, nameF_way);

        QByteArray buff = tabl_time[i].toLocal8Bit();
        const char *c_str3 = buff.data();

        strcat(nameF_tab, c_str3);

        QFile file(nameF_tab);
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {

            while(!file.atEnd())
            {

                // Чтение строки
                QString read_str = QString::fromUtf8(file.readLine());

                QString numb_str="";                        // Чтение числа

                int i_way = -1;
                int time_tab = 0;
                for (int i_r = 0; i_r < read_str.size(); i_r++)
                {

                    if (read_str[i_r] != '\t' && read_str[i_r] != '\n' && read_str[i_r] != '\r')
                    {
                        numb_str = numb_str + read_str[i_r];
                    }
                    else if (read_str[i_r] == '\r')
                    {
                        break;
                    }
                    else if (numb_str == "Time")
                    {
                        break;
                    }
                    else
                    {
                        if (i_way == -1)
                            time_tab = numb_str.toInt();
                        if (i_way>=0)
                        {
                            int ch = i_way/5;
                            int wr = i_way-ch*5-1;
                            if (wr >= 0 && wr < 4)
                            {
                                if (i == 0)
                                {
                                    tab.t250[ch][wr][time_tab/250] = numb_str.toInt();
                                }
                                else if (i == 1)
                                {
                                    tab.t100[ch][wr][time_tab/100] = numb_str.toInt();
                                }
                                else if (i == 2)
                                {
                                    tab.t50[ch][wr][time_tab/50] = numb_str.toInt();
                                }
                            }
                        }

                        i_way++;
                        numb_str="";
                    }

                }

            }

            file.close();
        }

    }

}

double ReadingProcessing::Offset_add(int q1, int q2, int q3, int q4, double add_offset)
{
    Offset[q1][q2][q3][q4]= Offset[q1][q2][q3][q4] + add_offset;
    return Offset[q1][q2][q3][q4];
}

void ReadingProcessing::Offset_save(QStringList files)
{
    char nameOffset[1200] = "";
    char nameOffset_all[1200] = "";
    QByteArray ba = QFileInfo(files[0]).absolutePath().toLocal8Bit();
    const char *c_str2 = ba.data();

    strcat(nameOffset, c_str2);
//    strcat(nameOffset, "/ImageAvto");

//    QDir dir(nameOffset); // создание папки
//    if (!dir.exists()) {
//        dir.mkpath(".");
//    }

    strcat(nameOffset_all, nameOffset);
    FILE * fi;
    strcat(nameOffset_all, "/Offset_all.txt");
    fi = fopen(nameOffset_all, "w");

    fprintf(fi, "Offset");

    fprintf(fi, "\tBig_step\t\tMiddle_step\t\tSmall_step\t\tResult\t\n");

    for (int ch_num = 0; ch_num < 14; ch_num++)
        for (int wr_num = 0; wr_num < 5; wr_num++)
        {
            if(wr_num == 4)
                fprintf(fi, "Ch_%dWire_All\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\n",
                        ch_num,
                        Offset[ch_num][wr_num][0][0], Offset[ch_num][wr_num][1][0],
                        Offset[ch_num][wr_num][0][1], Offset[ch_num][wr_num][1][1],
                        Offset[ch_num][wr_num][0][2], Offset[ch_num][wr_num][1][2],
                        (Offset[ch_num][wr_num][0][0]+Offset[ch_num][wr_num][0][1]+Offset[ch_num][wr_num][0][2])/3,
                        (Offset[ch_num][wr_num][1][0]+Offset[ch_num][wr_num][1][1]+Offset[ch_num][wr_num][1][2])/3);
            else
                fprintf(fi, "Ch_%dWire_%d\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\t"
                            "%f\t%f\n",
                        ch_num, wr_num,
                        Offset[ch_num][wr_num][0][0], Offset[ch_num][wr_num][1][0],
                        Offset[ch_num][wr_num][0][1], Offset[ch_num][wr_num][1][1],
                        Offset[ch_num][wr_num][0][2], Offset[ch_num][wr_num][1][2],
                        (Offset[ch_num][wr_num][0][0]+Offset[ch_num][wr_num][0][1]+Offset[ch_num][wr_num][0][2])/3,
                        (Offset[ch_num][wr_num][1][0]+Offset[ch_num][wr_num][1][1]+Offset[ch_num][wr_num][1][2])/3);
        }
    fclose(fi);


    FILE * fi_off;
    strcat(nameOffset, "/Offset.txt");
    fi_off = fopen(nameOffset, "w");

    fprintf(fi_off, "Offset");

    fprintf(fi_off, "\tThe_first\tThe_second\n");

    for (int ch_num = 0; ch_num < 14; ch_num++)
    {
        fprintf(fi_off, "Ch_%d\t"
                    "%d\t%d\n",
                ch_num,
                int((Offset[ch_num][4][0][0]+Offset[ch_num][4][0][1]+Offset[ch_num][4][0][2])/3+0.5),
                int((Offset[ch_num][4][1][0]+Offset[ch_num][4][1][1]+Offset[ch_num][4][1][2])/3+0.5));
    }
    fclose(fi_off);

};
