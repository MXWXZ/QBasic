#ifndef STATEND_H
#define STATEND_H

#include "statement.h"

class StatEnd : public Statement {
public:
    StatEnd();
    virtual ~StatEnd() override;

    virtual QString Parse(Token& param) override;
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) override;
};

#endif  // STATEND_H
