#include "statgoto.h"

StatGoto::StatGoto() { kind_ = kGoto; }

StatGoto::~StatGoto() {}

QString StatGoto::Parse(Token& param) {
    QString token;
    if (param.NextToken(&token) != Token::kConst)
        return QString("Line number \"%1\" invalid").arg(token);

    n_ = token.toInt();
    return "";
}

bool StatGoto::Run(QMap<QString, int>& env, Interpreter* itp) {
    return itp->Goto(n_);
}
