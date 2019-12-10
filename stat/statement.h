#ifndef STATEMENT_H
#define STATEMENT_H

#include <QMap>
#include <token.h>
#include <interpreter.h>

class Interpreter;
class Statement {
public:
    enum Kind { kNone, kRem, kLet, kPrint, kInput, kGoto, kIf, kEnd };

public:
    Statement();
    virtual ~Statement();

    virtual QString Parse(Token& param) = 0;
    static Statement* New(Token& exp, QString& err);
    virtual bool Run(QMap<QString, int>& env, Interpreter* itp) = 0;
    virtual Kind GetKind() const { return kind_; }

protected:
    Kind kind_ = kNone;
};

#endif  // STATEMENT_H
