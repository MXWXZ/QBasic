#include "expid.h"

ExpId::ExpId() { kind_ = kId; }

ExpId::ExpId(QString id) { id_ = id; }

ExpId::~ExpId() {}

int ExpId::Evaluate(const QMap<QString, int>& env, QString& err) {
    if (!env.contains(id_)) {
        err = QString("Id \"%1\" is not declared").arg(id_);
        return 0;
    }
    return env[id_];
}
