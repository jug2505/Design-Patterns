#include <iostream>

class Graphic {
public:
    virtual ~Graphic();

    virtual void Draw(const Point& at) = 0;
    virtual void HandleMouse(Event& event) = 0;
    
    virtual const Point& GetExtent() = 0;

    virtual void Load(istream& from) = 0;
    virtual void Save(ostream& to) = 0;
protected:
    Graphic();
};

class Image: public Graphic {
public:
    Image(const char* file);
    virtual ~Image();

    virtual void Draw(const Point& at);
    virtual void HandleMouse(Event& event);

    virtual const Point& GetExtent();

    virtual void Load(istream& from);
    virtual void Save(ostream& to);
private:
    // ...
};

class ImageProxy : public Graphic {
public:
    ImageProxy(const char* fileName) {
        _fileName = strdup(fileName);
        _extent = Point::Zero;
        _image = 0;
    }
    virtual ~ImageProxy();

    virtual void Draw(const Point& at) {
        GetImage()->Draw(at);
    }

    virtual void HandleMouse(Event& event) {
        GetImage()->HandleMouse(event);
    }

    virtual const Point& GetExtent() {
        if (_extent == Point::Zero) {
            _extent = GetImage()->GetExtent();
        }
        return _extent;
    }

    virtual void Load(istream& from) {
        from >> _extent >> _fileName;
    }
    virtual void Save(ostream& to) {
        to << _extent << _fileName;
    }
protected:
    Image* GetImage() {
        if (_image == 0) {
            _image = new Image(_fileName);
        }
        return _image;
    }
private:
    Image* _image;
    Point _extent;
    char* _fileName;
};

int main(){
    return 0;
}
