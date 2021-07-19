#include <iostream>

class Command {
public:
    virtual ~Command();
    virtual void Execute() = 0;
protected:
    Command();
};

class OpenCommand: public Command {
public:
    OpenCommand(Application* a) {
        _application = a;
    }
    virtual void Execute() {
        const char* name = AskUser();
        if (name != 0) {
            Document* document = new Document(name);
            _application->Add(document);
            document->Open();
        }
    }
protected:
    virtual const char* AskUser();
private:
    Application* _application;
    char* _responce;
};

class PasteCommand : public Command {
public:
    PasteCommand(Document* doc) {
        _document = doc;
    }

    virtual void Execute() {
        _document->Paste();
    }
private:
    Document* _document;
};

template <class Receiver>
class SimpleCommand : public Command {
public:
    typedef void (Receiver::* Action)();
    SimpleCommand(Receiver* r, Action a) : _receiver(r), _action(a) { }
    virtual void Execute() {
        (_receiver->*_action)();
    }
private:
    Action _action();
    Receiver* _receiver;
};

class MacroCommand : public Command {
public:
    MacroCommand();
    virtual ~MacroCommand();

    virtual void Add(Command* c) {
        _cmds->Append(c);
    }
    
    virtual void Remove(Command* c) {
        _cmds->remove(c);
    }

    virtual void Execute() {
        ListIterator<Command*> i(_cmds);
        for (i.First(); !i.IsDone(); i.Next()) {
            Command* c = i.CurrentItem();
            c->Execute();
        }
    }
private:
    List<Command*>* _cmds;
};

int main(){
    MyClass* receiver = new MyClass;
    Command* aCommand = new SimpleCommand<MyClass>(receiver, &MyClass::Action);
    aCommand->Execute();
    return 0;
}
