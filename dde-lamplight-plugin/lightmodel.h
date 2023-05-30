#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include <QObject>
#include <QMap>

class QProcess;

class LightModel : public QObject
{
    Q_OBJECT

    enum OpType {
        GET_AVALIABLE,
        GET_STATUS,
        SET_STATUS
    };

public:
    LightModel(QObject *parent = nullptr);
    bool isDeviceAvaliable();

public Q_SLOTS:
    void setDeviceStatus(bool);
    bool getDeviceState();

private:
    QString processCmd(OpType, const QString &param = "");

Q_SIGNALS:
    void notifyCurrentState(bool);

private:
    QProcess *m_process;
    bool m_currentState;
    QMap<OpType, QString> m_opMap;
};

#endif // LIGHTMODEL_H
