#ifndef MANUALSELECTORGENERATORUI_H
#define MANUALSELECTORGENERATORUI_H

#include <QGroupBox>

#include "src/utility.h"

class HkxObject;
class BehaviorGraphView;
class GenericTableWidget;
class hkbManualSelectorGenerator;
class TableWidget;
class SpinBox;
class LineEdit;
class ComboBox;
class QGridLayout;
class hkbVariableBindingSet;

class ManualSelectorGeneratorUI: public QGroupBox
{
    Q_OBJECT
    friend class HkDataUI;
public:
    ManualSelectorGeneratorUI();
    virtual ~ManualSelectorGeneratorUI(){}
    void loadData(HkxObject *data);
signals:
    void generatorNameChanged(const QString & newName, int index);
    void viewVariables(int index);
    void viewGenerators(int index);
    void viewProperties(int index);
private slots:
    void setName();
    void setSelectedGeneratorIndex();
    void setCurrentGeneratorIndex();
    void setBindingVariable(int index, const QString & name);
    void setGenerator(int index, const QString & name);
    void viewSelectedChild(int row, int column);
    void swapGeneratorIndices(int index1, int index2);
private:
    void connectSignals();
    void disconnectSignals();
    void loadBinding(int row, int colunm, hkbVariableBindingSet *varBind, const QString &path);
    void variableRenamed(const QString & name, int index);
    void generatorRenamed(const QString & name, int index);
    void setBehaviorView(BehaviorGraphView *view);
    void selectTableToView(bool viewproperties, const QString & path);
    void setBinding(int index, int row, const QString & variableName, const QString & path, hkVariableType type, bool isProperty);
    void removeGenerator(int index);
    void setRowItems(int row, const QString & name, const QString & classname, const QString & bind, const QString & value, const QString &tip1, const QString &tip2);
    void connectToTables(GenericTableWidget *generators, GenericTableWidget *variables, GenericTableWidget *properties);
    void addGenerator();
    void loadDynamicTableRows();
private:
    enum Generator_Type {
        STATE_MACHINE = 0,
        MANUAL_SELECTOR_GENERATOR,
        BLENDER_GENERATOR,
        I_STATE_TAGGING_GENERATOR,
        BONE_SWITCH_GENERATOR,
        CYCLIC_BLEND_TRANSITION_GENERATOR,
        SYNCHRONIZED_CLIP_GENERATOR,
        MODIFIER_GENERATOR,
        OFFSET_ANIMATION_GENERATOR,
        POSE_MATCHING_GENERATOR,
        CLIP_GENERATOR,
        BEHAVIOR_REFERENCE_GENERATOR,
        GAMEBYRO_SEQUENCE_GENERATOR
    };
    static QStringList types;
    static QStringList headerLabels;
    BehaviorGraphView *behaviorView;
    hkbManualSelectorGenerator *bsData;
    QGridLayout *topLyt;
    TableWidget *table;
    LineEdit *name;
    SpinBox *selectedGeneratorIndex;
    SpinBox *currentGeneratorIndex;
    ComboBox *typeSelectorCB;
};

#endif // MANUALSELECTORGENERATORUI_H
