#ifndef STATIF_H
#define STATIF_H

#include "statement.h"
#include "exp/expression.h"

class StatIf : public Statement {
public:
    StatIf();
    virtual ~StatIf() override;

    virtual QString Parse(Token& param) override;
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) override;

private:
    Expression* exp1_ = nullptr;
    Token::Type op_;
    Expression* exp2_ = nullptr;
    int n_;
};

#endif  // STATIF_H
