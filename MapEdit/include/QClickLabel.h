/* 
 * File:   QClickLabel.h
 * Author: matej
 *
 * Created on April 15, 2014, 10:55 PM
 */

#ifndef QCLICKLABEL_H
#define	QCLICKLABEL_H

#include <QLabel>
#include <utility>

using namespace std;

class QClickLabel : public QLabel {
public:
   
Q_OBJECT
 
public:
  explicit QClickLabel(QWidget * parent = 0 );
  virtual ~QClickLabel();  

  QPoint GetMousePosition();
 
signals:
    void clicked();
 
protected:
    void mousePressEvent ( QMouseEvent * event ) ;

private:
  int click_x;
  int click_y;
};

#endif	/* QCLICKLABEL_H */

