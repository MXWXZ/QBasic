#ifndef EXPCONST_H
#define EXPCONST_H

#include "expression.h"

class ExpConst : public Expression {
public:
    ExpConst();
    ExpConst(int val);
    virtual ~ExpConst() override;

    virtual int Evaluate(const QMap<QString, int>& env, QString& err) override;
};

#endif  // EXPCONST_H
