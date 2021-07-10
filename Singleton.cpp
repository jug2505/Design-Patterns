#include <iostream>

class MazeFactory {
public:
    static MazeFactory* Instance();

    // Здесь находится существующий интерфейс
protected:
    MazeFactory();
private:
    static MazeFactory* _instance;
};

// Если подклассы не порождаются
MazeFactory* MazeFactory::_instance = 0;

MazeFactory* MazeFactory::Instance() {
    if (_instance == 0) {
        _instance = new MazeFactory;
    }
    return _instance;
}

// Если есть подклассы и определяется, какой из них использовать
MazeFactory* MazeFactory::Instance() {
    if (_instance == 0) {
        const char* mazeStyle = getenv("MAZESTYLE");

        if (strcmp(mazeStyle, "bombed") == 0) {
            _instance = new BombedMazeFactory;
        } else if (strcmp(mazeStyle, "enchanted") == 0) {
            _instance = new EnchantedMazeFactory;

            // Другие варианты
        }
        else { // По умолчанию
            _instance = new MazeFactory;
        }
    }
    return _instance;
}

int main(){
    return 0;
}
