#include "lamplightconfigwidget.h"
#include "widgets/switchwidget.h"
#include "widgets/settingsgroup.h"

#include <QVBoxLayout>

using namespace dcc::widgets;

LampLightConfigWidget::LampLightConfigWidget(QWidget *parent, LightModel *model)
    : QWidget(parent)
    , m_switch(nullptr)
    , m_model(model)
{
    initUI();
    initConnetion();
}

void LampLightConfigWidget::onStatusChanged(bool status)
{
    m_switch->setChecked(status);
}

void LampLightConfigWidget::initUI()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(10, 10, 10, 10);

    m_switch = new SwitchWidget(this);
    m_switch->setTitle("启动灯带");
    m_switch->setChecked(false);

    SettingsGroup *group = new SettingsGroup;
    group->appendItem(m_switch);

    layout->addWidget(group, 0, Qt::AlignTop);
    layout->addStretch(10);

    setLayout(layout);
}

void LampLightConfigWidget::initConnetion()
{
    connect(m_model, &LightModel::notifyCurrentState, this, &LampLightConfigWidget::onStatusChanged);
    connect(this, &LampLightConfigWidget::requestSetStatus, m_model, &LightModel::setDeviceStatus);
    connect(m_switch, &SwitchWidget::clicked, this, [this] {
        Q_EMIT requestSetStatus(m_switch->checked());
    });
    connect(this, &LampLightConfigWidget::requestGetStatus, m_model, &LightModel::getDeviceState);
}
