#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <sql.h>

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_confirmButton_clicked();

    void on_concelButton_clicked();

private:
    Ui::LogIn *ui;
    Sql sql;
};

#endif // LOGIN_H
