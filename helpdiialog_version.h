#ifndef HELPDIIALOG_VERSION_H
#define HELPDIIALOG_VERSION_H

#include <QDialog>
#include <QPushButton>

class helpDiialog_version : public QDialog
{
    Q_OBJECT
public:
    explicit helpDiialog_version(QWidget *parent = 0);

private:
    QPushButton *btn;

signals:

public slots:

};

#endif // HELPDIIALOG_VERSION_H
