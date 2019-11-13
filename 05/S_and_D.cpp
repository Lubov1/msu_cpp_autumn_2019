#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdlib.h>
#include <exception>
#include <ostream>
#include <sstream>
#include "S_and_D.h"

using namespace std;
Serializer::Serializer(ostream& out)
    : out_(out)
{
}


Error Serializer::process(uint64_t val)
{
    out_<<val<<Separator;
    return Error::NoError;


}
Error Serializer::process(bool val)
{
    if (val)
        out_<<"True"<<Separator;
    else 
        out_<<"False"<<Separator;
    return Error::NoError;
}




Deserializer::Deserializer( istream& in)
    : in_(in)
{
}



Error Deserializer::process(uint64_t& val)
{
    uint64_t p;
    in_>> p;
    val = p;
    return Error::NoError;


}
Error Deserializer::process(bool& value)
{
    string text;
    in_ >> text;

    if (text == "True")
        value = true;
    else if (text == "False")
        value = false;
    else
        return Error::CorruptedArchive;

    return Error::NoError;

}



