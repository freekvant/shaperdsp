#include "limitparams.h"
#include "ui_limitparams.h"

LimitParams::LimitParams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LimitParams)
{
    ui->setupUi(this);
}

LimitParams::~LimitParams()
{
    delete ui;
}

void LimitParams::on_pushButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Save configuration"),
                                              tr("Configuration name:"), QLineEdit::Normal,
                                                tr("<New configuration> "), &ok);
    for (int i=0; i<ui->comboBox->count();i++)
        if (text==ui->comboBox->itemText(i)){
            ok=false;
            QMessageBox::critical(this,"","Item already exists");

        }


       if (ok && !text.isEmpty()){
             ui->comboBox->addItem(text);
             ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
       }


}

void LimitParams::on_pushButton_4_clicked()
{
    close();
}

void LimitParams::on_deleteConf_button_clicked()
{
    if (ui->comboBox->currentText()!="Default")
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
}
