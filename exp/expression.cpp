#include "expression.h"
#include "expconst.h"
#include "expid.h"
#include "expcompound.h"
#include <QStack>

int Expression::oprank_[] = {0, 0, 0, 1, 1, 2, 2, 3, 4};

Expression::Expression() {}

Expression::~Expression() {}

Expression* Expression::New(Token& exp, QString& err) {
    QString token;
    QStack<Op> ops;
    QStack<Expression*> oprs;
    bool error = false;
    bool unary = true;

    if (exp.IsEmpty()) {
        err = "Empty expression";
        return nullptr;
    }

    // first token must be - or const or id
    auto first_token = CheckToken(exp.NextToken(&token, false, true));
    if (first_token != 1 && first_token != 2 && first_token != 4) {
        err = QString("Token \"%1\" is not an expression").arg(token);
        return nullptr;
    }

    do {
        auto tktype = exp.NextToken(&token);
        auto optype = TokenToOp(tktype, unary);
        auto exptype = CheckToken(tktype);
        if (exptype == 1) {  // const or id
            if (tktype == Token::kConst)
                oprs.push(new ExpConst(token.toInt()));
            else
                oprs.push(new ExpId(token));
            unary = false;
        } else if (exptype == 2) {  // lbranch
            ops.push(kLBranch);
            unary = true;
        } else if (exptype == 3) {  // rbranch
            while (true) {
                if (ops.isEmpty()) {
                    error = 1;
                    goto END;
                }
                if (ops.top() == kLBranch) {
                    ops.pop();  // pop (
                    break;
                }
                if (!CalcExp(ops, oprs)) {
                    error = 1;
                    goto END;
                }
            }
            unary = false;
        } else if (exptype == 4 && optype == kNeg) {  // unary operation
            ops.push(kNeg);
            unary = true;
        } else {  // other operation
            while (ops.size() > 0 && ((optype != kExp && optype != kNeg &&
                                       oprank_[ops.top()] >= oprank_[optype]) ||
                                      ((optype == kExp || optype == kNeg) &&
                                       oprank_[ops.top()] > oprank_[optype]))) {
                if (!CalcExp(ops, oprs)) {
                    error = 1;
                    goto END;
                }
            }
            ops.push(optype);
            unary = true;
        }
    } while (CheckToken(exp.NextToken(&token, false, true)));
    while (!ops.isEmpty()) {
        if (!CalcExp(ops, oprs)) {
            error = 1;
            goto END;
        }
    }
END:
    if (error || oprs.size() != 1) {
        err = QString("Error parsing expression");
        return nullptr;
    }
    return oprs.pop();
}

int Expression::CheckToken(Token::Type type) {
    switch (type) {
        case Token::kConst:
        case Token::kId:
            return 1;
        case Token::kLBranch:
            return 2;
        case Token::kRBranch:
            return 3;
        case Token::kMinus:
            return 4;
        case Token::kPlus:
        case Token::kTimes:
        case Token::kDivide:
        case Token::kExp:
            return 5;
        default:
            return 0;
    }
}

Expression::Op Expression::TokenToOp(Token::Type type, bool unary) {
    switch (type) {
        case Token::kPlus:
            return kPlus;
        case Token::kMinus:
            if (unary)
                return kNeg;
            else
                return kMinus;
        case Token::kTimes:
            return kTimes;
        case Token::kDivide:
            return kDivide;
        case Token::kExp:
            return kExp;
        default:
            return kEmpty;
    }
}

bool Expression::CalcExp(QStack<Expression::Op>& ops,
                         QStack<Expression*>& oprs) {
    if (ops.isEmpty() || (ops.top() != kNeg && oprs.size() < 2) ||
        (ops.top() == kNeg && oprs.size() < 1))
        return false;
    auto op = ops.pop();
    if (op != kNeg) {
        auto rexp = oprs.pop();
        auto lexp = oprs.pop();
        oprs.push(new ExpCompound(op, lexp, rexp));
    } else {  // convert -x to 0-x
        auto lexp = new ExpConst(0);
        auto rexp = oprs.pop();
        oprs.push(new ExpCompound(kMinus, lexp, rexp));
    }
    return true;
}
