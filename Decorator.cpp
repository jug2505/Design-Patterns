#include <iostream>

class VisualComponent {
public:
    VisualComponent();
    virtual void Draw();
    virtual void Resize();
    // ...
};

class Decorator : public VisualComponent {
public:
    Decorator(VisualComponent*);

    virtual void Draw() {
        _component->Draw();
    }
    virtual void Resize() {
        _component->Resize();
    }
    // ...
private:
    VisualComponent* _component;
};

class BorderDecorator : public Decorator {
public:
    BorderDecorator(VisualComponent*, int borderWidth);

    virtual void Draw() {
        Decorator::Draw();
        DrawBorder(_width);
    }
    // ...
private:
    void DrawBorder(int);

    int _width;
};

int main(){
    return 0;
}
