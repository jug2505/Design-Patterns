#include <iostream>

class Subject {
public:
    virtual ~Subject();
    virtual void Attach(Observer* o) {
        _observers->Append(o);
    }
    virtual void Detach(Observer* o) {
        _observers->Remove(o);
    }
    virtual void Notify() {
        ListIterator<Observer*> i(_observers);
        for (i.First(); !i.IsDone(); i.Next()) {
            i.CurrentItem()->Update(this);
        }
    }
protected:
    Subject();
private:
    List<Observer*>* _observers;
};

class Observer {
public:
    virtual ~Observer();
    virtual void Update(Subject* theChangedSubject) = 0;
protected:
    Observer();
};

class ClockTimer : public Subject {
public:
    ClockTimer();
    virtual int GetHour();
    virtual int GetMinute();
    virtual int GetSecond();
    void Tick() {
        // Обновить внутреннее представление времени
        Notify();
    }
};

class DigitalClock : public Widget, public Observer {
public:
    DigitalClock(ClockTimer* s) {
        _subject = s;
        _subject->Attach(this);
    }
    DigitalClock() {
        _subject->Detach(this);
    }
    virtual ~DigitalClock();

    virtual void Update(Subject* theChangedSubject) {
        if (theChangedSubject == _subject) {
            Draw();
        }
    }

    virtual void Draw() {
        // Получить новые значения от субъекта

        int hour = _subject->GetHour();
        int minute = _subject->GetMinute();

        // Нарисовать цифровые часы
    }
private:
    ClockTimer* _subject;
};

class AnalogClock : public Widget, public Observer {
public:
    AnalogClock(ClockTimer*);
    virtual void Update(Subject*);
    virtual void Draw();
};

int main(){
    ClockTimer* timer = new ClockTimer;
    AnalogClock* analogClock = new AnalogClock(timer);
    DigitalClock* digitalClock = new DigitalClock(timer);

    return 0;
}
