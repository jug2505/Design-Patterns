#include <iostream>

class MazePrototypeFactory : public MazeFactory {
public:
    MazePrototypeFactory(Maze* m, Wall* w, Room* r, Door* d) {
        _prototypeMaze = m;
        _prototypeWall = w;
        _prototypeRoom = r;
        _prototypeDoor = d;
    }

    virtual Maze* MakeMaze() const;
    virtual Room* MakeRoom() const;
    virtual Wall* MakeWall() const {
        return _prototypeWall->Clone();
    }
    virtual Door* MakeDoor(Room* r1, Room* r2) const {
        Door* door = _prototypeDoor->Clone();
        door->Initialize(r1, r2);
        return door;
    }

private:
    Maze* _prototypeMaze;
    Room* _prototypeRoom;
    Wall* _prototypeWall;
    Door* _prototypeDoor;
};

class Door : public MapSite {
public:
    Door();
    Door(const Door& other) {
        _room1 = other._room1;
        _room2 = other._room2;
    }
    
    virtual void Initialize(Room* r1, Room* r2) {
        _room1 = r1;
        _room2 = r2;
    }
    virtual Door* Clone() const {
        return new Door(*this);
    }

    virtual void Enter();
    Room* OtherSideFrom(Room*);

private:
    Room* _room1;
    Room* _room2;
};

class BombedWall : public Wall{
public:
    BombedWall();
    BombedWall(const BombedWall& other) : Wall(other){
        _bomb = other._bomb;    
    }

    virtual Wall* Clone() const {
        return new BombedWall(*this);
    }
    bool HasBomb();

private:
    bool _bomb;
}

int main(){
    return 0;
}
