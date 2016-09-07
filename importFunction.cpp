#include "importFunction.h"
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QByteArray>
#include <QMessageBox>


int importAllFiles(QStringList &stringList, QList<QList<DATAPRO> > &allData)
{
    if (stringList.isEmpty())
    {
        QMessageBox::information(0, "警告", "没有选择文件");
        return -1;
    }
    int i = 0;
    for(QStringList::Iterator it = stringList.begin(); it!=stringList.end(); it++)
    {
        QList<DATAPRO> temp;
        allData.push_back(temp);
        importFunc(*it, allData[i]);
        i++;
    }
    QMessageBox::information(0, "数据导入", "导入数据完成^_^");
    return 0;
}



int importFunc(QString &readFileName, QList<DATAPRO> &dataPro)
{

    if(readFileName.isEmpty())
    {
        QMessageBox::information(0, "importFunc Error", "无效的文件名");
    }
    QFile openfile(readFileName);
//
//    QStringList splitList = readFileName.split('.');
    //QString tmpFileName = (QString)"C:\\Users\\Administrator\\Desktop\\0603-1.txt";
   // QFile writefile("C:\\Users\\Administrator\\Desktop\\0603-1.txt");
   // writefile.open(QIODevice::Append |QIODevice::Text);
    if ( openfile.open( QIODevice::ReadOnly ) )
    {
        QTextStream stream( &openfile );

       // QTextStream writeStream( &writefile );
        QString line;
        QStringList fonts;
        QStringList fontsData;
        QStringList fontsTime;
        DATAPRO tmp;
        int count = 0;//删除文件前七行
        do
        {
            line = stream.readLine(); // 不包括“\n”的一行文本
            if (count < 7)
            {
                count++;
                 //QMessageBox::information(0, "test", "运行到importfunc,并打开文件了，开始读了");
                continue;
            }
            //QStringList QStringList::split ( const QChar & sep, const QString & str, bool allowEmptyEntries = FALSE ) [static]
            fonts=line.split(9/*分隔符tab的asc码值*/,QString::SkipEmptyParts/*跳过空的部分*/, Qt::CaseInsensitive/*不区分大小写*/);
            //将读取到的行格式化到自定义结构DATAPRO
            for (int i = 0; i < fonts.size(); ++i)
            {
                if(i == 0)
                {
                    tmp.lineNum = fonts.at(i).toLocal8Bit().constData();
                }
                if(i == 1)
                {
                    tmp.magneticValue = fonts.at(i).toLocal8Bit().constData();
                }
                if(i == 2)
                {
                    tmp.dataQuality = fonts.at(i).toLocal8Bit().constData();
                }
                if(i == 3)
                {
                    QString dataline = fonts.at(i).toLocal8Bit().constData();
                    fontsData=dataline.split('/'/*分隔符/的asc码值*/,QString::SkipEmptyParts, Qt::CaseInsensitive);
                    for (int j = 0; j < fontsData.size(); ++j)
                    {
                        if(j == 0)
                        {
                            tmp.dateYear =(QString)"20" + fontsData.at(j).toLocal8Bit().constData();
                        }
                        if(j == 1)
                        {
                            tmp.dateMonth = fontsData.at(j).toLocal8Bit().constData();
                        }
                        if(j == 2)
                        {
                            tmp.dateDay = fontsData.at(j).toLocal8Bit().constData();
                        }
                    }
                }
                if(i == 4)
                {
                    QString timeline = fonts.at(i).toLocal8Bit().constData();

                    fontsTime=timeline.split(':'/*分隔符:的asc码值*/,QString::SkipEmptyParts, Qt::CaseInsensitive);
                    for (int k = 0; k < fontsTime.size(); ++k)
                    {
                        if(k == 0)
                        {
                            tmp.timeHour = fontsTime.at(k).toLocal8Bit().constData();
                        }
                        if(k == 1)
                        {
                            tmp.timeMinit = fontsTime.at(k).toLocal8Bit().constData();
                        }
                        if(k == 2)
                        {
                            tmp.timeSecond = fontsTime.at(k).toLocal8Bit().constData();
                        }
                    }
                }
            }
            tmp.totalSecond = 3600 * tmp.timeHour.toInt() + 60 * tmp.timeMinit.toInt() + tmp.timeSecond.toInt();

            dataPro.push_back(tmp);

//            writeStream<<tmp.dateYear<<' '<<tmp.dateMonth<<' '<<tmp.dateDay<<' '<<tmp.timeHour<<' '<<tmp.timeMinit<<' '<<tmp.timeSecond
//                      <<' ' << tmp.totalSecond<<' '<<tmp.magneticValue<<'\n';
        }while(!line.isNull());
        openfile.close();

    }
    return 0;
}

int dataProPrintAll(QStringList &stringList, QList<QList<DATAPRO> > &allData)
{
    if (stringList.isEmpty())
    {
        QMessageBox::information(0, "警告", "没有选择文件");
        return -1;
    }
    int i = 0;
    for(QStringList::Iterator it = stringList.begin(); it!=stringList.end(); it++)
    {
       // QMessageBox::information(0, QObject::tr("importallfiles"), *it);

         DataProPrintf(*it, allData[i]);
        i++;
    }
    QMessageBox::information(0, "提示", "文件导出成功");
    return 0;
}

int DataProPrintf(QString &readFileName, QList<DATAPRO> &dataPro)
{
    if (readFileName.isNull() || dataPro.isEmpty())
    {
        QMessageBox::information(0, "问题","文件名或者文件内容为空");
        return -1;
    }
   // QMessageBox::information(0, "test", dataPro[900].lineNum);
    QStringList splitList = readFileName.split('.');
    QString writeFileName = splitList[0] + "-1." + splitList[1];
    QFile writeFile(writeFileName);

    if ( writeFile.open( QIODevice::Text |QIODevice::Append ) )
    {
        QTextStream writeStream( &writeFile );
        for (int i = 0; i < dataPro.size(); ++i)
        {
            writeStream<<dataPro[i].dateYear<<' '<<dataPro[i].dateMonth<<' '<<dataPro[i].dateDay<<' '<<dataPro[i].timeHour<<' '<<dataPro[i].timeMinit
                      <<' '<<dataPro[i].timeSecond <<' ' << dataPro[i].totalSecond<<' '<<dataPro[i].magneticValue<<'\n';
        }
        writeFile.close();
    }
    return 0;
}
