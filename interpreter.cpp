#include "interpreter.h"

Interpreter::Interpreter() {}

Interpreter::~Interpreter() { Clear(); }

QString Interpreter::Parse(QString line) {
    bool ok;
    line = line.simplified();
    auto numstr = line.section(' ', 0, 0);
    if (numstr.isEmpty())
        return "";
    auto num = numstr.toInt(&ok);
    if (!ok || num < 0)
        return QString("Line number \"%1\" invalid").arg(numstr);

    QString err;
    Token token(line.section(' ', 1));
    Statement* cmd = Statement::New(token, err);
    if (!err.isEmpty())
        return err;
    if (!token.IsEmpty()) {  // token remained
        delete cmd;
        return QString("Invalid token \"%1\"").arg(token.GetRemain());
    }

    stat_[num] = qMakePair(line, cmd);
    return "";
}

QString Interpreter::Execute(QString line) {
    QString err;
    Token token(line);
    Statement* cmd = Statement::New(token, err);
    if (!err.isEmpty())
        goto END;
    if (!token.IsEmpty()) {  // token remained
        err = QString("Invalid token \"%1\"").arg(token.GetRemain());
        goto END;
    }
    cmd->Run(env_, this);
END:
    emit stop();
    delete cmd;
    return err;
}

void Interpreter::Clear() {
    for (auto& i : stat_)
        delete i.second;
    stat_.clear();
    env_.clear();
}

QString Interpreter::GetList() const {
    QString ret;
    for (auto& i : stat_)
        ret += i.first + "\n";
    return ret;
}

void Interpreter::run() {
    running_ = true;
    pc_ = stat_.begin();
    auto runenv = env_;
    while (pc_ != stat_.end()) {
        npc_ = pc_ + 1;  // statement may modify npc
        if (!pc_->second->Run(runenv, this))
            break;
        pc_ = npc_;
    }
    running_ = false;
    emit print("\n");
    emit stop();
}

bool Interpreter::Goto(int line) {
    if (!stat_.contains(line)) {
        Print(QString("Error: Line \"%1\" invalid\n").arg(line));
        return false;
    }
    npc_ = stat_.find(line);
    return true;
}

void Interpreter::Print(QString str, bool iserr /* = true*/) {
    if (iserr) {
        if (running_)  // trick, execute do not have pc_ so just ignore it
            emit print(QString("Line %1: %2\n").arg(pc_.key()).arg(str));
        else
            emit print(QString("Error: %1\n").arg(str));
    } else {
        emit print(str + "\n");
    }
}

int Interpreter::Input() {
    int res;
    emit input(res);
    return res;
}
