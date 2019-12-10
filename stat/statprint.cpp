#include "statprint.h"

StatPrint::StatPrint() { kind_ = kPrint; }

StatPrint::~StatPrint() {}

QString StatPrint::Parse(Token& param) {
    QString err;
    exp_ = Expression::New(param, err);
    return err;
}

bool StatPrint::Run(QMap<QString, int>& env, Interpreter* itp) {
    QString err;
    auto eval = exp_->Evaluate(env, err);
    if (!err.isEmpty()) {
        itp->Print(err);
        return false;
    }
    QString str;
    str.setNum(eval);
    itp->Print(str, false);
    return true;
}
