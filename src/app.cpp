#include "app.h"
#include "ui_app.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

App::App(QWidget *parent): QMainWindow(parent), ui(new Ui::App), filename("") {
    ui->setupUi(this);
    gmv = 0;
    modified = false;

    ui->toolbar->addAction(ui->actionOpen);
    ui->toolbar->addAction(ui->actionSave);
    ui->toolbar->addAction(ui->actionClose);
    ui->toolbar->addSeparator();
    ui->toolbar->addAction(ui->actionAbout);

    ui->tabs->setVisible(false);
}

App::~App() {
    delete ui;
}

void App::on_actionAbout_triggered() {
    QMessageBox box;
    box.setText("GMV property editor                                                  ");
    box.setInformativeText(QString::fromUtf8("An example application working with GMV files\n© YouTube Sonic TAS community <ystc.ru>"));
    box.setIcon(QMessageBox::Information);
    box.exec();
}

void App::on_actionExit_triggered() {
    qApp->exit();
}

void App::on_actionOpen_triggered() {
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Gens movies (*.gmv)"));
    if(filename.isEmpty()) return;
    if(gmv) disposeGMV(gmv);

    gmv = loadGMV(filename.toStdString().c_str());

    if(!gmv) {
        // Failed to load the provided file
        return;
    }

    ui->comment->setText(QString((const char *) gmv->header.comment));
    ui->rerecords->setValue(gmv->header.rerecords);
    ui->fps->setValue(getInputFrameRate(gmv));
    ui->savestate->setChecked(movieRequiresSavestate(gmv));
    ui->tracks->setValue(getInputControllerNumber(gmv));

    ui->actionSave->setEnabled(true);
    ui->actionClose->setEnabled(true);

    modified = false;

    ui->tabs->setVisible(true);
}

void App::on_actionSave_triggered() {
    save();
}

void App::save() {
    saveGMV(gmv, filename.toStdString().c_str());
    modified = false;
}

bool App::wannaSave() {
    QMessageBox box;
    box.setText("Do you want to save changes?");
    box.setIcon(QMessageBox::Question);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return (box.exec() == QMessageBox::Yes);
}

void App::on_actionClose_triggered() {

    if(modified) {
        if(wannaSave()) save();
    }

    ui->actionClose->setEnabled(false);
    ui->actionSave->setEnabled(false);

    ui->tabs->setVisible(false);
    disposeGMV(gmv);
    gmv = 0;
}

void App::on_comment_textEdited(const QString &arg1) {
    memccpy(gmv->header.comment, arg1.toStdString().c_str(), 1, 40);
    modified = true;
}

void App::on_rerecords_valueChanged(int arg1) {
    gmv->header.rerecords = arg1;
    modified = true;
}

void App::on_tracks_valueChanged(int arg1) {
    setInputControllerNumber(gmv, arg1);
    modified = true;
}

void App::on_savestate_stateChanged(int arg1) {
    requireSavestate(gmv, (arg1 == Qt::Checked));
    modified = true;
}

void App::on_fps_valueChanged(int arg1) {
    setInputFrameRate(gmv, arg1);
    modified = true;
}
