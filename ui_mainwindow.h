/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *Com_combo;
    QPushButton *Com_Refresh_btn;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rf_btn;
    QComboBox *rf_id_combobox;
    QSpacerItem *horizontalSpacer;
    QRadioButton *imu_btn;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_serial_init;
    QPushButton *btn_serial_stop;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(546, 646);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Com_combo = new QComboBox(centralwidget);
        Com_combo->setObjectName(QStringLiteral("Com_combo"));

        horizontalLayout->addWidget(Com_combo);

        Com_Refresh_btn = new QPushButton(centralwidget);
        Com_Refresh_btn->setObjectName(QStringLiteral("Com_Refresh_btn"));

        horizontalLayout->addWidget(Com_Refresh_btn);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        rf_btn = new QRadioButton(centralwidget);
        rf_btn->setObjectName(QStringLiteral("rf_btn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rf_btn->sizePolicy().hasHeightForWidth());
        rf_btn->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(rf_btn);

        rf_id_combobox = new QComboBox(centralwidget);
        rf_id_combobox->setObjectName(QStringLiteral("rf_id_combobox"));
        sizePolicy.setHeightForWidth(rf_id_combobox->sizePolicy().hasHeightForWidth());
        rf_id_combobox->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(rf_id_combobox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        imu_btn = new QRadioButton(centralwidget);
        imu_btn->setObjectName(QStringLiteral("imu_btn"));

        horizontalLayout_2->addWidget(imu_btn);


        gridLayout->addLayout(horizontalLayout_2, 8, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 10, -1, -1);
        btn_serial_init = new QPushButton(centralwidget);
        btn_serial_init->setObjectName(QStringLiteral("btn_serial_init"));

        horizontalLayout_3->addWidget(btn_serial_init);

        btn_serial_stop = new QPushButton(centralwidget);
        btn_serial_stop->setObjectName(QStringLiteral("btn_serial_stop"));

        horizontalLayout_3->addWidget(btn_serial_stop);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setShowGrid(false);

        gridLayout->addWidget(tableWidget, 14, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 546, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\266\205\346\240\270IMU Receiver", Q_NULLPTR));
        Com_Refresh_btn->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        rf_btn->setText(QApplication::translate("MainWindow", "Wireless Receiver, ID=", Q_NULLPTR));
        imu_btn->setText(QApplication::translate("MainWindow", "IMU", Q_NULLPTR));
        btn_serial_init->setText(QApplication::translate("MainWindow", "Start Connection", Q_NULLPTR));
        btn_serial_stop->setText(QApplication::translate("MainWindow", "Stop Connection", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
