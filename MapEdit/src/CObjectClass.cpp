/* 
 * File:   CObjectClass.cpp
 * Author: Matej Pechac
 * 
 * Created on September 14, 2014, 10:15 PM
 */

#include "CObjectClass.h"

#include <QtCore/QXmlStreamWriter>
#include <QtCore/QFile>

CObjectClass::CObjectClass() {
}

CObjectClass::CObjectClass(const CObjectClass& orig) {
  classes = orig.classes;
}

CObjectClass::~CObjectClass() {
}

int CObjectClass::LoadFromXML(string filename) {
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

        if(xml.name() == "classes") {
            continue;
        }

        if(xml.name() == "class") {
          map <string, string> data;
          while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "class")) {
            if(xml.tokenType() == QXmlStreamReader::StartElement) {
              string key = xml.name().toAscii().constData();
              string value = xml.attributes().value("value").toAscii().constData();
              
              data[key] = value;
            }
            xml.readNext();
          }
          classes[stoi(data["id"])] = data["name"];
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

