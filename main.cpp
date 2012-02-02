
#include "submanager.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv){
    QApplication app(argc, argv);
    MainWindow window;
    STVideoPlayer *vp = new STVideoPlayer("../subteacher/film.avi", &window);
    SubManager *sm = new SubManager("../subteacher/film.srt", "../subteacher/film2.srt", &window, vp);

    window.show();
    app.exec();

    delete sm;
    return 0;
}
