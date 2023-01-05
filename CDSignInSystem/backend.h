#ifndef BACKEND_H
#define BACKEND_H

#include <QMainWindow>
#include "train.h"
#include "sql.h"
#include <QFile>
#include <QStandardItemModel>

namespace Ui {
class Backend;
}

class Backend : public QMainWindow
{
    Q_OBJECT

public:
    explicit Backend(QWidget *parent = nullptr);
    ~Backend();

protected:
    void startTrain();

private slots:
    void on_LogOut_clicked();
    void on_addButton_clicked();

    void on_saveButton_clicked();

    void on_updateUserButton_clicked();

    void on_deleteUserButton_clicked();

private:
    Ui::Backend *ui;
    std::vector<User>updateUserList;
    std::vector<int>deleteUserIdList;
    Sql sql;
    QStandardItemModel tmodel;
};

#endif // BACKEND_H
