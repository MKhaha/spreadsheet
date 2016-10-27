/********************************************************************************
** Form generated from reading UI file 'scanworkpiecedialog.ui'
**
** Created: Thu Oct 13 10:59:14 2016
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANWORKPIECEDIALOG_H
#define UI_SCANWORKPIECEDIALOG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ScanWorkPieceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *starScanButton;
    QPushButton *stopScanButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *currentSerialNumbersLabel;
    QLineEdit *currentSerialNumberslineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *currentTotalValueLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *targetNumLabel;
    QLineEdit *targetValueLineEdit;
    QProgressBar *progressBar;

    void setupUi(QDialog *ScanWorkPieceDialog)
    {
        if (ScanWorkPieceDialog->objectName().isEmpty())
            ScanWorkPieceDialog->setObjectName(QString::fromUtf8("ScanWorkPieceDialog"));
        ScanWorkPieceDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(ScanWorkPieceDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        starScanButton = new QPushButton(ScanWorkPieceDialog);
        starScanButton->setObjectName(QString::fromUtf8("starScanButton"));

        horizontalLayout->addWidget(starScanButton);

        stopScanButton = new QPushButton(ScanWorkPieceDialog);
        stopScanButton->setObjectName(QString::fromUtf8("stopScanButton"));

        horizontalLayout->addWidget(stopScanButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        currentSerialNumbersLabel = new QLabel(ScanWorkPieceDialog);
        currentSerialNumbersLabel->setObjectName(QString::fromUtf8("currentSerialNumbersLabel"));

        horizontalLayout_2->addWidget(currentSerialNumbersLabel);

        currentSerialNumberslineEdit = new QLineEdit(ScanWorkPieceDialog);
        currentSerialNumberslineEdit->setObjectName(QString::fromUtf8("currentSerialNumberslineEdit"));

        horizontalLayout_2->addWidget(currentSerialNumberslineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        currentTotalValueLabel = new QLabel(ScanWorkPieceDialog);
        currentTotalValueLabel->setObjectName(QString::fromUtf8("currentTotalValueLabel"));

        horizontalLayout_3->addWidget(currentTotalValueLabel);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        targetNumLabel = new QLabel(ScanWorkPieceDialog);
        targetNumLabel->setObjectName(QString::fromUtf8("targetNumLabel"));

        horizontalLayout_3->addWidget(targetNumLabel);

        targetValueLineEdit = new QLineEdit(ScanWorkPieceDialog);
        targetValueLineEdit->setObjectName(QString::fromUtf8("targetValueLineEdit"));

        horizontalLayout_3->addWidget(targetValueLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        progressBar = new QProgressBar(ScanWorkPieceDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(ScanWorkPieceDialog);

        QMetaObject::connectSlotsByName(ScanWorkPieceDialog);
    } // setupUi

    void retranslateUi(QDialog *ScanWorkPieceDialog)
    {
        ScanWorkPieceDialog->setWindowTitle(QApplication::translate("ScanWorkPieceDialog", "ScanWorkPieceDialog", 0));
        starScanButton->setText(QApplication::translate("ScanWorkPieceDialog", "StartScan", 0));
        stopScanButton->setText(QApplication::translate("ScanWorkPieceDialog", "StopScan", 0));
        currentSerialNumbersLabel->setText(QApplication::translate("ScanWorkPieceDialog", "current serial numbers:", 0));
        currentTotalValueLabel->setText(QApplication::translate("ScanWorkPieceDialog", "current total num:", 0));
        targetNumLabel->setText(QApplication::translate("ScanWorkPieceDialog", "target num:", 0));
    } // retranslateUi

};

namespace Ui {
    class ScanWorkPieceDialog: public Ui_ScanWorkPieceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANWORKPIECEDIALOG_H
