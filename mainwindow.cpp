#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "helpDiialog_version.h"
#include <QStringList>

#include "importFunction.h"


QStringList  global_files;
int global_theNumberOfFiles;
QList<QList<DATAPRO> > allData;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("DataPro"));
    createAction();
    createMenu();
    exit(9);



}

//创建menu
void MainWindow::createMenu()
{
    fileMenu = this->menuBar()->addMenu(tr("文件"));//添加文件菜单
    fileMenu->addAction(openFileAction);//添加动作
    fileMenu->addAction(importFile3);

    landMagneticDataProcess = this->menuBar()->addMenu(tr("地磁"));//添加地磁菜单
    landMagneticDataProcess->addAction(WCZ_3DataPrintf);

    helpMenu = this->menuBar()->addMenu(tr("帮助"));//添加帮助菜单
    helpMenu->addAction(versionAction);//添加动作
    helpMenu->addSeparator();//添加分隔符


}
//在menu里边添加动作
void MainWindow::createAction()
{
    /*****************文件菜单下的action*************/
    openFileAction = new QAction(tr("打开"), this);//定义action
    openFileAction->setShortcut((QString)"Ctrl+O");//创建快捷方式
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(fileMenu_openFileAction()));

    importFile3 = new QAction(tr("导入数据"),this);
    importFile3->setShortcut(QString("Ctrl+I"));
    //importFile3->setStatusTip((QString)"导入要处理的数据文件");
    connect(importFile3, SIGNAL(triggered()), this, SLOT(fileMenu_importAction()));

    /****************创建陆地地磁处理菜单********************/
    WCZ_3DataPrintf = new QAction(tr("数据解编-3"), this);
    WCZ_3DataPrintf->setShortcut((QString)"Ctrl+P");
    connect(WCZ_3DataPrintf, SIGNAL(triggered()), this, SLOT(printWCZ_3()));

    /******************帮助菜单下的action******************/
    versionAction = new QAction(tr("版本信息"), this);//定义action
    versionAction->setShortcut((QString)"Ctrl+H");//创建快捷方式

    connect(versionAction,SIGNAL(triggered()), this, SLOT(test()));
}
void MainWindow::test()
{
    helpDiialog_version *helptest = new helpDiialog_version;
    helptest->show();
}

//fileMenu下的槽函数
//打开文件,获得文件名和数量
void MainWindow::fileMenu_openFileAction()
{
    QStringList files = QFileDialog::getOpenFileNames(
                this, "Select one or more files to open",
                "/home",
                "*.txt");
    global_files = files;
    global_theNumberOfFiles = files.count();
    if(global_files.isEmpty())
    {
        QMessageBox::information(0, "打开文件", "打开文件失败");
    }
    else
    {
        QMessageBox::information(0, "打开文件", "打开文件成功");
    }
}
//导入数据
void MainWindow::fileMenu_importAction()
{
    if (global_files.isEmpty())
    {
        QMessageBox::information(this, tr("导入数据"), tr("没有打开要导入的文件，请先打开文件"));
        return;
    }
    importAllFiles(global_files, allData);

}
//格式化输出数据
void MainWindow::printWCZ_3()
{
    //testDataProPrintf();
    if(global_files.isEmpty() || allData.isEmpty())
    {
        QMessageBox::information(0, "消息","内存中没有数据");
        return;
    }
    //DataProPrintf(*global_files.begin(), allData[0]);
    dataProPrintAll(global_files, allData);
}

//关闭程序的提示
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("退出程序"),
                                                               tr("是否退出?"),QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::Yes)
    {
        event->accept();//接收退出信号
    }
    else
    {
        event->ignore();//忽略
    }
}

MainWindow::~MainWindow()
{


}
