#include <iostream>

class MazeBuilder {
public:
    virtual void BuildMaze() {}
    virtual void BuildRoom(int room) {}
    virtual void BuildDoor(int roomFrom, int roomTo) {}
    virtual Maze* GetMaze() { return 0; }
protected:
    MazeBuilder();
};

class StandardMazeBuilder : public MazeBuilder {
public:
    StandardMazeBuilder() {
        _currentMaze = 0;
    }

    virtual void BuildMaze() {
        _currentMaze = new Maze;
    }
    
    virtual void BuildRoom(int n) {
        if (!_currentMaze->RoomNo(n)) {
            Room* room = new Room(n);
            _currentMaze->AddRoom(room);

            room->SetSide(North, new Wall);
            room->SetSide(South, new Wall);
            room->SetSide(East, new Wall);
            room->SetSide(West, new Wall);
        }
    }

    virtual void BuildDoor(int n1, int n2) {
        Room* r1 = _currentMaze->RoomNo(n1);
        Room* r2 = _currentMaze->RoomNo(n2);
        Door* d = new Door(r1, r2);

        r1->SetSide(CommonWall(r1, r2), d);
        r2->SetSide(CommonWall(r2, r1), d);
    }

    virtual Maze* GetMaze() {
        return _currentMaze;
    }

private:
    Direction CommonWall(Room*, Room*);
    Maze* _currentMaze;
};

Maze* MazeGame::CreateMaze(MazeBuilder& builder) {
    builder.BuildMaze();
    
    builder.BuildRoom(1);
    builder.BuildRoom(2);
    builder.BuildDoor(1, 2);

    return builder.GetMaze();
}



int main(){
    return 0;
}
