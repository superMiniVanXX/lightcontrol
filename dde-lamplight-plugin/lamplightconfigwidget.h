#ifndef LAMPLIGHTCONFIGWIDGET_H
#define LAMPLIGHTCONFIGWIDGET_H

#include "lightmodel.h"

#include <QWidget>

namespace dcc {
namespace widgets {
class SwitchWidget;
}
} // namespace dcc

class LampLightConfigWidget : public QWidget
{
    Q_OBJECT
public:
    LampLightConfigWidget(QWidget *parent = nullptr, LightModel *model = nullptr);

Q_SIGNALS:
    void requestSetStatus(bool);
    void requestGetStatus();

public Q_SLOTS:
    void onStatusChanged(bool);

private:
    void initUI();
    void initConnetion();

private:
    dcc::widgets::SwitchWidget *m_switch;
    LightModel *m_model;
};

#endif // LAMPLIGHTCONFIGWIDGET_H
