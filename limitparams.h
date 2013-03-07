#ifndef LIMITPARAMS_H
#define LIMITPARAMS_H

#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class LimitParams;
}

class LimitParams : public QDialog
{
    Q_OBJECT
    
public:
    explicit LimitParams(QWidget *parent = 0);
    ~LimitParams();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_deleteConf_button_clicked();

private:
    Ui::LimitParams *ui;
};

#endif // LIMITPARAMS_H
