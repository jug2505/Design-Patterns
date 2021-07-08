#include <iostream>

class Creator {
public:
    virtual Product* Create(ProductId id) {
        if (id == MINE) return new MyProduct;
        if (id == YOURS) return new YourProduct;

        return 0;
    }
};

class MyCreator : Creator {
public:
    virtual Product* Create(ProductId id) {
        if (id == MINE) return new YourProduct;
        if (id == YOURS) return new MyProduct;
        if (id = THEIRS) return new TheirProduct;
        return Creator::Create(id);
    }
};

// Отложенная инициализация
class Creator {
public:
    Product* GetProduct() {
        if (_product == 0) {
            _product = CreateProduct();
        }
        return _product;
    }
protected:
    virtual Product* CreateProduct();
private:
    Product* _product;
};

// Шаблонная реализация
template <class TheProduct>
class StandardCreator : public Creator {
public:
    virtual Product* CreateProduct() {
        return new TheProduct;
    }
};

int main(){
    return 0;
}
