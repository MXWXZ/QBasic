#ifndef EXPCOMPOUND_H
#define EXPCOMPOUND_H

#include "expression.h"

class ExpCompound : public Expression {
public:
    ExpCompound();
    ExpCompound(Op op, Expression* lexp, Expression* rexp);
    virtual ~ExpCompound() override;

    virtual int Evaluate(const QMap<QString, int>& env, QString& err) override;
};

#endif  // EXPCOMPOUND_H
