#include <iostream>

class Equipment {
public:
    virtual ~Equipment();

    const char* Name() { return _name; }

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();

    virtual void Accept(EquipmentVisitor&);
protected:
    Equipment(const char*);
private:
    const char* _name;
};

class EquipmentVisitor {
public:
    virtual ~EquipmentVisitor();

    virtual void VisitFloppyDisk(FloppyDisk*);
    virtual void VisitCard(Card*);
    virtual void VisitChassis(Chassis*);
    virtual void VisitBus(Bus*);

protected:
    EquipmentVisitor();
};

void FloppyDisk::Accept(EquipmentVisitor& visitor) {
    visitor.VisitFloppyDisk(this);
}

void Chassis::Accept(EquipmentVisitor& visitor) {
    for (ListIterator i(_parts); !i.IsDone(); i.Next()) {
        i.CurrentItem()->Accept(visitor);
    }
    visitor.VisitChassis(this);
}

class PricingVisitor : public EquipmentVisitor {
public:
    PricingVisitor();

    Currency& GetTotalPrice();

    virtual void VisitFloppyDisk(FloppyDisk* e){
        _total += e->NetPrice();
    }
    virtual void VisitCard(Card*);
    virtual void VisitChassis(Chassis* e) {
        _total += e->DiscountPrice();
    }
    virtual void VisitBus(Bus*);

private:
    Currency _total;
};

class InventoryVisitor : public EquipmentVisitor {
public:
    InventoryVisitor();

    Inventory& GetInventory();

    virtual void VisitFloppyDisk(FloppyDisk* e) {
        _inventory.Accumulate(e);
    }
    virtual void VisitCard(Card*);
    virtual void VisitChassis(Chassis* e) {
        _inventory.Accumulate(e);
    }
    virtual void VisitBus(Bus*);

private:
    Inventory _inventory;
};

int main(){

    return 0;
}
