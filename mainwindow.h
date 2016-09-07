#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStringList>





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    /**************创建文件菜单****************/
    QMenu *fileMenu;
    QAction *openFileAction;/*创建菜单的按钮（action）*/


    QAction *importFile3;

    /******创建帮助菜单******/
    QMenu *helpMenu;
    QAction *versionAction;/*创建菜单的按钮（action）*/

   void createMenu();//创建菜单函数
   void createAction();//创建动作
   void closeEvent(QCloseEvent *event);//关闭窗口的事件

   /******创建陆地地磁处理菜单******/
   QMenu *landMagneticDataProcess;
   QAction *WCZ_3DataPrintf;
private slots:
   void test();
   //QStringList fileMenu_openFileAction();
   void fileMenu_openFileAction();
   void fileMenu_importAction();

   void printWCZ_3();
};

#endif // MAINWINDOW_H
