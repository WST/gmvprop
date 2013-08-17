#include "app.h"
#include "ui_app.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

App::App(QWidget *parent): QMainWindow(parent), ui(new Ui::App), filename("") {
    ui->setupUi(this);
    gmv = 0;

    ui->toolbar->addAction(ui->actionOpen);
    ui->toolbar->addAction(ui->actionSave);
    ui->toolbar->addAction(ui->actionClose);
    ui->toolbar->addSeparator();
    ui->toolbar->addAction(ui->actionAbout);
}

App::~App()
{
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
    ui->comment->setText(QString((const char *) gmv->header.comment));
    ui->rerecords->setValue(gmv->header.rerecords);

    ui->actionSave->setEnabled(true);
    ui->actionClose->setEnabled(true);
    ui->rerecords->setEnabled(true);
    ui->comment->setEnabled(true);
}

void App::on_actionSave_triggered() {
    memccpy(gmv->header.comment, ui->comment->text().toStdString().c_str(), 1, 40);
    gmv->header.rerecords = ui->rerecords->value();
    saveGMV(gmv, filename.toStdString().c_str());
}

void App::on_actionClose_triggered() {
    ui->actionClose->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->rerecords->setEnabled(false);
    ui->comment->setEnabled(false);
    ui->comment->clear();
    ui->rerecords->clear();
    disposeGMV(gmv);
    gmv = 0;
}
