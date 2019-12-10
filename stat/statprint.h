#ifndef STATPRINT_H
#define STATPRINT_H

#include "statement.h"
#include "exp/expression.h"

class StatPrint : public Statement {
public:
    StatPrint();
    virtual ~StatPrint() override;

    virtual QString Parse(Token& param) override;
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) override;

private:
    Expression* exp_;
};

#endif  // STATPRINT_H
