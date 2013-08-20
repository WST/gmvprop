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

    void on_comment_textEdited(const QString &arg1);

    void on_rerecords_valueChanged(int arg1);

    void on_tracks_valueChanged(int arg1);

    void on_savestate_stateChanged(int arg1);

    void on_fps_valueChanged(int arg1);

    void on_append_to_the_end_toggled(bool checked);

private:
    Ui::App *ui;
    MovieFile *gmv;
    QString filename;
    bool modified;
    bool wannaSave();
    void save();
};

#endif // APP_H
