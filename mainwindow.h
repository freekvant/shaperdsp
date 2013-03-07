#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QFileDialog>
#include <QSettings>
#include "collect.h"
#include "limitparams.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getFilterBoards(QStringList &boardlist);
    LimitParams *LimitForm;


    
private slots:

    void on_Tab1ComboTestNames_currentIndexChanged(int index);

    void on_Tab1Build_clicked();

    void on_pushButton_3_clicked();



    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;
    Collect *Collector;

    QStringList *order;
    QStringList filterBoardList;
    QSettings *path_settings;
    QString path;

    void GenTemplate();
    void GenRegExp();
    void Draw();

};

#endif // MAINWINDOW_H
