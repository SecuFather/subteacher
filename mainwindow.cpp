#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    checkShortcut = new QShortcut(Qt::CTRL+Qt::Key_L, this);
    answerShortcut = new QShortcut(Qt::CTRL+Qt::Key_K, this);
    moveShortcut = new QShortcut(Qt::CTRL+Qt::Key_M, this);
    hintShortcut = new QShortcut(Qt::CTRL+Qt::Key_H, this);
    skipShortcut = new QShortcut(Qt::CTRL+Qt::Key_S, this);

    QObject::connect(ui->moveButton, SIGNAL(clicked()),
                     this, SLOT(moveHint()));
    QObject::connect(checkShortcut, SIGNAL(activated()),
                     ui->checkButton, SLOT(click()));
    QObject::connect(answerShortcut, SIGNAL(activated()),
                     ui->answerEdit, SLOT(selectAll()));
    QObject::connect(answerShortcut, SIGNAL(activated()),
                     ui->answerEdit, SLOT(setFocus()));
    QObject::connect(moveShortcut, SIGNAL(activated()),
                     ui->moveButton, SLOT(click()));
    QObject::connect(hintShortcut, SIGNAL(activated()),
                     ui->hintButton, SLOT(click()));
    QObject::connect(skipShortcut, SIGNAL(activated()),
                     ui->skipButton, SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete moveShortcut;
    delete answerShortcut;
    delete checkShortcut;
    delete ui;
}

QFrame* MainWindow::getVideoFrame(){
    return ui->videoFrame;
}

QPushButton* MainWindow::getPlayPauseButton(){
    return ui->playPauseButton;
}
QPushButton* MainWindow::getStopButton(){
    return ui->stopButton;
}
QPushButton* MainWindow::getCheckButton(){
    return ui->checkButton;
}

QPushButton *MainWindow::getHintButton(){
    return ui->hintButton;
}

QPushButton *MainWindow::getSkipButton(){
    return ui->skipButton;
}

QPushButton *MainWindow::getSaveButton(){
    return ui->saveButton;
}

QTextEdit *MainWindow::getAnswerEdit(){
    return ui->answerEdit;
}

QAction *MainWindow::getIncSubDelayAction(){
    return ui->incSubDelay;
}

QAction *MainWindow::getDecSubDelayAction(){
    return ui->decSubDelay;
}

QAction *MainWindow::getIncTrSubDelayAction(){
    return ui->incTrSubDelay;
}

QAction *MainWindow::getDecTrSubDelayAction(){
    return ui->decTrSubDelay;
}

void MainWindow::moveHint(){
    ui->answerEdit->setPlainText(ui->hintEdit->toPlainText());
}

void MainWindow::setHintEdit(QString str){
    ui->hintEdit->setPlainText(str);
}

void MainWindow::setTrEdit(QString str){
    ui->trEdit->append(str);
    QScrollBar * sb = ui->trEdit->horizontalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::enablePlayPause(bool state){
    ui->playPauseButton->setEnabled(state);
    ui->checkButton->setEnabled(!state);
}





