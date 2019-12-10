#ifndef STATLET_H
#define STATLET_H

#include "statement.h"
#include "exp/expression.h"

class StatLet : public Statement {
public:
    StatLet();
    virtual ~StatLet() override;

    virtual QString Parse(Token& param) override;
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) override;

private:
    QString id_;
    Expression* exp_ = nullptr;
};

#endif  // STATLET_H
