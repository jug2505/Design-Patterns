#include <iostream>

class Graphic;

class MoveCommand {
public:
    MoveCommand(Graphic* target, const Point& delta);
    void Execute() {
        ConstraintSolver* solver = ConstraintSolver::Instance();
        _state = solver->CreateMemento();
        // Создание хранителя
        _target->Move(_delta);
        solver->Solve();
    }
    void Unexecute() {
        ConstraintSolver* solver = ConstraintSolver::Instance();
        _target->Move(_delta);
        solver->SetMemento(_state);
        // Восстановление состояния
        solver->Solve();
    }
private:
    ConstraintSolverMemento* _state;
    Point _delta;
    Graphic* _target;
};

class ConstraintSolver {
public:
    static ConstraintSolver* Instance();

    void Solve();
    void AddConstraint(
        Graphic* startConnection, Graphic* endConnection
    );
    void RemoveConstraint(
        Graphic* startConnection, Graphic* endConnection
    );

    ConstraintSolverMemento* CreateMemento();
    void SetMemento(ConstraintSolverMemento*);
private:
    // Нетривиальное состояние и операции для 
    // поддержки семантики связанности
};

class ConstraintSolverMemento {
public:
    virtual ~ConstraintSolverMemento();
private:
    friend class ConstraintSolver;
    ConstraintSolverMemento();

    // Закрытое состояние Solver
};


int main(){
    return 0;
}
