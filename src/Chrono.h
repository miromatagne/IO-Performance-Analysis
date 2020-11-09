#ifndef INFO_H417_GROUP_15_CHRONO_H
#define INFO_H417_GROUP_15_CHRONO_H


class Chrono {
private:
    double PCFreq = 0.0;
    __int64 CounterStart = 0;
public:
    void startChrono();

    double getChrono();
};


#endif
