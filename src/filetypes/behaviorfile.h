#ifndef BEHAVIORFILE_H
#define BEHAVIORFILE_H

#include "src/filetypes/hkxfile.h"

class hkbBehaviorGraph;
class CharacterFile;

class BehaviorFile: public HkxFile
{
    friend class hkbBehaviorGraphData;
    friend class BehaviorGraphView;
    friend class hkbBehaviorGraph;
    friend class MainWindow;
public:
    BehaviorFile(MainWindow *window, CharacterFile *characterData, const QString & name);
    virtual ~BehaviorFile();
    HkxObjectExpSharedPtr * findHkxObject(long ref);
    HkxObjectExpSharedPtr * findGenerator(long ref);
    HkxObjectExpSharedPtr * findGeneratorChild(long ref);
    HkxObjectExpSharedPtr * findModifier(long ref);
    HkxObjectExpSharedPtr * findBehaviorGraph(long ref);
    QVector<int> removeGeneratorData();
    QVector<int> removeModifierData();
    QVector<int> removeOtherData();
    int getIndexOfGenerator(const HkxObjectExpSharedPtr & obj) const;
    bool setGeneratorData(HkxObjectExpSharedPtr & ptrToSet, int index);
    hkbGenerator * getGeneratorDataAt(int index);
    int getIndexOfModifier(const HkxObjectExpSharedPtr & obj) const;
    bool setModifierData(HkxObjectExpSharedPtr & ptrToSet, int index);
    hkbModifier * getModifierDataAt(int index);
    QStringList getVariableNames() const;
    QStringList getEventNames() const;
    QStringList getGeneratorNamesAndTypeNames() const;
    QStringList getModifierNamesAndTypeNames() const;
    HkxObject * getBehaviorGraphData() const;
    hkbBehaviorGraph * getBehaviorGraph() const;
    HkxObject * getRootStateMachine() const;
    void removeBindings(int varIndex);
    hkVariableType getVariableTypeAt(int index) const;
    bool addObjectToFile(HkxObject *obj, long ref = -1);
    //For compatability for now... will be removed later...
    QStringList getGeneratorNames(){return QStringList();}
    QStringList getModifierNames(){return QStringList();}
    //
    void write();
    CustomTreeGraphicsViewIcon * getRootIcon() const;
    QStringList getAllReferencedBehaviorFilePaths() const;
    QStringList getRagdollBoneNames() const;
    QStringList getRigBoneNames() const;
protected:
    bool parse();
    bool link();
private:
    CharacterFile *character;
    HkxObjectExpSharedPtr behaviorGraph;
    HkxObjectExpSharedPtr stringData;
    HkxObjectExpSharedPtr variableValues;
    HkxObjectExpSharedPtr graphData;
    QList <HkxObjectExpSharedPtr> generators;
    QList <HkxObjectExpSharedPtr> generatorChildren;
    QList <HkxObjectExpSharedPtr> modifiers;
    QList <HkxObjectExpSharedPtr> otherTypes;
    QStringList referencedBehaviors;
    long largestRef;
};

#endif // BEHAVIORFILE_H