#include <iostream>

class Shape {
public:
    Shape();
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual Manipulator* CreateManipulator() const;
};

class TextView {
public:
    TextView();
    void GetOrigin(Coord& x, Coord& y) const;
    void GetExtent(Coord& width, Coord& height) const;
    virtual bool IsEmpty() const;
};

// Адаптер класса
class TextShape : public Shape, private TextView {
public:
    TextShape();
    
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const {
        Coord bottom, left, width, height;

        GetOrigin(bottom, left);
        GetExtent(width, height);

        bottomLeft = Point(bottom, left);
        bottomRight = Point(bottom + height, left + width);
    }

    virtual bool IsEmpty() const {
        return TextView::IsEmpty();
    }
    virtual Manipulator* CreateManipulator() const {
        return new TextManipulator(this);
    }
};

// Адаптер объектов
class TextShape : public Shape {
public:
    TextShape(TextView* t) {
        _text = t;
    }

    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const {
        Coord bottom, left, width, height;

        _text->GetOrigin(bottom, left);
        _text->GetExtent(width, height);

        bottomLeft = Point(bottom, left);
        bottomRight = Point(bottom + height, left + width);
    }

    virtual bool IsEmpty() const {
        return _text->IsEmpty();
    }
    virtual Manipulator* CreateManipulator() const {
        return new TextManipulator(this);
    }
private:
    TextView* _text;
};

int main(){
    return 0;
}
