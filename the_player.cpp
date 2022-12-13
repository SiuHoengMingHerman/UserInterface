//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info, labels);
}

/* code added */
void ThePlayer::setLabels(std::vector<QLabel *> l){
    labels = l;
}
/* end */

//void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
//    switch (ms) {
//        case QMediaPlayer::State::StoppedState:
//            play(); // starting playing again...
//            break;
//        case QMediaPlayer::State::PausedState:
//            stop();
//            break;
//    default:
//        break;
//    }
//}

void ThePlayer::jumpTo (TheButtonInfo* button, std::vector<QLabel*> labels) {
    setMedia( * button -> url);
    labels[0]->setText(button->name);
    labels[1]->setText(button->url->toString());
    std::stringstream ss;
    ss << button->size;
    char string[50] = "";
    ss >> string;
    labels[2]->setText(string);
    play();
}

void ThePlayer::mPause(){
    pause();
}

void ThePlayer::mPlay(){
    play();
}
