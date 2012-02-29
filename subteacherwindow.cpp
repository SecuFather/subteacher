#include "subteacherwindow.h"
#include "ui_subteacherwindow.h"
#include "settingswindow.h"
#include "wordbasewindow.h"
#include <QFileDialog>
#include "newmediawindow.h"
#include "loadmediawindow.h"
#include "submanager.h"
#include "subteacherthread.h"
#include <QKeyEvent>
#include <QShortcut>

SubteacherWindow::SubteacherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubteacherWindow),
    settingsWindow(new SettingsWindow(this)), wordBaseWindow(new WordBaseWindow(this)),
    fileWindow(new QFileDialog(this)), newMediaWindow(new NewMediaWindow(this)),
    loadMediaWindow(new LoadMediaWindow(this)),
    checkShortcut(new QShortcut(Qt::CTRL + Qt::Key_Space, this)),
    hintShortcut(new QShortcut(Qt::SHIFT + Qt::Key_Space, this))
{
    ui->setupUi(this);
    initWidgets();

    vp = new VideoPlayer(VideoCategory, ui->videoFrame);
    vp->setMinimumWidth(width());
    vp->load(MediaSource("../../film.avi"));
    sm = new SubManager("../../film.srt");
    stt = new SubTeacherThread(vp, sm);

    initSlotsAndSignals();
}

SubteacherWindow::~SubteacherWindow()
{
    delete stt;
    delete sm;
    delete vp;
    delete ui;    
}

void SubteacherWindow::initWidgets(){
    setWindowTitle("Subteacher");
    setWindowIcon(QIcon::fromTheme("face-smile"));

    ui->continueButton->setIcon(QIcon::fromTheme("media-playback-start"));
    ui->newButton->setIcon(QIcon::fromTheme("list-add"));
    ui->saveButton->setIcon(QIcon::fromTheme("document-save"));
    ui->loadButton->setIcon(QIcon::fromTheme("document-open"));
    ui->restartButton->setIcon(QIcon::fromTheme("view-refresh"));
    ui->wordbaseButton->setIcon(QIcon::fromTheme("applications-office"));
    ui->settingsButton->setIcon(QIcon::fromTheme("applications-system"));
    ui->exitButton->setIcon(QIcon::fromTheme("window-close"));

    ui->checkButton->setIcon(QIcon::fromTheme("system-search"));
    ui->hintButton->setIcon(QIcon::fromTheme("help-contents"));
    ui->playButton->setIcon(QIcon::fromTheme("media-playback-start"));
    ui->goBackButton->setIcon(QIcon::fromTheme("media-skip-backward"));
    ui->skipButton->setIcon(QIcon::fromTheme("media-skip-forward"));
}

void SubteacherWindow::initSlotsAndSignals(){
    QObject::connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(showSettings()));
    QObject::connect(ui->wordbaseButton, SIGNAL(clicked()), this, SLOT(showWordBase()));
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(showLoadWindow()));
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(showSaveWindow()));
    QObject::connect(ui->newButton, SIGNAL(clicked()), this, SLOT(showNewMediaWindow()));

    QObject::connect(checkShortcut, SIGNAL(activated()), ui->checkButton, SLOT(animateClick()));
    QObject::connect(hintShortcut, SIGNAL(activated()), ui->hintButton, SLOT(animateClick()));        

    QObject::connect(ui->checkButton, SIGNAL(clicked(bool)), this, SLOT(checkAnswer()));
    QObject::connect(stt, SIGNAL(mediaPlay(bool)), ui->playButton, SLOT(setChecked(bool)));
    QObject::connect(stt, SIGNAL(showSubs()), this, SLOT(showSubs()));
}

void SubteacherWindow::showSettings(){
    settingsWindow->show();
}

void SubteacherWindow::showWordBase(){
    wordBaseWindow->show();
}

void SubteacherWindow::showLoadWindow(){
    QStringList sl;
    sl.append("first");
    sl.append("second");
    loadMediaWindow->show(&sl);
}

void SubteacherWindow::showSaveWindow(){
    fileWindow->setAcceptMode(QFileDialog::AcceptSave);
    fileWindow->show();
}

void SubteacherWindow::showNewMediaWindow(){
    newMediaWindow->show();
}

void SubteacherWindow::checkAnswer(){
    stt->run(true);
}

void SubteacherWindow::showSubs(){
    ui->subLabel->setText(sm->currentSub());
}
