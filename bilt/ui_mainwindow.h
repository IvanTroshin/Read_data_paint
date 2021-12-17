/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_open;
    QPushButton *pushButton_open_tables;
    QPushButton *pushButton_offsets;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *plot_time;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Small_step;
    QPushButton *Middle_step;
    QPushButton *Big_step;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QPushButton *Save;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *checkBox_offset;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *first_offset;
    QSpinBox *second_offset;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton_first_line;
    QRadioButton *radioButton_second_line;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_left;
    QPushButton *pushButton_right;
    QPushButton *pushButton_sevf_offset;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1127, 594);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(97, 78, 78, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(153, 0, 3, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(203, 203, 203, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush4(QColor(152, 152, 152, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush4);
        QBrush brush5(QColor(97, 97, 97, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush5);
        QBrush brush6(QColor(157, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush6);
        QBrush brush7(QColor(255, 255, 255, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush7);
        QBrush brush8(QColor(144, 0, 0, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Link, brush8);
        QBrush brush9(QColor(0, 0, 0, 128));
        brush9.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Link, brush8);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        QBrush brush10(QColor(122, 122, 122, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        QBrush brush11(QColor(0, 120, 215, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush11);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Link, brush8);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush9);
#endif
        MainWindow->setPalette(palette);
        MainWindow->setFocusPolicy(Qt::TabFocus);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_open = new QPushButton(centralwidget);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));
        QFont font;
        font.setPointSize(10);
        pushButton_open->setFont(font);
        pushButton_open->setIconSize(QSize(15, 15));
        pushButton_open->setAutoExclusive(false);
        pushButton_open->setAutoDefault(false);

        horizontalLayout_2->addWidget(pushButton_open);

        pushButton_open_tables = new QPushButton(centralwidget);
        pushButton_open_tables->setObjectName(QString::fromUtf8("pushButton_open_tables"));
        pushButton_open_tables->setFont(font);
        pushButton_open_tables->setIconSize(QSize(15, 15));

        horizontalLayout_2->addWidget(pushButton_open_tables);

        pushButton_offsets = new QPushButton(centralwidget);
        pushButton_offsets->setObjectName(QString::fromUtf8("pushButton_offsets"));
        pushButton_offsets->setFont(font);

        horizontalLayout_2->addWidget(pushButton_offsets);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(false);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush12(QColor(105, 105, 105, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush12);
        textEdit->setPalette(palette1);
        QFont font1;
        font1.setPointSize(8);
        textEdit->setFont(font1);
        textEdit->setMouseTracking(true);
        textEdit->setTabletTracking(false);
        textEdit->setAcceptDrops(true);

        gridLayout_2->addWidget(textEdit, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        plot_time = new QCustomPlot(centralwidget);
        plot_time->setObjectName(QString::fromUtf8("plot_time"));
        plot_time->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(plot_time);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        Small_step = new QPushButton(centralwidget);
        Small_step->setObjectName(QString::fromUtf8("Small_step"));
        Small_step->setFont(font);

        verticalLayout_3->addWidget(Small_step);

        Middle_step = new QPushButton(centralwidget);
        Middle_step->setObjectName(QString::fromUtf8("Middle_step"));
        Middle_step->setFont(font);

        verticalLayout_3->addWidget(Middle_step);

        Big_step = new QPushButton(centralwidget);
        Big_step->setObjectName(QString::fromUtf8("Big_step"));
        QFont font2;
        font2.setPointSize(10);
        font2.setKerning(true);
        Big_step->setFont(font2);

        verticalLayout_3->addWidget(Big_step);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QFont font3;
        font3.setPointSize(9);
        comboBox->setFont(font3);

        horizontalLayout->addWidget(comboBox);

        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setFont(font3);

        horizontalLayout->addWidget(comboBox_2);


        verticalLayout_3->addLayout(horizontalLayout);

        Save = new QPushButton(centralwidget);
        Save->setObjectName(QString::fromUtf8("Save"));
        Save->setFont(font3);

        verticalLayout_3->addWidget(Save);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        checkBox_offset = new QCheckBox(centralwidget);
        checkBox_offset->setObjectName(QString::fromUtf8("checkBox_offset"));
        QFont font4;
        font4.setPointSize(10);
        font4.setStrikeOut(false);
        checkBox_offset->setFont(font4);
        checkBox_offset->setTabletTracking(false);
        checkBox_offset->setChecked(false);
        checkBox_offset->setTristate(false);

        verticalLayout_3->addWidget(checkBox_offset);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        first_offset = new QSpinBox(centralwidget);
        first_offset->setObjectName(QString::fromUtf8("first_offset"));
        first_offset->setMaximum(99999);
        first_offset->setValue(7);

        horizontalLayout_5->addWidget(first_offset);

        second_offset = new QSpinBox(centralwidget);
        second_offset->setObjectName(QString::fromUtf8("second_offset"));
        second_offset->setMaximum(99999);
        second_offset->setValue(13);

        horizontalLayout_5->addWidget(second_offset);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, -1, -1);
        radioButton_first_line = new QRadioButton(centralwidget);
        radioButton_first_line->setObjectName(QString::fromUtf8("radioButton_first_line"));

        horizontalLayout_3->addWidget(radioButton_first_line);

        radioButton_second_line = new QRadioButton(centralwidget);
        radioButton_second_line->setObjectName(QString::fromUtf8("radioButton_second_line"));

        horizontalLayout_3->addWidget(radioButton_second_line);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        pushButton_left = new QPushButton(centralwidget);
        pushButton_left->setObjectName(QString::fromUtf8("pushButton_left"));

        horizontalLayout_4->addWidget(pushButton_left);

        pushButton_right = new QPushButton(centralwidget);
        pushButton_right->setObjectName(QString::fromUtf8("pushButton_right"));

        horizontalLayout_4->addWidget(pushButton_right);


        verticalLayout_3->addLayout(horizontalLayout_4);

        pushButton_sevf_offset = new QPushButton(centralwidget);
        pushButton_sevf_offset->setObjectName(QString::fromUtf8("pushButton_sevf_offset"));

        verticalLayout_3->addWidget(pushButton_sevf_offset);


        gridLayout->addLayout(verticalLayout_3, 0, 2, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 5);
        gridLayout->setColumnStretch(2, 1);

        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_open->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        pushButton_open_tables->setText(QCoreApplication::translate("MainWindow", "Open tables", nullptr));
        pushButton_offsets->setText(QCoreApplication::translate("MainWindow", "Offsets", nullptr));
        Small_step->setText(QCoreApplication::translate("MainWindow", "Small step", nullptr));
        Middle_step->setText(QCoreApplication::translate("MainWindow", "Middle step", nullptr));
        Big_step->setText(QCoreApplication::translate("MainWindow", "Big step", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "1 wire", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "2 wire", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "3 wire", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "4 wire", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "All", nullptr));

        Save->setText(QCoreApplication::translate("MainWindow", "Save all graphs", nullptr));
        checkBox_offset->setText(QCoreApplication::translate("MainWindow", "Change the offset", nullptr));
        radioButton_first_line->setText(QCoreApplication::translate("MainWindow", "The first line", nullptr));
        radioButton_second_line->setText(QCoreApplication::translate("MainWindow", "The second line", nullptr));
        pushButton_left->setText(QCoreApplication::translate("MainWindow", "<--", nullptr));
        pushButton_right->setText(QCoreApplication::translate("MainWindow", "-->", nullptr));
        pushButton_sevf_offset->setText(QCoreApplication::translate("MainWindow", "Save new offset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
