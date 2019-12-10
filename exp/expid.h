#ifndef EXPID_H
#define EXPID_H

#include <QMap>
#include "expression.h"

class ExpId : public Expression {
public:
    ExpId();
    ExpId(QString id);
    virtual ~ExpId() override;

    virtual int Evaluate(const QMap<QString, int>& env, QString& err) override;
};

#endif  // EXPID_H
