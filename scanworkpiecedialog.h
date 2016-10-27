#ifndef SCANWORKPIECEDIALOG_H
#define SCANWORKPIECEDIALOG_H

#include <QDialog>

namespace Ui {
class ScanWorkPieceDialog;
}

class ScanWorkPieceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanWorkPieceDialog(QWidget *parent = 0);
    ~ScanWorkPieceDialog();

signals:
    void newSerialNumbers(const QString &);

private slots:
    void setLineEditEnable();
    void setLineEidtDisable();
    void currentSerialNumberslineEdit_returnPressed();
    void targetValueLineEdit_returnPressed();

private:
    Ui::ScanWorkPieceDialog *ui;

    int currentTotalValue;
    int targetMinValue;
    int targetMaxValue;
    int targetValue;
};

#endif // SCANWORKPIECEDIALOG_H
