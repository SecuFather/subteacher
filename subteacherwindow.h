#ifndef SUBTEACHERWINDOW_H
#define SUBTEACHERWINDOW_H

#include <QMainWindow>

#include <Phonon>
#include <phonon/VideoPlayer>
using namespace Phonon;

namespace Ui {
class SubteacherWindow;
}
class SettingsWindow;
class WordBaseWindow;
class QFileDialog;
class NewMovieWindow;
class QShortcut;

class SubteacherWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SubteacherWindow(QWidget *parent = 0);
    ~SubteacherWindow();

    void initWidgets();
    void initSlotsAndSignals();
    
private:
    VideoPlayer *vp;
    Ui::SubteacherWindow *ui;
    SettingsWindow *settingsWindow;
    WordBaseWindow *wordBaseWindow;
    QFileDialog *fileWindow;
    NewMovieWindow *newMovieWindow;

    QShortcut *checkShortcut;
    QShortcut *hintShortcut;

public slots:
    void showSettings();
    void showWordBase();
    void showLoadWindow();
    void showSaveWindow();
    void showNewMovieWindow();
};

#endif // SUBTEACHERWINDOW_H
