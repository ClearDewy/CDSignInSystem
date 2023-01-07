#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <sql.h>
#include <QMouseEvent>

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
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    Ui::LogIn *ui;
    Sql sql;
    QPoint *dragPosition;

};

#endif // LOGIN_H
