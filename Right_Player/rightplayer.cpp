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

    ui->volumesong->setRange(0, 100);
    ui->volumesong->setValue(50);
    r_player->setVolume(50);

    connect (ui->openfile, &QPushButton::clicked, this, &RightPlayer::browsefile);
    connect(ui->playlisttable, &QListWidget::doubleClicked,this, &RightPlayer::songselected);
    connect (ui->stop_play, &QPushButton::clicked, this, &RightPlayer::playsong);
    connect (ui->volumesong, &QSlider::valueChanged, r_player, &QMediaPlayer::setVolume);
    connect(r_player, &QMediaPlayer::currentMediaChanged, this, &RightPlayer::curschange);
    connect(r_player, &QMediaPlayer::stateChanged, this, &RightPlayer::statechange);
    connect(r_player, &QMediaPlayer::positionChanged, this, &RightPlayer::positionchange);
    connect(r_player, &QMediaPlayer::durationChanged, this, &RightPlayer::durationchange);

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
    if (r_player->state() == QMediaPlayer::PlayingState){
        r_player->pause();
        ui->stop_play->setText(">");
    }else{
        r_player->play();
    }
}

void RightPlayer::on_mute_clicked()
{
    if(ui->mute->text() == "Mute"){
        r_player->setMuted(true);
        ui->mute->setText("Unmute");
    }else{
        r_player->setMuted(false);
        ui->mute->setText("Mute");
    }
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


void RightPlayer::on_slidertime_sliderMoved(int position)
{
    r_player->setPosition(position);
}

void RightPlayer::durationchange(qint64 position)
{
    ui->slidertime->setMaximum(position);
}

void RightPlayer::positionchange(qint64 position)
{
    int fullsong = r_player->duration();
    ui->slidertime->setValue(position);
    QTime time = QTime::fromMSecsSinceStartOfDay(position);
    QTime fulltime = QTime::fromMSecsSinceStartOfDay(fullsong);

    ui->timesong->setText(time.toString("mm:ss") + "/" + fulltime.toString("mm:ss"));
}
