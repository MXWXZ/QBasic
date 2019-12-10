#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QString>
#include "token.h"

class Expression {
public:
    enum Kind { kNone, kConst, kId, kCompound };
    enum Op {
        kEmpty,
        kLBranch,
        kRBranch,
        kPlus,
        kMinus,
        kTimes,
        kDivide,
        kExp,
        kNeg,

        kMax
    };
    static int oprank_[kMax];

public:
    Expression();
    virtual ~Expression();

    static Expression* New(Token& exp, QString& err);
    virtual int Evaluate(const QMap<QString, int>& env, QString& err) = 0;
    virtual Kind GetKind() const { return kind_; }

protected:
    static int CheckToken(Token::Type type);
    static Op TokenToOp(Token::Type type, bool unary);
    static bool CalcExp(QStack<Op>& ops, QStack<Expression*>& oprs);

protected:
    Kind kind_ = kNone;
    QString id_;
    int val_;
    Op op_;
    Expression* lexp_ = nullptr;
    Expression* rexp_ = nullptr;
};

#endif  // EXPRESSION_H
