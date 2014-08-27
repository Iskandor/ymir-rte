/* 
 * File:   CUnitModule.h
 * Author: Matej Pechac
 *
 * Created on February 23, 2013, 4:48 PM
 */

#ifndef CUNITMODULE_H
#define	CUNITMODULE_H

#include "CXmlSerializable.h"

#include <vector>
#include <string>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QFile>
#include <assert.h>

using namespace std;

template<class T>
class CModule {
public:
  CModule() {
    next_id = 0;
  };
  
  CModule(string name) {
    next_id = 0;
    this->name = name;
  };
  
  CModule(const CModule& orig) {
    this->next_id = orig.next_id;
    this->name = orig.name;
    this->buffer = orig.buffer;    
  };
  
  virtual ~CModule() {
  };
  
  void   AddUnit    (T unit) {
    unit.SetID(next_id);
    next_id++;
    buffer.push_back(unit);
  };
  
  void   EditUnit   (int index, T unit) {
    buffer[index] = unit;
  };
  
  void   RemoveUnit (int index) {
    typename vector<T>::iterator it = buffer.begin();

    for(int i = 0; i < index; i++) {
      ++it;
    }

    buffer.erase(it);  
  };
  
  T GetUnit    (unsigned int index) {
    if (index > buffer.size()) {
      assert(0);
    }
    return buffer[index];    
  };
  
  T* GetUnitPtr (unsigned int id) {
    for(int i = 0; i < buffer.size(); i++) {
      if (buffer[i].GetID() == id) {
        return &buffer[i];
      }
    }
    return NULL;    
  };
  
  int GetSize    () {
    return buffer.size();
  };
  
  int SaveToXML (string root, string elem) {
    QFile file(QString::fromStdString(name+".xml"));

    if (!file.open(QIODevice::WriteOnly)) {
      return -1;
    }	
    else {
      QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();

      xmlWriter->setDevice(&file);
      xmlWriter->writeStartDocument();
      xmlWriter->writeStartElement(root.c_str());

      for(unsigned int i = 0; i < buffer.size(); i++) {
        xmlWriter->writeStartElement(elem.c_str());

        map<string, string> u_map = ((T)buffer[i]).exportMap();

        for(map<string, string>::iterator u_map_it = u_map.begin(); u_map_it != u_map.end(); u_map_it++) {
          xmlWriter->writeStartElement(u_map_it->first.c_str());
          xmlWriter->writeAttribute("value", u_map_it->second.c_str());
          xmlWriter->writeEndElement();
        }
        xmlWriter->writeEndElement();
      }

      xmlWriter->writeEndElement();
      xmlWriter->writeEndDocument();

      delete xmlWriter;
    }

    return 0;    
  };
  
  int  LoadFromXML  (string filename, string root, string elem) {
    T*  unit;
    QFile   file(QString::fromStdString(filename+".xml"));

    name = filename;
    next_id = 0;

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
          if(xml.name().toString().toStdString().compare(root) == 0) {
              continue;
          }

          if(xml.name().toString().toStdString().compare(elem) == 0) {
            map <string, string> data;
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name().toString().toStdString().compare(elem) == 0)) {
              if(xml.tokenType() == QXmlStreamReader::StartElement && xml.name().toString().toStdString().compare(elem) != 0) {
                string key = xml.name().toAscii().constData();
                string value = xml.attributes().value("value").toAscii().constData();

                data[key] = value;
              }
              xml.readNext();
            }            
            unit = new T(data);
            buffer.push_back(*unit);
            if (next_id <= unit->GetID()) {
              next_id = unit->GetID() + 1;
            }
          }
        }
      }
      if(xml.hasError()) {
          //QMessageBox::critical(this, "CUnitModule::LoadFromXML", xml.errorString(), QMessageBox::Ok);
          return -1;
      }

      xml.clear();
    }  
    return 0;    
  };
  
private:
  vector<T>       buffer;
  string          name;
  int             next_id;
};

#endif	/* CUNITMODULE_H */

