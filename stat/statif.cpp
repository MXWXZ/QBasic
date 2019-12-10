#include "statif.h"

StatIf::StatIf() { kind_ = kIf; }

StatIf::~StatIf() {
    delete exp1_;
    delete exp2_;
    exp1_ = nullptr;
    exp2_ = nullptr;
}

QString StatIf::Parse(Token& param) {
    QString tmp;
    exp1_ = Expression::New(param, tmp);
    if (!tmp.isEmpty())
        return tmp;
    op_ = param.NextToken(&tmp);
    if (op_ == Token::kNone)
        return QString("Missing op token");
    if (op_ != Token::kEQ && op_ != Token::kGT && op_ != Token::kLT)
        return QString("Op token \"%1\" invalid").arg(tmp);
    tmp.clear();  // eat op
    exp2_ = Expression::New(param, tmp);
    if (!tmp.isEmpty())
        return tmp;
    if (param.NextToken() != Token::kThen)
        return QString("Missing THEN in IF statement");
    if (param.NextToken(&tmp) != Token::kConst)
        return QString("Line number \"%1\" invalid").arg(tmp);
    n_ = tmp.toInt();
    return "";
}

bool StatIf::Run(QMap<QString, int>& env, Interpreter* itp) {
    QString err;
    int eval1, eval2;
    bool cond;
    eval1 = exp1_->Evaluate(env, err);
    if (!err.isEmpty())
        goto ERROR;
    eval2 = exp2_->Evaluate(env, err);
    if (!err.isEmpty())
        goto ERROR;
    switch (op_) {
        case Token::kEQ:
            cond = eval1 == eval2;
            break;
        case Token::kGT:
            cond = eval1 > eval2;
            break;
        case Token::kLT:
            cond = eval1 < eval2;
            break;
        default:
            assert(0);
    }
    if (cond)
        itp->Goto(n_);
    return true;
ERROR:
    itp->Print(err);
    return false;
}
