#ifndef BSOFFSETANIMATIONGENERATOR_H
#define BSOFFSETANIMATIONGENERATOR_H

#include "hkbgenerator.h"

class BSOffsetAnimationGenerator: public hkbGenerator
{
    friend class BehaviorGraphView;
public:
    BSOffsetAnimationGenerator(BehaviorFile *parent, long ref = 0);
    virtual ~BSOffsetAnimationGenerator();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    QString getName() const;
    bool evaulateDataValidity();
    static QString getClassname();
    int getIndexToInsertIcon() const;
    bool write(HkxXMLWriter *writer);
private:
    BSOffsetAnimationGenerator& operator=(const BSOffsetAnimationGenerator&);
    BSOffsetAnimationGenerator(const BSOffsetAnimationGenerator &);
private:
    static uint refCount;
    static QString classname;
    ulong userData;
    QString name;
    HkxObjectExpSharedPtr pDefaultGenerator;
    HkxObjectExpSharedPtr pOffsetClipGenerator;
    qreal fOffsetVariable;
    qreal fOffsetRangeStart;
    qreal fOffsetRangeEnd;
};

#endif // BSOFFSETANIMATIONGENERATOR_H
