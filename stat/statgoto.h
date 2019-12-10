#ifndef STATGOTO_H
#define STATGOTO_H

#include "statement.h"

class StatGoto : public Statement {
public:
    StatGoto();
    virtual ~StatGoto() override;

    virtual QString Parse(Token& param) override;
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) override;

private:
    int n_;
};

#endif  // STATGOTO_H
