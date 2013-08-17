#ifndef APP_H
#define APP_H

#include <QMainWindow>

extern "C" {
#include "gmv.h"
}

namespace Ui {
class App;
}

class App : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit App(QWidget *parent = 0);
    ~App();
    
private slots:
    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

private:
    Ui::App *ui;
    MovieFile *gmv;
    QString filename;
};

#endif // APP_H
