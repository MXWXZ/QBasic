#ifndef STATREM_H
#define STATREM_H

#include "statement.h"

class StatRem : public Statement {
public:
    StatRem();
    virtual ~StatRem() override;

    virtual QString Parse(Token& param) override;
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) override;
};

#endif  // STATREM_H
