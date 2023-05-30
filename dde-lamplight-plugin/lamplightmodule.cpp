#include "lamplightmodule.h"
#include "lamplightconfigwidget.h"
#include "lightmodel.h"

#include <QThread>

using namespace dccV20;
DCORE_USE_NAMESPACE

LampLightModule::LampLightModule()
    : QObject()
    , ModuleInterface()
    , m_dconfig(nullptr)
    , m_model(nullptr)
    , m_workThread(nullptr)
    , m_isModuleAvaliable(false)
{
    m_model = new LightModel(this);

    // 如果模块不存在，插件设置为不可用
    m_isModuleAvaliable = m_model->isDeviceAvaliable();

    m_workThread = new QThread(this);
    connect(m_model, &QObject::destroyed, this, [this] {
        m_model = nullptr;
    });
    m_model->moveToThread(m_workThread);
}

LampLightModule::~LampLightModule()
{
}

void LampLightModule::initialize()
{
}

void LampLightModule::active()
{
    if (m_isModuleAvaliable) {
        auto showWid = new LampLightConfigWidget(nullptr, m_model);
        showWid->setVisible(true);
        m_frameProxy->pushWidget(this, showWid);
        Q_EMIT showWid->requestGetStatus();
    }
}

const QString LampLightModule::displayName() const
{
    return tr("Lights");
}

QIcon LampLightModule::icon() const
{
    return QIcon::fromTheme("dcc_power_light");
    // return QIcon(":/icons/normal/dcc_power_light_32px.svg");
}

QString LampLightModule::translationPath() const
{
    return "";
}

QString LampLightModule::path() const
{
    return POWER;
}

QString LampLightModule::follow() const
{
    // 通用 - 使用电源 - 使用电池 - 灯光
    return "灯光设置";
}

void LampLightModule::deactive()
{
}

const QString LampLightModule::name() const
{
    return "灯光设置";
}

void LampLightModule::addChildPageTrans() const
{
}

void LampLightModule::initSearchData()
{
}

bool LampLightModule::enabled() const
{
    return m_isModuleAvaliable;
}
