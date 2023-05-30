#ifndef LAMPLIGHTMODULE_H
#define LAMPLIGHTMODULE_H

#include "interface/namespace.h"
#include "interface/moduleinterface.h"
#include "dtkcore_global.h"

#include <QObject>

DCORE_BEGIN_NAMESPACE
class DConfig;
DCORE_END_NAMESPACE

class LightModel;
class QThread;

class LampLightModule : public QObject
    , public DCC_NAMESPACE::ModuleInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID ModuleInterface_iid FILE "lamplight.json")
    Q_INTERFACES(DCC_NAMESPACE::ModuleInterface)

public:
    LampLightModule();
    ~LampLightModule() Q_DECL_OVERRIDE;

    virtual void initialize() override;
    virtual const QString name() const override;
    virtual const QString displayName() const override;
    virtual QIcon icon() const override;
    virtual QString translationPath() const override;
    virtual QString path() const override;
    virtual QString follow() const override;
    virtual void deactive() override;
    virtual void addChildPageTrans() const override;
    virtual bool enabled() const override;

protected:
    void initSearchData() override;

public Q_SLOTS:
    virtual void active() override;

private:
    DTK_CORE_NAMESPACE::DConfig *m_dconfig;
    LightModel *m_model;
    QThread *m_workThread;
    bool m_isModuleAvaliable;
};

#endif // LAMPLIGHTMODULE_H
