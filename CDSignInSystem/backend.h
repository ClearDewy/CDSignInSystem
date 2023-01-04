#ifndef BACKEND_H
#define BACKEND_H

#include <QMainWindow>
#include "train.h"
#include "sql.h"
#include <QFile>

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

private:
    Ui::Backend *ui;
    std::vector<User>updateUserList;
    Sql sql;
};

#endif // BACKEND_H
