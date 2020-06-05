#ifndef SPADE_ITEM_H
#define SPADE_ITEM_H


class Item {
    int id;
    bool equalRelation;

public:
    Item(int id, bool equalRelation) : id(id), equalRelation(equalRelation) {}

    int getId() {
        return id;
    }

    bool isEqualRelation() {
        return equalRelation;
    }

    bool operator==(Item &rhs) {
        return id == rhs.id && equalRelation == rhs.equalRelation;
    }
};


#endif //SPADE_ITEM_H
