#ifndef RIGHTPLAYER_H
#define RIGHTPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QDir>
QT_BEGIN_NAMESPACE
namespace Ui { class RightPlayer; }
QT_END_NAMESPACE

class RightPlayer : public QMainWindow
{
    Q_OBJECT

public:
    RightPlayer(QWidget *parent = nullptr);
    ~RightPlayer();

private slots:

    void songselected();
    void playsong();
    void browsefile();
    void curschange(QMediaContent media);
    void statechange(int state);

private:
    Ui::RightPlayer *ui;
    QMediaPlayer *r_player;
    QMediaPlaylist *r_playlist;
    QString *r_fileway;
};

#endif // RIGHTPLAYER_H
