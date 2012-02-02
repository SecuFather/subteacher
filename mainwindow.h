#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QTextEdit>
#include <QShortcut>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QFrame* getVideoFrame();

    QPushButton* getPlayPauseButton();
    QPushButton* getStopButton();
    QPushButton* getCheckButton();
    QPushButton* getHintButton();
    QPushButton* getSkipButton();
    QPushButton* getSaveButton();    

    QTextEdit* getAnswerEdit();

    QAction* getIncSubDelayAction();
    QAction* getDecSubDelayAction();
    QAction* getIncTrSubDelayAction();
    QAction* getDecTrSubDelayAction();

    QShortcut* checkShortcut;
    QShortcut* answerShortcut;
    QShortcut* moveShortcut;
    QShortcut* hintShortcut;
    QShortcut* skipShortcut;

private:
    Ui::MainWindow *ui;
public slots:
    void moveHint();
    void setHintEdit(QString str);
    void setTrEdit(QString str);   
    void enablePlayPause(bool state);
};

#endif // MAINWINDOW_H
