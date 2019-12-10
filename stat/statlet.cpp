#include "statlet.h"

StatLet::StatLet() { kind_ = kLet; }

StatLet::~StatLet() {
    delete exp_;
    exp_ = nullptr;
}

QString StatLet::Parse(Token& param) {
    QString err;
    if (param.NextToken(&id_) != Token::kId)
        err = QString("Id \"%1\" invalid").arg(id_);
    else if (param.NextToken() != Token::kEQ)
        err = QString("\"=\" is missing");
    else
        exp_ = Expression::New(param, err);
    return err;
}

bool StatLet::Run(QMap<QString, int>& env, Interpreter* itp) {
    QString err;
    auto eval = exp_->Evaluate(env, err);
    if (!err.isEmpty()) {
        itp->Print(err);
        return false;
    }
    env[id_] = eval;
    return true;
}
