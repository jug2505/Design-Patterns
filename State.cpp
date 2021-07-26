#include <iostream>

class TCPOctetStream;
class TCPState {
public:
    virtual void Transmit(TCPConnection*, TCPOctetStream*) {}
    virtual void ActiveOpen(TCPConnection*) {}
    virtual void PassiveOpen(TCPConnection*) {}
    virtual void Close(TCPConnection*) {}
    virtual void Synchronize(TCPConnection*) {}
    virtual void Acknowledge(TCPConnection*);
    virtual void Send(TCPConnection*);
protected:
    void ChangeState(TCPConnection* t, TCPState* s) {
        t->ChangeState(s);
    }
};

class TCPConnection {
public:
    TCPConnection() {
        _state = TCPClosed::Instance();
    }

    void ActiveOpen() {
        _state->ActiveOpen(this);
    }
    void PassiveOpen() {
        _state->PassiveOpen(this);
    }
    void Close() {
        _state->Close(this);
    }
    void Send();
    void Acknowledge() {
        _state->Acknowledge(this);
    }
    void Synchronize() {
        _state->Synchronize(this);
    }

    void ProcessOctet(TCPOctetStream*);
private:
    friend class TCPState;
    void ChangeState(TCPState* s) {
        _state = s;
    }
private:
    TCPState* _state;
};

class TCPEstablished : public TCPState {
public:
    static TCPState* Instance();
    virtual void Transmit(TCPConnection* t, TCPOctetStream* o) {
        t->ProcessOctet(o);
    }
    virtual void Close(TCPConnection* t) {
        ChangeState(t, TCPListen::Instance());
    }
};

class TCPListen : public TCPState {
public:
    static TCPState* Instance();
    virtual void Send(TCPConnection* t) {
        ChangeState(t, TCPEstablished::Instance());
    }
};

class TCPClosed : public TCPState {
public:
    static TCPState* Instance();
    virtual void ActiveOpen(TCPConnection* t) {
        // Послать SYN, получить SYN, ACK и т.д.
        ChangeState(t, TCPEstablished::Instance());
    }
    virtual void PassiveOpen(TCPConnection* t) {
        ChangeState(t, TCPListen::Instance());
    }
};

int main(){

    return 0;
}
