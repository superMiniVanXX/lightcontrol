#include "lightmodel.h"

#include <QProcess>
#include <QDebug>

const QString ILSTCmd = "/usr/bin/ilst";

LightModel::LightModel(QObject *parent)
    : QObject(parent)
    , m_process(nullptr)
{
    m_opMap.insert(OpType::GET_AVALIABLE, "-p");
    m_opMap.insert(OpType::GET_STATUS, "-r");
    m_opMap.insert(OpType::SET_STATUS, "-l %1");
}

void LightModel::setDeviceStatus(bool status)
{
    QString inputParam = status ? "true" : "false";
    processCmd(SET_STATUS, inputParam);

    // 不检查返回，必须通过二次查询通知外部发生状态更新
    getDeviceState();
}

bool LightModel::getDeviceState()
{
    bool isEnabled = false;
    QString response = processCmd(GET_STATUS);

    response = response.trimmed().toLower();
    if (!response.isEmpty()) {
        isEnabled = response == "true";
    }

    Q_EMIT notifyCurrentState(isEnabled);

    return isEnabled;
}

QString LightModel::processCmd(LightModel::OpType cmd, const QString &param)
{
    Q_ASSERT(cmd >= GET_AVALIABLE);
    Q_ASSERT(cmd <= SET_STATUS);

    QStringList params;
    params << m_opMap[cmd];

    if (SET_STATUS == cmd) {
        params << param;
    }

    QProcess process;
    process.start(ILSTCmd, params);
    if (!process.waitForFinished()) {
        qDebug() << Q_FUNC_INFO << "failed to process" << params;
        return "";
    }

    return process.readAll();
}

bool LightModel::isDeviceAvaliable()
{
    bool isAvaliable = false;

    QString response = processCmd(GET_AVALIABLE);
    response = response.trimmed().toLower();
    isAvaliable = response == "true";

    // todo :
    // return isAvaliable;
    return true;
}
