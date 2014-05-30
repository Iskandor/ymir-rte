/* 
 * File:   CRace.cpp
 * Author: Matej Pechac
 * 
 * Created on October 28, 2013, 1:52 PM
 */

#include "CRace.h"

#include <QtCore/QXmlStreamWriter>
#include <QtCore/QFile>

CRace::CRace(string filename) {
  if (LoadFromXML(filename) != 0) {
   //zalogujem chybu 
  } 
}

CRace::CRace(const CRace& orig) {
  names = orig.names;
}

CRace::~CRace() {
}

vector<string> CRace::getNames() {
  return names;
}

int CRace::getSize() {
  return names.size();
}

int CRace::findName(string name) {
  int i;
  
  for(i = 0; i < names.size(); i++) {
    if (name.compare(names[i]) == 0) {
      return i;
    }
  }
  
  return -1;
}

int CRace::LoadFromXML(string filename) {
  QFile   file(QString::fromStdString(filename+".xml"));
  
	if (!file.open(QIODevice::ReadOnly)) {
    return -1;
	}	
	else {
    QXmlStreamReader xml;
    xml.setDevice(&file);

    while(!xml.atEnd() && !xml.hasError()) {

      QXmlStreamReader::TokenType token = xml.readNext();

      if(token == QXmlStreamReader::StartDocument) {
        continue;
      }

      if(token == QXmlStreamReader::StartElement) {

        if(xml.name() == "races") {
            continue;
        }

        if(xml.name() == "race") {
          while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "race")) {
            if(xml.tokenType() == QXmlStreamReader::StartElement) {
              string key = xml.name().toAscii().constData();
              string value = xml.attributes().value("value").toAscii().constData();
              
              if (key == "name") {
                names.push_back(value);
              }
            }
            xml.readNext();
          }
        }
      }
    }
    if(xml.hasError()) {
        return -1;
    }

    xml.clear();
  }
  
  return 0;
}