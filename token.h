#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

class Token {
public:
    // token type
    enum Type {
        kNone,

        kRem,
        kLet,
        kPrint,
        kInput,
        kGoto,
        kIf,
        kEnd,
        kThen,

        kKey,  // keywords

        kConst,
        kId,
        kLBranch,
        kRBranch,
        kEQ,
        kGT,
        kLT,
        kExp,
        kPlus,
        kMinus,
        kTimes,
        kDivide,
        kSpace,

        // do NOT modify
        kMax,
        kErr
    };

    static QString pattern_[kMax];

public:
    Token();
    Token(QString str);

    Type NextToken(QString* token = nullptr, bool edit = true,
                   bool trim = true);
    bool IsEmpty() const;
    void Clear();
    QString GetRemain() const;

private:
    QString str_;
};

#endif  // TOKEN_H
