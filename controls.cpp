#include "controls.h"

#include <QBoxLayout>
#include <QToolButton>
#include <QStyle>

controls::controls(QWidget *parent)
    :QWidget(parent)
{
    playbutton = new QToolButton(this);
    playbutton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playbutton, &QAbstractButton::clicked, this, &controls::playClicked);

    stopbutton = new QToolButton(this);
    stopbutton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopbutton->setEnabled(false);

    connect(stopbutton, &QAbstractButton::clicked, this, &controls::stop);

    QBoxLayout *controls = new QHBoxLayout;
    controls->setContentsMargins(0,0,0,0);
    controls->addWidget(stopbutton);
    controls->addWidget(playbutton);
    setLayout(controls);
}

QMediaPlayer::State controls::mediaStatus() const
{
    return status;
}

void controls::setState(QMediaPlayer::State state)
{
    if (state != status) {
        status = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            stopbutton->setEnabled(false);
            playbutton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case QMediaPlayer::PlayingState:
            stopbutton->setEnabled(true);
            playbutton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            stopbutton->setEnabled(true);
            playbutton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}
