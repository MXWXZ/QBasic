#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QMimeData>
#include "interpreter.h"
#include "highlighter.h"

class Interpreter;
class Console : public QTextEdit {
    Q_OBJECT

public:
    explicit Console(QWidget* parent = nullptr);
    virtual ~Console() override;

protected:
    void Execute(QString str);
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void insertFromMimeData(const QMimeData* source) override;

protected slots:
    void print(QString str);
    void input(int& res);
    void stop();
    void quit();
    void changed();

private:
    Interpreter* itp_ = nullptr;
    int state_ = 0;
    int inputed_;
    Highlighter* highlighter_ = nullptr;
};

#endif  // CONSOLE_H
