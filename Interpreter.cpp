#include <iostream>

class BooleanExp {
public:
    BooleanExp();
    virtual ~BooleanExp();
    virtual bool Evaluate(Context&) = 0;
    virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
    virtual BooleanExp* Copy() const = 0;
};

class Contex {
public:
    bool Lookup(const char*) const;
    void Allign(VariableExp*, bool);
};

class VariableExp : public BooleanExp {
public:
    VariableExp(const char* name) {
        _name = strdup(name);
    }
    virtual ~VariableExp();
    virtual bool Evaluate(Context& aContext) {
        return aContext.Lookup(_name);
    }
    virtual BooleanExp* Replace(const char* name, BooleanExp& exp) {
        if (strcmp(name, _name) == 0) {
            return exp.Copy();
        }
        else {
            return new VariableExp(_name);
        }
    }
    virtual BooleanExp* Copy() const {
        return new VariableExp(_name);
    }
private:
    char* _name;
};

class AndExp : public BooleanExp {
public:
    AndExp(BooleanExp* op1, BooleanExp* op2) {
        _operand1 = op1;
        _operand2 = op2;
    }
    virtual ~AndExp();
    virtual bool Evaluate(Context& aContext) {
        return _operand1->Evaluate(aContext) && _operand2->Evaluate(aContext);
    }
    virtual BooleanExp* Replace(const char* name, BooleanExp& exp) {
        return new AndExp(
            _operand1->Replace(name, exp),
            _operand2->Replace(name, exp)
        );
    }
    virtual BooleanExp* Copy() const {
        return new AndExp(_operand1->Copy(), _operand2->Copy());
    }
private:
    BooleanExp* _operand1;
    BooleanExp* _operand2;
};

int main(){
    BooleanExp* expression;
    Context context;

    VariableExp* x = new VariableExp("X");
    VariableExp* y = new VariableExp("Y");
    
    expression = new OrExp(
        new AndExp(new Constant(true), x),
        new AndExp(y, new NotExp(x)
    );

    context.Assign(x, false);
    context.Assign(y, true);

    bool result = expression->Evaluate(context);

    return 0;
}
