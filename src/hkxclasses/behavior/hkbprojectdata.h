#ifndef HKBPROJECTDATA_H
#define HKBPROJECTDATA_H

#include "src/hkxclasses/hkxobject.h"

class BehaviorFile;

class hkbProjectData: public HkxObject
{
public:
    hkbProjectData(HkxFile *parent, long ref = 0);
    virtual ~hkbProjectData();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    bool evaulateDataValidity();
    static QString getClassname();
    bool write(HkxXMLWriter *writer);
private:
    hkbProjectData& operator=(const hkbProjectData&);
    hkbProjectData(const hkbProjectData &);
private:
    static QStringList EventMode;   //EVENT_MODE_IGNORE_FROM_GENERATOR=0, ????
    static uint refCount;
    static QString classname;
    hkQuadVariable worldUpWS;
    HkxObjectExpSharedPtr stringData;
    QString defaultEventMode;
};

#endif // HKBPROJECTDATA_H