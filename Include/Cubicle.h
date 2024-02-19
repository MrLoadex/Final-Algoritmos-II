#ifndef CUBICLE_H
#define CUBICLE_H

class Cubicle {
private:
    int id;

public:
    Cubicle(int cubicleId);
    void setId(int _id);
    int getId() const;
};

#endif // CUBICLE_H
