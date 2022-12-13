//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

/* header added */
#include <sstream>
#include <QtWidgets/QLabel>
/* end */

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    std::vector<QLabel*> labels;
    QTimer* mTimer;
    long updateCount = 0;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(10); // be slightly less annoying
//        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

//        mTimer = new QTimer(NULL);
//        mTimer->setInterval(1000); // 1000ms is one second between ...
//        mTimer->start();
//        connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method
    }
    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

    // set the pointer of the labels
    void setLabels(std::vector<QLabel*> labels);

//private slots:

//    // change the image and video for one button every one second
////    void shuffle();

//    void playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button, std::vector<QLabel*> labels);
    void mPlay();
    void mPause();

};

#endif //CW2_THE_PLAYER_H
