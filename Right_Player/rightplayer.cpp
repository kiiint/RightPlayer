#include "rightplayer.h"
#include "ui_rightplayer.h"

RightPlayer::RightPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RightPlayer)
{
    ui->setupUi(this);

    r_player = new QMediaPlayer();
    r_playlist = new QMediaPlaylist();
    r_player->setPlaylist(r_playlist);

    connect (ui->openfile, &QPushButton::clicked, this, &RightPlayer::browsefile);
    connect(ui->playlisttable, &QListWidget::doubleClicked,this, &RightPlayer::songselected);
    connect (ui->stop_play, &QPushButton::clicked, this, &RightPlayer::playsong);
    connect(r_player, &QMediaPlayer::currentMediaChanged, this, &RightPlayer::curschange);

    ui->playlisttable->clear();

}

RightPlayer::~RightPlayer()
{
    delete ui;
}

void RightPlayer::browsefile()
{
    QString r_fileway = QFileDialog::getOpenFileName(this, "Open folder", QDir::homePath(), "MP3 *.mp3");
    ui->playlisttable->addItem(r_fileway);
}
void RightPlayer::songselected()
{
    QString name_song = ui->playlisttable->currentItem()->text();
    ui->songname->setText(name_song);
    r_player->setMedia(QUrl::fromLocalFile(r_fileway + QDir::separator()+name_song));

}

void RightPlayer::playsong()
{
    if (r_player->state() == QMediaPlayer::PlayingState)
            r_player->pause();
        else
            r_player->play();
}

void RightPlayer::curschange(QMediaContent media)
{
    QString songway = media.canonicalUrl().toString();
    ui->songname->setText(songway.remove(0, songway.lastIndexOf("/") + 1));
}

void RightPlayer::statechange(int state)
{
    switch(state) {
    case QMediaPlayer::StoppedState: ui->stop_play->setText(">"); break;
    case QMediaPlayer::PlayingState: ui->stop_play->setText("||"); break;
    }
}



