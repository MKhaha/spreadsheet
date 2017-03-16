#include "generateqrcodedialog.h"
#include "ui_generateqrcodedialog.h"
#include "qrencodepublic.h"
#include "qrencode.h"
#include <QMessageBox>
#include <QFileDialog>

static QString DefaultQRString = QString("");
static int DefaultImageMargin = 4;
static int DefaultImageSize = 200;
const QString RESULTS_PATH = "./results/";

GenerateQRcodeDialog::GenerateQRcodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateQRcodeDialog)
{
    ui->setupUi(this);

    imageSavePath = "C:\\";
    textCurrentPostion = DefaultQRString;
    imageMargin = DefaultImageMargin;
    imageSize = DefaultImageSize;

    QRegExp regExpForMargin("[1-9][0-9]{0,1}");
    ui->marginLineEdit->setValidator(new QRegExpValidator(regExpForMargin, this));
    QRegExp regExpForImage("[1-9][0-9]{1,2}");
    ui->sizeLineText->setValidator(new QRegExpValidator(regExpForImage, this));

    connect(ui->getFromCurrentPositionPushButton, SIGNAL(clicked(bool)),
            this, SLOT(getTextCurrentPositionPrivateSlots()));
    connect(ui->generateQRcodePushButton, SIGNAL(clicked(bool)),
            this, SLOT(generateQRcode()));
    connect(ui->filePathPushButton, SIGNAL(clicked(bool)),
            this, SLOT(getImageSavePath()));

}

void GenerateQRcodeDialog::getTextCurrentPositionPrivateSlots()
{
    emit getTextCurrentPosition(textCurrentPostion);
}

void GenerateQRcodeDialog::textFromSpreedSheet(QString &text)
{
    ui->codeStringTextEdit->setText(text);
}

void GenerateQRcodeDialog::getImageSavePath()
{
    QString imageSavePathTemp = QFileDialog::getSaveFileName(this,
            QString::fromLocal8Bit("image save as..."),
            "",
            tr("Config Files (*.jpg)"));
    if(imageSavePathTemp.isEmpty())
    {
        return;
    }
    else
    {
        ui->filePathLineEdit->setText(imageSavePathTemp);
        imageSavePath = imageSavePathTemp;
    }
}

void GenerateQRcodeDialog::generateQRcode()
{
    std::string strThisObjectName = this->objectName().toStdString();
    const char* chThisObjectName = strThisObjectName.c_str();

    if(ui->codeStringTextEdit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, tr(chThisObjectName),
                             tr("Code String is NULL"));

        return;
    }

    if(ui->marginLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr(chThisObjectName),
                             tr("margin is NULL, use default " + DefaultImageMargin));
    }
    else
    {
        imageMargin = ui->marginLineEdit->text().toInt();
    }

    if(ui->sizeLineText->text().isEmpty())
    {
        QMessageBox::information(this, tr(chThisObjectName),
                             tr("is NULL, use default " + DefaultImageSize));
    }
    else
    {
        imageSize = ui->sizeLineText->text().toInt();
    }

    QrencodePublic encoder;
    encoder.setMargin(imageMargin);
    encoder.encode(ui->codeStringTextEdit->toPlainText());
    QImage code = encoder.toQImage();

    QString tempMessage = "save image to:" + imageSavePath;
    std::string strMessage = tempMessage.toStdString();
    const char* chMessage = strMessage.c_str();
    QMessageBox::information(this,tr("save image"),tr(chMessage));
    code.scaled(imageSize, imageSize).save(imageSavePath,"JPG");
}

GenerateQRcodeDialog::~GenerateQRcodeDialog()
{
    delete ui;
}
