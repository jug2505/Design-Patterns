#include <iostream>

class Window {
public:
    Window(View* contents);

    // Запросы, обрабатываемые окном
    virtual void DrawContents();

    virtual void Open();
    virtual void Close();
    virtual void Iconify();
    virtual void Deiconify();

    // Запросы, перенаправляемые реализации
    virtual void SetOrigin(const Point& at);
    virtual void SetExtent(const Point& extent);
    virtual void Raise();
    virtual void Lower();

    virtual void DrawLine(const Point&, const Point&);
    virtual void DrawRect(const Point& p1, const Point& p2) {
        WindowImp* imp = GetWindowImp();
        imp->DeviceRect(p1.X(), p1.Y(), p2.X(), p2.Y());
    }
    virtual void DrawPolygon(const Point[], int n);
    virtual void DrawText(const char*, const Point&);

protected:
    WindowImp* GetWindowImp() {
        if (_imp == 0) {
            _imp = WindowSystemFactory::Instance()->MakeWindowImp();
        }
        return _imp;
    }
    View* GetView();

private:
    WindowImp* _imp;
    View* _contents; // Содерджимое окна
};

class WindowImp {
public:
    virtual void ImpTop() = 0;
    virtual void ImpBottom() = 0;
    virtual void ImpSetExtent(const Point&) = 0;
    virtual void ImpSetOrigin(const Point&) = 0;

    virtual void DeviceRect(Coord, Coord, Coord, Coord) = 0;
    virtual void DeviceText(const char*, Coord, Coord) = 0;
    virtual void DeviceBitmap(const char*, Coord, Coord) = 0;
    // Множество других функций для рисования в окне ...
protected:
    WindowImp();
};

class ApplicationWindow : public Window {
public:
    // ...
    virtual void DrawContents() {
        GetView()->DrawOn(this);
    }
};

class IconWindow : public Window {
public:
    // ...
    virtual void DrawContents() {
        WindowImp* imp = GetWindowImp();
        if (imp != 0) {
            imp->DeviceBitmap(_bitmapName, 0.0, 0.0);
        }
    }
private:
    const char* _bitmapName;
};

class XWindowImp : public WindowImp {
public:
    XWindowImp();
    // Опрерации открытого интерфейса
private:
    // Переменные, описывающите состояние, специфичное для X Window system
    Display* _dpy;
    Drawable _winid;
    GC _gc;
};

int main(){
    return 0;
}
