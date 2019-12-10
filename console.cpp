#include "console.h"
#include <QMessageBox>
#include <QApplication>
#include "token.h"

Console::Console(QWidget* parent) : QTextEdit(parent) {
    itp_ = new Interpreter();
    connect(itp_, &Interpreter::stop, this, &Console::stop);
    connect(this, &Console::destroyed, this, &Console::quit);
    connect(this, &Console::textChanged, this, &Console::changed);
    highlighter_ = new Highlighter(document());
}

Console::~Console() {
    delete itp_;
    delete highlighter_;
    itp_ = nullptr;
    highlighter_ = nullptr;
}

void Console::Execute(QString str) {
    if (str == "QUIT") {
        exit(0);
    } else if (str == "HELP") {
        QString help =
            "RUN: run the program\nLIST: list steps\nCLEAR: delete "
            "program\nHELP: show help\nQUIT: quit\n\n";
        textCursor().insertText(help);
    } else if (str == "CLEAR") {
        itp_->Clear();
    } else if (str == "LIST") {
        textCursor().insertText(itp_->GetList() + "\n");
    } else if (str == "RUN") {
        state_ = 1;
        // must use Qt::BlockingQueuedConnection to make sequence
        // in different thread
        connect(itp_, &Interpreter::print, this, &Console::print,
                Qt::BlockingQueuedConnection);
        connect(itp_, &Interpreter::input, this, &Console::input,
                Qt::BlockingQueuedConnection);
        itp_->start();
        // disconnect will be in slots
    } else if (str.startsWith("LET ") || str.startsWith("PRINT ") ||
               str.startsWith("INPUT ")) {
        state_ = 1;
        // same thread, so just use default setting
        connect(itp_, &Interpreter::print, this, &Console::print);
        connect(itp_, &Interpreter::input, this, &Console::input);
        auto ret = itp_->Execute(str);
        if (!ret.isEmpty())
            textCursor().insertText("Error: " + ret + "\n");
        // disconnect will be in slots
    } else {
        auto ret = itp_->Parse(str);
        if (!ret.isEmpty())
            textCursor().insertText("Error: " + ret + "\n");
    }
}

void Console::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Backspace) {
        if (toPlainText().back() == '\n' ||
            (state_ == 2 && toPlainText().endsWith("\n ? ")))
            return;
    } else if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        QString lastline = cursor.selectedText();

        if (state_ == 0) {
            QTextEdit::keyPressEvent(event);
            Execute(lastline);
            return;
        } else if (state_ == 2) {
            lastline.remove(0, 3);
            lastline = lastline.trimmed();
            if (lastline.isEmpty()) {
                append(" ? ");
                return;
            } else {
                bool ok;
                inputed_ = lastline.toInt(&ok);
                if (!ok) {
                    append(QString("Error: Invalid Input\n ? "));
                    return;
                } else {
                    state_ = 1;
                }
            }
        } else {
            return;
        }
    } else if (state_ == 1) {
        return;
    }
    QTextEdit::keyPressEvent(event);
}

void Console::mousePressEvent(QMouseEvent* e) {}

void Console::insertFromMimeData(const QMimeData* source) {
    // hook paste operation
    QMimeData tmp;
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.select(QTextCursor::LineUnderCursor);
    QString lastline = cursor.selectedText();
    auto strs = lastline + source->text();
    auto str = strs.split('\n');
    auto last = str.last();
    str.removeLast();  // ignore last line
    for (auto i : str) {
        tmp.setText(i + "\n");
        QTextEdit::insertFromMimeData(&tmp);
        Execute(i);
    }
    // add last line to the gui
    tmp.setText(last);
    QTextEdit::insertFromMimeData(&tmp);
}

void Console::print(QString str) { textCursor().insertText(str); }

void Console::input(int& res) {
    textCursor().insertText(" ? ");
    state_ = 2;
    while (state_ == 2)
        QApplication::processEvents();  // pull message to prevent dead
    res = inputed_;
}

void Console::stop() {
    state_ = 0;
    disconnect(itp_, &Interpreter::print, this, &Console::print);
    disconnect(itp_, &Interpreter::input, this, &Console::input);
}

void Console::quit() { itp_->quit(); }

void Console::changed() { moveCursor(QTextCursor::End); }
