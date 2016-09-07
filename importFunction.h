#ifndef IMPORTFUNCTION_H
#define IMPORTFUNCTION_H

#include <QStringList>
#include <QList>

typedef struct stringDataStruct{
    QString lineNum;
    QString magneticValue;
    QString dataQuality;
    QString dateYear;
    QString dateMonth;
    QString dateDay;
    QString timeHour;
    QString timeMinit;
    QString timeSecond;
    long int totalSecond;
}DATAPRO;

int importAllFiles(QStringList &stringList, QList<QList<DATAPRO> > &allData);
int importFunc(QString &readFileName, QList<DATAPRO> &dataPro);

//格式化输出
int DataProPrintf(QString &readFileName, QList<DATAPRO> &dataPro);

int dataProPrintAll(QStringList &stringList, QList<QList<DATAPRO> > &allData);

#endif // IMPORTFUNCTION_H
