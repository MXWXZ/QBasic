#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QMap>
#include <QThread>
#include "stat/statement.h"
#include "console.h"

class Console;
class Statement;
class Interpreter : public QThread {
    Q_OBJECT

public:
    Interpreter();
    virtual ~Interpreter() override;

    QString Parse(QString line);
    QString Execute(QString line);
    void Clear();
    QString GetList() const;

    int GetPC() const { return pc_.key(); }
    bool Goto(int line);
    void Print(QString str, bool iserr = true);
    int Input();

protected:
    virtual void run() override;

signals:
    void print(QString str);
    void input(int& res);
    void stop();

private:
    bool running_ = false;
    QMap<int, QPair<QString, Statement*>>::iterator pc_;
    QMap<int, QPair<QString, Statement*>>::iterator npc_;
    QMap<int, QPair<QString, Statement*>> stat_;
    QMap<QString, int> env_;
};

#endif  // INTERPRETER_H
