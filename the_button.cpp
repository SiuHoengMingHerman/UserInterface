//
// Created by twak on 11/11/2019.
//

#include "the_button.h"


void TheButton::init(TheButtonInfo* i, std::vector<QLabel*> l) {
    setIcon( *(i->icon) );
    info =  i;
    labels = l;
}


void TheButton::clicked() {
    emit jumpTo(info, labels);
}
