#ifndef ISTRATEGY_H
#define ISTRATEGY_H

class IStrategy{
public:
    virtual void execute() = 0;
    virtual ~IStrategy(){};
};

#endif // ISTRATEGY_H
