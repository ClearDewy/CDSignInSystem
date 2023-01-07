#ifndef ACCOUNTWND_H
#define ACCOUNTWND_H

#include <QWidget>
#include <qsqltablemodel.h>
#include "sql.h"
#include <QMessageBox>

namespace Ui {
class AccountWnd;
}

class AccountWnd : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWnd(Sql*,QWidget *parent = nullptr);
    ~AccountWnd();

private slots:
    void on_addButton_clicked();

    void on_deleteUserButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::AccountWnd *ui;
    Sql *sql;
    QSqlTableModel *tmodel;
};

#endif // ACCOUNTWND_H
