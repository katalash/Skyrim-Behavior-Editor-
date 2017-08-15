#include "gethandleonbonemodifierui.h"

#include "src/hkxclasses/hkxobject.h"
#include "src/hkxclasses/behavior/modifiers/hkbgethandleonbonemodifier.h"
#include "src/hkxclasses/behavior/hkbvariablebindingset.h"
#include "src/filetypes/behaviorfile.h"
#include "src/ui/genericdatawidgets.h"

#include <QGridLayout>
#include <QHeaderView>

#define BASE_NUMBER_OF_ROWS 6

#define NAME_ROW 0
#define ENABLE_ROW 1
#define HANDLE_OUT_ROW 2
#define LOCAL_FRAME_NAME_ROW 3
#define RAGDOLL_BONE_INDEX_ROW 4
#define ANIMATION_BONE_INDEX_ROW 5

#define NAME_COLUMN 0
#define TYPE_COLUMN 1
#define BINDING_COLUMN 2
#define VALUE_COLUMN 3

#define BINDING_ITEM_LABEL QString("Use Property     ")

QStringList GetHandleOnBoneModifierUI::headerLabels = {
    "Name",
    "Type",
    "Bound Variable",
    "Value"
};

GetHandleOnBoneModifierUI::GetHandleOnBoneModifierUI()
    : bsData(NULL),
      topLyt(new QGridLayout),
      table(new TableWidget(QColor(Qt::white))),
      name(new LineEdit),
      enable(new CheckBox),
      localFrameName(new ComboBox),
      ragdollBoneIndex(new ComboBox),
      animationBoneIndex(new ComboBox)
{
    setTitle("hkbGetHandleOnBoneModifier");
    table->setRowCount(BASE_NUMBER_OF_ROWS);
    table->setColumnCount(headerLabels.size());
    table->setHorizontalHeaderLabels(headerLabels);
    table->setItem(NAME_ROW, NAME_COLUMN, new TableWidgetItem("name"));
    table->setItem(NAME_ROW, TYPE_COLUMN, new TableWidgetItem("hkStringPtr", Qt::AlignCenter));
    table->setItem(NAME_ROW, BINDING_COLUMN, new TableWidgetItem("N/A", Qt::AlignCenter));
    table->setCellWidget(NAME_ROW, VALUE_COLUMN, name);
    table->setItem(ENABLE_ROW, NAME_COLUMN, new TableWidgetItem("enable"));
    table->setItem(ENABLE_ROW, TYPE_COLUMN, new TableWidgetItem("hkBool", Qt::AlignCenter));
    table->setItem(ENABLE_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(ENABLE_ROW, VALUE_COLUMN, enable);
    table->setItem(HANDLE_OUT_ROW, NAME_COLUMN, new TableWidgetItem("handleOut"));
    table->setItem(HANDLE_OUT_ROW, TYPE_COLUMN, new TableWidgetItem("hkHandle", Qt::AlignCenter));
    table->setItem(HANDLE_OUT_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setItem(HANDLE_OUT_ROW, VALUE_COLUMN, new TableWidgetItem("N/A", Qt::AlignCenter));
    table->setItem(LOCAL_FRAME_NAME_ROW, NAME_COLUMN, new TableWidgetItem("localFrameName"));
    table->setItem(LOCAL_FRAME_NAME_ROW, TYPE_COLUMN, new TableWidgetItem("hkStringPtr", Qt::AlignCenter));
    table->setItem(LOCAL_FRAME_NAME_ROW, BINDING_COLUMN, new TableWidgetItem("N/A", Qt::AlignCenter));
    table->setCellWidget(LOCAL_FRAME_NAME_ROW, VALUE_COLUMN, localFrameName);
    table->setItem(RAGDOLL_BONE_INDEX_ROW, NAME_COLUMN, new TableWidgetItem("ragdollBoneIndex"));
    table->setItem(RAGDOLL_BONE_INDEX_ROW, TYPE_COLUMN, new TableWidgetItem("hkInt32", Qt::AlignCenter));
    table->setItem(RAGDOLL_BONE_INDEX_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(RAGDOLL_BONE_INDEX_ROW, VALUE_COLUMN, ragdollBoneIndex);
    table->setItem(ANIMATION_BONE_INDEX_ROW, NAME_COLUMN, new TableWidgetItem("animationBoneIndex"));
    table->setItem(ANIMATION_BONE_INDEX_ROW, TYPE_COLUMN, new TableWidgetItem("hkInt32", Qt::AlignCenter));
    table->setItem(ANIMATION_BONE_INDEX_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(ANIMATION_BONE_INDEX_ROW, VALUE_COLUMN, animationBoneIndex);
    topLyt->addWidget(table, 0, 0, 8, 3);
    setLayout(topLyt);
}

void GetHandleOnBoneModifierUI::connectSignals(){
    connect(name, SIGNAL(editingFinished()), this, SLOT(setName()), Qt::UniqueConnection);
    connect(enable, SIGNAL(released()), this, SLOT(setEnable()), Qt::UniqueConnection);
    connect(localFrameName, SIGNAL(currentTextChanged(QString)), this, SLOT(setLocalFrameName(QString)), Qt::UniqueConnection);
    connect(ragdollBoneIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(setRagdollBoneIndex(int)), Qt::UniqueConnection);
    connect(animationBoneIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(setAnimationBoneIndex(int)), Qt::UniqueConnection);
    connect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(viewSelected(int,int)), Qt::UniqueConnection);
}

void GetHandleOnBoneModifierUI::disconnectSignals(){
    disconnect(name, SIGNAL(editingFinished()), this, SLOT(setName()));
    disconnect(enable, SIGNAL(released()), this, SLOT(setEnable()));
    disconnect(localFrameName, SIGNAL(currentTextChanged(QString)), this, SLOT(setLocalFrameName(QString)));
    disconnect(ragdollBoneIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(setRagdollBoneIndex(int)));
    disconnect(animationBoneIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(setAnimationBoneIndex(int)));
    disconnect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(viewSelected(int,int)));
}

void GetHandleOnBoneModifierUI::connectToTables(GenericTableWidget *variables, GenericTableWidget *properties){
    if (variables && properties){
        disconnect(variables, SIGNAL(elementSelected(int,QString)), 0, 0);
        disconnect(properties, SIGNAL(elementSelected(int,QString)), 0, 0);
        connect(variables, SIGNAL(elementSelected(int,QString)), this, SLOT(setBindingVariable(int,QString)), Qt::UniqueConnection);
        connect(properties, SIGNAL(elementSelected(int,QString)), this, SLOT(setBindingVariable(int,QString)), Qt::UniqueConnection);
        connect(this, SIGNAL(viewVariables(int)), variables, SLOT(showTable(int)), Qt::UniqueConnection);
        connect(this, SIGNAL(viewProperties(int)), properties, SLOT(showTable(int)), Qt::UniqueConnection);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::connectToTables(): One or more arguments are NULL!!"))
    }
}

void GetHandleOnBoneModifierUI::loadData(HkxObject *data){
    disconnectSignals();
    if (data){
        if (data->getSignature() == HKB_GET_HANDLE_ON_BONE_MODIFIER){
            int index = -1;
            QStringList localFrames;
            localFrames.append("None");
            QStringList boneNames;
            boneNames.append("None");
            hkbVariableBindingSet *varBind = NULL;
            bsData = static_cast<hkbGetHandleOnBoneModifier *>(data);
            name->setText(bsData->name);
            enable->setChecked(bsData->enable);
            if (localFrameName->count() == 0){
                localFrames = localFrames + static_cast<BehaviorFile *>(bsData->getParentFile())->getLocalFrameNames();
                localFrameName->insertItems(0, localFrames);
            }
            index = localFrameName->findText(bsData->localFrameName);
            if (index < 0 || index >= localFrameName->count()){
                CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::loadData(): The local frame name was not loaded correctly!!!"));
            }
            localFrameName->setCurrentIndex(index);
            if (ragdollBoneIndex->count() == 0){
                boneNames = boneNames + static_cast<BehaviorFile *>(bsData->getParentFile())->getRagdollBoneNames();
                ragdollBoneIndex->insertItems(0, boneNames);
            }
            ragdollBoneIndex->setCurrentIndex(bsData->ragdollBoneIndex + 1);
            boneNames.clear();
            boneNames.append("None");
            if (animationBoneIndex->count() == 0){
                boneNames = boneNames + static_cast<BehaviorFile *>(bsData->getParentFile())->getRigBoneNames();
                animationBoneIndex->insertItems(0, boneNames);
            }
            animationBoneIndex->setCurrentIndex(bsData->animationBoneIndex + 1);
            varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
            if (varBind){
                loadBinding(ENABLE_ROW, BINDING_COLUMN, varBind, "enable");
                loadBinding(HANDLE_OUT_ROW, BINDING_COLUMN, varBind, "handleOut");
                loadBinding(RAGDOLL_BONE_INDEX_ROW, BINDING_COLUMN, varBind, "ragdollBoneIndex");
                loadBinding(ANIMATION_BONE_INDEX_ROW, BINDING_COLUMN, varBind, "animationBoneIndex");
            }else{
                table->item(ENABLE_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(HANDLE_OUT_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(RAGDOLL_BONE_INDEX_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(ANIMATION_BONE_INDEX_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
            }
        }else{
            CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::loadData(): The data is an incorrect type!!"));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::loadData(): The data is NULL!!"));
    }
    connectSignals();
}

void GetHandleOnBoneModifierUI::setName(){
    if (bsData){
        if (bsData->name != name->text()){
            bsData->name = name->text();
            static_cast<DataIconManager*>((bsData))->updateIconNames();
            bsData->getParentFile()->toggleChanged(true);
            emit modifierNameChanged(name->text(), static_cast<BehaviorFile *>(bsData->getParentFile())->getIndexOfModifier(bsData));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setName(): The data is NULL!!"));
    }
}

void GetHandleOnBoneModifierUI::setEnable(){
    if (bsData){
        bsData->enable = enable->isChecked();
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setEnable(): The data is NULL!!"));
    }
}

void GetHandleOnBoneModifierUI::setLocalFrameName(const QString & name){
    if (bsData){
        bsData->localFrameName = name;
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setLocalFrameName(): The data is NULL!!"));
    }
}

void GetHandleOnBoneModifierUI::setRagdollBoneIndex(int index){
    if (bsData){
        bsData->ragdollBoneIndex = index - 1;
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setRagdollBoneIndex(): The data is NULL!!"));
    }
}

void GetHandleOnBoneModifierUI::setAnimationBoneIndex(int index){
    if (bsData){
        bsData->animationBoneIndex = index - 1;
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setAnimationBoneIndex(): The data is NULL!!"));
    }
}

void GetHandleOnBoneModifierUI::viewSelected(int row, int column){
    if (bsData){
        bool isProperty = false;
        if (column == BINDING_COLUMN){
            switch (row){
            case ENABLE_ROW:
                if (table->item(ENABLE_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "enable");
                break;
            case HANDLE_OUT_ROW:
                if (table->item(HANDLE_OUT_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "handleOut");
                break;
            case RAGDOLL_BONE_INDEX_ROW:
                if (table->item(RAGDOLL_BONE_INDEX_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "ragdollBoneIndex");
                break;
            case ANIMATION_BONE_INDEX_ROW:
                if (table->item(ANIMATION_BONE_INDEX_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "animationBoneIndex");
                break;
            default:
                return;
            }
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::viewSelected(): The 'bsData' pointer is NULL!!"))
    }
}

void GetHandleOnBoneModifierUI::selectTableToView(bool viewisProperty, const QString & path){
    if (bsData){
        if (viewisProperty){
            if (bsData->variableBindingSet.data()){
                emit viewProperties(static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data())->getVariableIndexOfBinding(path) + 1);
            }else{
                emit viewProperties(0);
            }
        }else{
            if (bsData->variableBindingSet.data()){
                emit viewVariables(static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data())->getVariableIndexOfBinding(path) + 1);
            }else{
                emit viewVariables(0);
            }
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::selectTableToView(): The data is NULL!!"));
    }
}

void GetHandleOnBoneModifierUI::variableRenamed(const QString & name, int index){
    if (bsData){
        index--;
        hkbVariableBindingSet *bind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
        if (bind){
            int bindIndex = bind->getVariableIndexOfBinding("enable");
            if (bindIndex == index){
                table->item(ENABLE_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("handleOut");
            if (bindIndex == index){
                table->item(HANDLE_OUT_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("ragdollBoneIndex");
            if (bindIndex == index){
                table->item(RAGDOLL_BONE_INDEX_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("animationBoneIndex");
            if (bindIndex == index){
                table->item(ANIMATION_BONE_INDEX_ROW, BINDING_COLUMN)->setText(name);
            }
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::variableRenamed(): The 'bsData' pointer is NULL!!"))
    }
}

bool GetHandleOnBoneModifierUI::setBinding(int index, int row, const QString &variableName, const QString &path, hkVariableType type, bool isProperty){
    hkbVariableBindingSet *varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
    if (bsData){
        if (index == 0){
            varBind->removeBinding(path);
            table->item(row, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
        }else if ((!isProperty && static_cast<BehaviorFile *>(bsData->getParentFile())->getVariableTypeAt(index - 1) == type) ||
                  (isProperty && static_cast<BehaviorFile *>(bsData->getParentFile())->getCharacterPropertyTypeAt(index - 1) == type)){
            if (!varBind){
                varBind = new hkbVariableBindingSet(bsData->getParentFile());
                bsData->variableBindingSet = HkxSharedPtr(varBind);
            }
            if (isProperty){
                if (!varBind->addBinding(path, variableName, index - 1, hkbVariableBindingSet::hkBinding::BINDING_TYPE_CHARACTER_PROPERTY)){
                    CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setBinding(): The attempt to add a binding to this object's hkbVariableBindingSet failed!!"));
                }
            }else{
                if (!varBind->addBinding(path, variableName, index - 1, hkbVariableBindingSet::hkBinding::BINDING_TYPE_VARIABLE)){
                    CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setBinding(): The attempt to add a binding to this object's hkbVariableBindingSet failed!!"));
                }
            }
            table->item(row, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+variableName);
            bsData->getParentFile()->toggleChanged(true);
        }else{
            WARNING_MESSAGE(QString("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\n\nYou are attempting to bind a variable of an invalid type for this data field!!!"));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setBinding(): The data is NULL!!"));
    }
    return true;
}

void GetHandleOnBoneModifierUI::setBindingVariable(int index, const QString &name){
    if (bsData){
        bool isProperty = false;
        int row = table->currentRow();
        switch (row){
        case ENABLE_ROW:
            if (table->item(ENABLE_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "enable", VARIABLE_TYPE_BOOL, isProperty);
            break;
        case HANDLE_OUT_ROW:
            if (table->item(HANDLE_OUT_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "handleOut", VARIABLE_TYPE_POINTER, isProperty);
            break;
        case RAGDOLL_BONE_INDEX_ROW:
            if (table->item(RAGDOLL_BONE_INDEX_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "ragdollBoneIndex", VARIABLE_TYPE_INT32, isProperty);
            break;
        case ANIMATION_BONE_INDEX_ROW:
            if (table->item(ANIMATION_BONE_INDEX_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "animationBoneIndex", VARIABLE_TYPE_INT32, isProperty);
            break;
        default:
            return;
        }
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::setBindingVariable(): The data is NULL!!"));
    }
}

void GetHandleOnBoneModifierUI::loadBinding(int row, int colunm, hkbVariableBindingSet *varBind, const QString &path){
    if (bsData){
        if (varBind){
            int index = varBind->getVariableIndexOfBinding(path);
            QString varName;
            if (index != -1){
                if (varBind->getBindingType(path) == hkbVariableBindingSet::hkBinding::BINDING_TYPE_CHARACTER_PROPERTY){
                    varName = static_cast<BehaviorFile *>(bsData->getParentFile())->getCharacterPropertyNameAt(index, true);
                    table->item(row, colunm)->setCheckState(Qt::Checked);
                }else{
                    varName = static_cast<BehaviorFile *>(bsData->getParentFile())->getVariableNameAt(index);
                }
            }
            if (varName == ""){
                varName = "NONE";
            }
            table->item(row, colunm)->setText(BINDING_ITEM_LABEL+varName);
        }else{
            CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::loadBinding(): The variable binding set is NULL!!"));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("GetHandleOnBoneModifierUI::loadBinding(): The data is NULL!!"));
    }
}