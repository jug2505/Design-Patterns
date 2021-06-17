#include <iostream>

enum Direction {North, South, East, West};

class MapSite {
public:
    virtual void Enter() = 0;
};

class Room : public MapSite {
public:
    Room(int roomNo);

    MapSite* GetSide(Direction) const;
    void SetSide(Direction, MapSite*);

    virtual void Enter();

private:
    MapSite* _sides[4];
    int _roomNumber;
};

class Wall : public MapSite {
public:
    Wall();

    virtual void Enter();
};

class Door : public MapSite {
public:
    Door(Room* = 0, Room* = 0);

    virtual void Enter();
    Room* OtherSideFrom(Room*);

private:
    Room* _room1;
    Room* _room2;
    bool _isOpen;
};

class Maze {
public:
    Maze();

    void AddRoom(Room*);
    Room* RoomNo(int) const;
private:

};

// Абстрактная фабрика

class MazeFactory {
public:
    MazeFactory();

    virtual Maze* MakeMaze() const { return new Maze; }
    virtual Wall* MakeWall() const { return new Wall; }
    virtual Room* MakeRoom(int n) const { return new Room(n); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }
};

class EnchantedMazeFactory : public MazeFactory {
public:
    EnchantedMazeFactory();

    virtual Room* MakeRoom(int n) const { return new EnchantedRoom(n, CastSpell()); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new DoorNeedingSpell(r1, r2); }

protected:
    Spell* CastSpell() const;
};

int main(){
    return 0;
}
