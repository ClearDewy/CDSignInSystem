#ifndef USERWND_H
#define USERWND_H

#include <QWidget>
#include "train.h"
#include "sql.h"
#include <QFile>
#include <QStandardItemModel>

namespace Ui {
class UserWnd;
}

class UserWnd : public QWidget
{
    Q_OBJECT

public:
    explicit UserWnd(Sql*,QWidget *parent = nullptr);
    ~UserWnd();
protected:
    void startTrain();

private slots:

    void on_addButton_clicked();

    void on_saveButton_clicked();

    void on_updateUserButton_clicked();

    void on_deleteUserButton_clicked();

private:
    Ui::UserWnd *ui;
    std::vector<User>updateUserList;
    std::vector<int>deleteUserIdList;
    Sql *sql;
    QStandardItemModel tmodel;
};

#endif // USERWND_H
