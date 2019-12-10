#include "statement.h"
#include "statrem.h"
#include "statlet.h"
#include "statprint.h"
#include "statinput.h"
#include "statgoto.h"
#include "statif.h"
#include "statend.h"

Statement::Statement() {}

Statement::~Statement() {}

Statement* Statement::New(Token& exp, QString& err) {
    Statement* ret = nullptr;
    QString token;
    auto type = exp.NextToken(&token);
    switch (type) {
        case Token::kRem:
            ret = new StatRem;
            break;
        case Token::kLet:
            ret = new StatLet;
            break;
        case Token::kPrint:
            ret = new StatPrint;
            break;
        case Token::kInput:
            ret = new StatInput;
            break;
        case Token::kGoto:
            ret = new StatGoto;
            break;
        case Token::kIf:
            ret = new StatIf;
            break;
        case Token::kEnd:
            ret = new StatEnd;
            break;
        default:
            err = QString("Statement \"%1\" invalid").arg(token);
            return nullptr;
    }
    if (!exp.IsEmpty() &&
        exp.NextToken(nullptr, true, false) != Token::kSpace) {
        delete ret;
        err = QString("Missing space after statement");
        return nullptr;
    }
    err = ret->Parse(exp);
    if (!err.isEmpty()) {
        delete ret;
        ret = nullptr;
    }
    return ret;
}
