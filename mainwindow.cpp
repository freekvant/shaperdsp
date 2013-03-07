#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define PATHDEF "/framework/results"
#define PATHDEF "C:/for_tar"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int i = 0;
    ui->setupUi(this);
//    Collector = new Collect("/windows/D/ShaperDSP/for_tar", this);
    LimitForm = new LimitParams();

    path_settings = new QSettings("settings.conf",QSettings::IniFormat);
    if (!path_settings->childGroups().contains("Paths")){
         path = QFileDialog::getExistingDirectory(this,tr("Boards directory"),"C:/"
                                                    ,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
         if (path ==""){
             QCoreApplication::quit();
             return;
         }
        path_settings->setValue("Paths/BoardPath",path);
        path_settings->sync();
    }
    else
            path = path_settings->value("Paths/BoardPath").toString();

    qDebug()<<QApplication::applicationDirPath();

    Collector = new Collect(path, this);
    Collector->show();
    Collector->CollectAllInfo();
    ui->listWidget->addItems(Collector->GetBoardList());
    for(i = 0; i < ui->listWidget->count(); i++)
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    ui->Tab2ComboBID->addItems(Collector->GetBoardList());
    ui->Tab3ComboBID->addItems(Collector->GetBoardList());
    ui->Tab1ComboTestNames->addItems(Collector->GetTestList());

    order = new QStringList;


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Tab1ComboTestNames_currentIndexChanged(int index)
{
    QStringList shapeNames,famshapeNames,slNames,famSlNames,noiseNames,fsrNames;


    shapeNames << "max_diff" << "t_0" << "t_dif" << "Re(B1)"<< "Im(B1)" << "t_scint" << "a_tail" << "t_tail"<< "Re(B2)"<< "Im(B2)" << "b";
    famshapeNames<<"A"<<"t_0"<< "t_dif" << "Re(B1)"<< "Im(B1)" << "t_scint"<< "Re(B2)"<< "Im(B2)" << "b1"<<"b2";
    slNames<<"p0"<<"p1"<<"p2"<<"p3"<<"p4"<<"p5"<<"p6";
    famSlNames<<"p0"<<"p1";//<<"p2"<<"p3"<<"p4"<<"p5"<<"p6";
    noiseNames<<"N"<<"Ncoh";
    fsrNames<<"E1"<<"E2";



    if(ui->Tab1ComboTestNames->itemText(index) == "shape") {
        ui->Tab1ComboParameter->clear();
        ui->Tab1ComboParameter->addItems(shapeNames);
    }

    if(ui->Tab1ComboTestNames->itemText(index) == "famshape") {
        ui->Tab1ComboParameter->clear();
        ui->Tab1ComboParameter->addItems(famshapeNames);
    }
    if(ui->Tab1ComboTestNames->itemText(index) == "sl_test") {
        ui->Tab1ComboParameter->clear();
        ui->Tab1ComboParameter->addItems(slNames);
    }
    if(ui->Tab1ComboTestNames->itemText(index) == "fam_sl_test") {
        ui->Tab1ComboParameter->clear();
        ui->Tab1ComboParameter->addItems(famSlNames);
    }
    if(ui->Tab1ComboTestNames->itemText(index) == "noise") {
        ui->Tab1ComboParameter->clear();
        ui->Tab1ComboParameter->addItems(noiseNames);
    }
    if(ui->Tab1ComboTestNames->itemText(index) == "fast_slow_ratio") {
        ui->Tab1ComboParameter->clear();
        ui->Tab1ComboParameter->addItems(fsrNames);
    }
  /*
   if(ui->Tab1ComboTestNames->itemText(index) == "adcbit" ||
            ui->Tab1ComboTestNames->itemText(index) == "logic" ) {
        ui->Tab1ComboParameter->clear();

    }
    */
}

void MainWindow::on_Tab1Build_clicked()
{
    ui->Tab1TextEdit->clear();
    getFilterBoards(Collector->filterBoards);
    //send dates
    order->clear();
    GenTemplate();

    Collector->GetParamListAll(*order);



    Draw();
}

void MainWindow::GenTemplate()
{
    QString Test = ui->Tab1ComboTestNames->itemText(ui->Tab1ComboTestNames->currentIndex());
    QString Param = ui->Tab1ComboParameter->itemText(ui->Tab1ComboParameter->currentIndex());

    if(Test == "shape") {
        if(Param == "max_diff")
            order->append("difref_tot.dat");
        else
            order->append("parn16_final.dat");
    }
    if(Test == "famshape")
        order->append("parnfam_final.dat");

    if (Test == "sl_test")
        order->append("/sl.log");

    if (Test == "noise")
        order->append("noise.log");

    if (Test == "fam_sl_test")
        order->append("fam_sl.log");

    if (Test == "fast_slow_ratio")
        order->append("fast_slow_ratio.log");


    GenRegExp();
}

void MainWindow::GenRegExp()
{


    QString Test = ui->Tab1ComboTestNames->itemText(ui->Tab1ComboTestNames->currentIndex());
    QString Param = ui->Tab1ComboParameter->itemText(ui->Tab1ComboParameter->currentIndex());
    if(Test == "shape")
    {

        if(Param == "max_diff") { order->append("none"); order->append("3");  }

        if (Param =="t_0" )     {  order->append("none");order->append("2");}
        if (Param =="t_dif" )   {  order->append("none");  order->append("3");}
        if (Param =="Re(B1)" )  {  order->append("none");order->append("3");}
        if (Param =="Im(B1)" )   { order->append("none");order->append("4");}
        if (Param =="t_scint" ) {  order->append("none");order->append("5");}
        if (Param =="a_tail" )   { order->append("none");order->append("6");}
        if (Param =="t_tail" )  {  order->append("none");order->append("7");}
        if (Param =="Re(B2)" )  {  order->append("none"); order->append("8");}
        if (Param =="Im(B2)" )  {  order->append("none");order->append("9");}
        if (Param =="b" )       {  order->append("none");order->append("10");}




    }
    if(Test == "famshape")
    {

           if(Param == "A") { order->append("none"); order->append("1");}
           if (Param =="t_0" )   {  order->append("none");  order->append("2");}
           if (Param =="t_dif" )   {  order->append("none");  order->append("3");}
           if (Param =="Re(B1)" )  {  order->append("none");order->append("4");}
           if (Param =="Im(B1)" )   { order->append("none");order->append("5");}
           if (Param =="t_scint" ) {  order->append("none");order->append("6");}
           if (Param =="Re(B2)" )  {  order->append("none"); order->append("7");}
           if (Param =="Im(B2)" )  {  order->append("none");order->append("8");}
           if (Param =="b1" ) {order->append("none"); order->append("9"); }
           if (Param =="b2" )  {  order->append("none");order->append("10");}
    }

    if (Test == "sl_test")
    {
        if (Param == "p0")
        {
            order->append("(Ch\\s\\d*\\W)|(p0\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+)");
            order->append("-1");
        }

        if (Param == "p1")
        {
        order->append("(Ch\\s\\d*\\W)|(p1\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+)");
        order->append("-1");
        }

        if (Param == "p2")
        {
            order->append("(Ch\\s\\d*\\W)|(p2\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+)");
            order->append("-1");
        }
        if (Param == "p3")
        {
            order->append("(Ch\\s\\d*\\W)|(p3\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+)");
            order->append("0");
        }
        if (Param == "p4")
        {
            order->append("(Ch\\s\\d*\\W)|(p4\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+)");
            order->append("0");
        }
        if (Param == "p5")
        {
            order->append("(Ch\\s\\d*\\W)|(p5\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+)");
            order->append("0");
        }
        if (Param == "p6")
        {
            order->append("(Ch\\s\\d*\\W)|(p6\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+)");
            order->append("0");
        }

    }
    if (Test == "noise")
    {
        if (Param == "N") {   order->append("none"); order->append("1"); }
        if (Param == "Ncoh") { order->append("none"); order->append("2"); }
    }

    if (Test == "fam_sl_test")
    {
        if (Param == "p0")
        {
           order->append("p0\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+");
            order->append("0");
        }
        if (Param == "p1")
        {
           order->append("p1\\s\\W\\s-?\\d+\\W\\d+e\\W\\d+");
            order->append("0");
        }
    }

    if (Test == "fast_slow_ratio")
    {
        if (Param == "E1") { order->append("none");order->append("3");}
        if (Param == "E2") { order->append("none");order->append("4");}

    }




}

void MainWindow::Draw()
{
    QStringList::Iterator it_order;
    it_order = order->begin();
    while(it_order != order->end())
    {
        ui->Tab1TextEdit->append(*it_order);
        it_order++;
    }
}
void MainWindow::getFilterBoards(QStringList &boardlist)
{

    boardlist.clear();
    for (int i=0; i<ui->listWidget->count(); i++ )
        if (ui->listWidget->item(i)->checkState()==Qt::Checked)
            boardlist.append(ui->listWidget->item(i)->text());
}

void MainWindow::on_pushButton_3_clicked()
{

   LimitForm->show();

}

void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->checkState()==Qt::Unchecked)
        for (int i=0; i<ui->listWidget->count(); i++ )
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    else
        for (int i=0; i<ui->listWidget->count(); i++ )
            ui->listWidget->item(i)->setCheckState(Qt::Checked);


}

