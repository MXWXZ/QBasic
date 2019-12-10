#include "expcompound.h"
#include <QtMath>

ExpCompound::ExpCompound() { kind_ = kCompound; }

ExpCompound::ExpCompound(Op op, Expression* lexp, Expression* rexp) {
    op_ = op;
    lexp_ = lexp;
    rexp_ = rexp;
}

ExpCompound::~ExpCompound() {}

int ExpCompound::Evaluate(const QMap<QString, int>& env, QString& err) {
    switch (op_) {
        case kPlus:
            return lexp_->Evaluate(env, err) + rexp_->Evaluate(env, err);
        case kMinus:
            return lexp_->Evaluate(env, err) - rexp_->Evaluate(env, err);
        case kTimes:
            return lexp_->Evaluate(env, err) * rexp_->Evaluate(env, err);
        case kDivide:
            return lexp_->Evaluate(env, err) / rexp_->Evaluate(env, err);
        case kExp:
            return qPow(lexp_->Evaluate(env, err), rexp_->Evaluate(env, err));
        default:
            return 0;
    }
}
