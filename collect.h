#ifndef COLLECT_H
#define COLLECT_H

#include <QDialog>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QProgressDialog>
#include <QMessageBox>

namespace Ui {
    class Collect;
}

class Collect : public QDialog
{
    Q_OBJECT

public:
    explicit Collect(const QString &path,QWidget *parent = 0);
    ~Collect();

    void CollectAllInfo();
    int GetBoardsNum()  { return BoardList->count();}
    int GetFilesNum()   { return FileList->count();}
    QStringList& GetBoardList() {return *BoardList;}
    QStringList& GetTestList() {return *TestList;}
    QStringList& GetFileList() {return *FileList;}
    void GetParamListAll(QStringList & order);
    void ParseFile1(QStringList & order);
    void GetColumnValues(QStringList &destList, int column, QString filename );
    void ExecRegExp(QStringList &destList, QString regexp, QString fileName);

    QStringList filterBoards;


private:
    Ui::Collect *ui;

    void CollectFileNames(const QString &path);
    void CollectBoardNames(const QString &path);
    void CollectTestNames(const QString &path);

    QString BasePath;
    int BasePathLenght;
    QStringList *FileList;
    QStringList *BoardList;
    QStringList *TestList;

    QStringList::Iterator it1;

    float DirCount;
};

#endif // COLLECT_H
