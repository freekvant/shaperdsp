#include "collect.h"
#include "ui_collect.h"

Collect::Collect(const QString &path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Collect)
{
    ui->setupUi(this);


    BasePath = path;
    BasePathLenght = BasePath.length();
    FileList = new QStringList;
    BoardList = new QStringList;
    TestList = new QStringList;
    DirCount = 0;

//TODO: todo

}

Collect::~Collect()
{
    delete ui;
}

void Collect::CollectAllInfo()
{
    BoardList->clear();
    FileList->clear();
    TestList->clear();
    DirCount = 0;
    CollectBoardNames(BasePath);
    qDebug()<<BoardList->count()<<" boards found";
    CollectFileNames(BasePath);
    qDebug()<<FileList->count()<<" files found";

}

void Collect::CollectFileNames(const QString &path)
{
QDir dir(path);
QStringList::Iterator it;
//QRegExp rx("\\b(.txt|difref_tot.dat|parn16_final.dat|parnfam_final.dat|sl.log|noise\B)\\b");
//QRegExp rx("\\b(log|difref_tot.dat|parn16_final.dat|parnfam_final.dat|sl.log|fam_sl|noise|fast_slow_ratio.log)\\b");
QRegExp rx("\\Wtxt|^difref_tot\\Wdat|^fam_sl.log|^parn16_final\\Wdat|^parnfam_final\\Wdat|^sl.log|^noise\\Wlog|^fast_slow_ratio\\Wlog");


    int pos = 0;
    QStringList files = dir.entryList();
    it = files.begin();
    while (it != files.end()) {
        if (rx.indexIn(*it,pos)!=-1)
            FileList->append(QFileInfo(path, *it).absoluteFilePath());


        ++it;
    }



    //------------------Process Meter---------------------------------
   if(dir.absolutePath().length() == BasePathLenght+13 )// filter slash + 12 symbols board id
    {
        DirCount++;
    //    qDebug()<<"Proc"<<DirCount/BoardList->count();
        ui->progressBar->setValue(DirCount/BoardList->count()*100);
        qApp->processEvents();
        if (ui->progressBar->value()==100)
            this->close();
    }
    //------------------Process Meter---------------------------------


    QStringList dirs = dir.entryList(QDir::Dirs);
    it = dirs.begin();
    while (it != dirs.end()) {
        if (*it != "." && *it != "..")
            CollectFileNames(path + "/" + *it);
        ++it;
    }
}

void Collect::CollectBoardNames(const QString &path)
{

    QDir dir(path);
    if (dir.exists())
    {

        QStringList::Iterator it;
        QStringList dirs = dir.entryList();
            it = dirs.begin();
            while (it != dirs.end()) {
                if (*it != "." && *it != "..") {
                    BoardList->append(*it);


                    CollectTestNames(path + "/" + *it);
                }
                ++it;
            }
    }
    else
    {
        QMessageBox::critical(this,"","Path don't exists");
        QCoreApplication::quit();
    }
}

void Collect::CollectTestNames(const QString &path)
{
//QRegExp rx("\\b(adcbit|famshape|fam_sl_test|fast_slow_ratio|logic|noise|shape|sl_test)\\b");
QRegExp rx("famshape|^fam_sl_test|fast_slow_ratio|^noise|^shape|^sl_test");
//QRegExpValidator valid(rx, 0);
int pos = 0;
QDir dir(path);
if (dir.exists())
{

    QStringList::Iterator it;
    QStringList dirs = dir.entryList();

        it = dirs.begin();
        while (it != dirs.end()) {
     //       if (valid.validate(*it, pos))
              if (rx.indexIn(*it,pos)!=-1)
                TestList->append(*it);
            ++it;
        }
        TestList->removeDuplicates();
}
    else
{
        QMessageBox::critical(this,"","Path don't exists");
        QCoreApplication::exit();
}

}


void Collect::GetParamListAll(QStringList & order)
{
QStringList::Iterator it_order;
QStringList::Iterator it;
QStringList *FilterFileList = new QStringList;
QString FPath;
int index;

    for (int i=0; i<FileList->length(); i++)
        for (int j=0;j<filterBoards.length();j++)
            if (FileList->at(i).contains(filterBoards.at(j)))
                FilterFileList->append(FileList->at(i));


    FilterFileList->removeDuplicates();
    it = FilterFileList->begin();

    while (it != FilterFileList->end())
    {
        FPath = *it;
        it_order = order.begin();
        index = FPath.indexOf(*it_order);


        if(index != -1)  {

            order.append(FPath); //full path

            ParseFile1(order);
        }

   ++it;

    }
   // qDebug("End of GetParamListAll");
}


void Collect::ParseFile1(QStringList & order)
{
   // qDebug("Parse");

QStringList::Iterator it_order;
    it_order = order.begin();
    it_order += 3; //full path
    if (*(it_order-2)=="none")
        GetColumnValues(order,(*--it_order).toInt(),*it_order);
    else
        ExecRegExp(order,*(it_order-2),*it_order);




}


void Collect::GetColumnValues(QStringList &destList, int column, QString filename )
{
    QStringList list;
    QFile fileParse(filename);
    if (fileParse.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream out(&fileParse);
        while (!out.atEnd())
        {
            list = out.readLine().split(QRegExp("\\s+"));
            if (column < list.length())
                destList.append(list[column]);


//             destList.append(out.readLine().split(QRegExp("\\s+"))[column]);
        }

    }
    fileParse.close();

}

void Collect::ExecRegExp(QStringList &destList, QString regexp, QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream t( &file );

    QRegExp rx(regexp);
    if (rx.isValid() && !rx.isEmpty())
        while ( !t.atEnd() )
        {
            if (rx.indexIn(t.readLine())!=-1)
                destList.append(rx.cap());//answer

        }
    else
        QMessageBox::information(this,"","RegExp Error");
}

