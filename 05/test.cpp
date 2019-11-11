#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdlib.h>
#include <exception>
#include <ostream>
#include <sstream>
#include <assert.h>
#include "S_and_D.h"

using namespace std;

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};
    



int main(int argc, char const *argv[])
{
    Data x { 3, true,2 };
    stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 5, false, 6 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

}
