/* 
 * File:   QClickLabel.cpp
 * Author: matej
 * 
 * Created on April 15, 2014, 10:55 PM
 */

#include "QClickLabel.h"
#include <QMouseEvent>


QClickLabel::QClickLabel(QWidget * parent ) : QLabel(parent) {
}

QClickLabel::~QClickLabel() {
}

void QClickLabel::mousePressEvent ( QMouseEvent * event ) {
  
  click_x = event->x();
  click_y = event->y();
  
  emit clicked();
}

QPoint QClickLabel::GetMousePosition() {
  return QPoint(click_x, click_y);
}


