#ifndef STATINPUT_H
#define STATINPUT_H

#include "statement.h"

class StatInput : public Statement {
public:
    StatInput();
    virtual ~StatInput() override;

    virtual QString Parse(Token& param) override;
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) override;

private:
    QString var_;
};

#endif  // STATINPUT_H
