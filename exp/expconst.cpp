#include "expconst.h"

ExpConst::ExpConst() { kind_ = kConst; }

ExpConst::ExpConst(int val) { val_ = val; }

ExpConst::~ExpConst() {}

int ExpConst::Evaluate(const QMap<QString, int>& env, QString& err) {
    return val_;
}
