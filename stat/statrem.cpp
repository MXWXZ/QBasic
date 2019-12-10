#include "statrem.h"

StatRem::StatRem() { kind_ = kRem; }

StatRem::~StatRem() {}

QString StatRem::Parse(Token& param) {
    param.Clear();
    return "";
}

bool StatRem::Run(QMap<QString, int>& env, Interpreter* itp) { return true; }
