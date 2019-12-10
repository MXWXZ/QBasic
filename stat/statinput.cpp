#include "statinput.h"

StatInput::StatInput() { kind_ = kInput; }

StatInput::~StatInput() {}

QString StatInput::Parse(Token& param) {
    if (param.NextToken(&var_) != Token::kId)
        return QString("Id \"%1\" invalid").arg(var_);
    return "";
}

bool StatInput::Run(QMap<QString, int>& env, Interpreter* itp) {
    env[var_] = itp->Input();
    return true;
}
