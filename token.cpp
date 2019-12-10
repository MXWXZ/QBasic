#include "token.h"
#include <QRegExp>

QString Token::pattern_[] = {
    "",    "REM", "LET",  "PRINT", "INPUT", "GOTO",
    "IF",  "END", "THEN", "",      "\\d+",  "[a-zA-Z][a-zA-Z0-9]*",
    "\\(", "\\)", "=",    ">",     "<",     "\\*\\*",
    "\\+", "-",   "\\*",  "/",     " "};

Token::Token() {}

Token::Token(QString str) : str_(str) {}

Token::Type Token::NextToken(QString* token, bool edit /* = true */,
                             bool trim /* = true*/) {
    if (trim)
        str_ = str_.trimmed();
    if (str_.isEmpty()) {
        if (token)
            *token = "";
        return kNone;
    }

    // first pattern will be matched
    for (int i = 1; i < kMax; ++i) {
        if (pattern_[i].isEmpty())
            continue;
        QRegExp reg(pattern_[i]);
        if (reg.indexIn(str_) == 0) {
            if (token)
                *token = reg.cap();
            if (edit)
                str_.remove(0, reg.matchedLength());
            return (Type)i;
        }
    }

    if (token)
        *token = str_;
    return kErr;
}

bool Token::IsEmpty() const { return str_.trimmed().isEmpty(); }

void Token::Clear() { str_.clear(); }

QString Token::GetRemain() const { return str_; }
