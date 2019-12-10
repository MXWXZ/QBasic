#include "statend.h"

StatEnd::StatEnd() { kind_ = kEnd; }

StatEnd::~StatEnd() {}

QString StatEnd::Parse(Token& param) { return ""; }

bool StatEnd::Run(QMap<QString, int>& env, Interpreter* itp) { return false; }
