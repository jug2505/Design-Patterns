#include <iostream>

typedef int Topic;
const Topic NO_HELP_TOPIC = -1;

class HelpHandler {
public:
    HelpHandler(HelpHandler* h = 0, Topic t = NO_HELP_TOPIC) : _successor(h), _topic(t) {}
    virtual bool HasHelp() {
        return _topic != NO_HELP_TOPIC;
    }
    virtual void SetHandler(HelpHandler*, Topic);
    virtual void HandleHelp() {
        if (_successor != 0) {
            _successor->HandleHelp();
        }
    }
private:
    HelpHandler* _successor;
    Topic _topic;
};

class Widget : public HelpHandler {
protected:
    Widget(Widget* parent, Topic t = NO_HELP_TOPIC) : HelpHandler(parent, t) {
        _parent = parent;
    }
private:
    Widget* _parent;
};

class Button : public Widget {
public:
    Button(Widget* d, Topic t = NO_HELP_TOPIC) : Widget(d, t) {}
    virtual void HandleHelp() {
        if (HasHelp()) {
            // Предоставить справку по кнопке
        }
        else {
            HelpHandler::HandleHelp();
        }
    }
    // Операции класса Widget, которые Button замещает ...
};

class Dialog : public Widget {
public:
    Dialog(HelpHandler* d, Topic t = NO_HELP_TOPIC) : Widget(0) {
        SetHandler(d, t);
    }
    virtual void HandleHelp() {
        if (HasHelp()) {
            // Предоставить справку по диалоговому окну
        }
        else {
            HelpHandler::HandleHelp();
        }
    }
    // Операции класса Widget, которые Button замещает ...
};

class Application : public HelpHandler {
public:
    Application(Topic t) : HelpHandler(0, t) { }
    virtual void HandleHelp() {
        // Показать список разделов справки
    }
    // Операции, относящиеся к самому приложению
};

int main(){
    const Topic PRINT_TOPIC = 1;
    const Topic PAPER_ORIENTATION_TOPIC = 2;
    const Topic APPLICATION_TOPIC = 3;
    Application* application = new Application(APPLICATION_TOPIC);
    Dialog* dialog = new Dialog(application, PRINT_TOPIC);
    Button* button = new Button(dialog, PAPER_ORIENTATION_TOPIC);
    button->HandleHelp();

    return 0;
}
