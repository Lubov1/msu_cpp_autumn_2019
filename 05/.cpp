#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdlib.h>
#include <exception>
#include <ostream>
#include <sstream>
#include <assert.h>
using namespace std;
Serializer::Serializer(ostream& out)
    : out_(out)
{
}

template <class T>
Error Serializer::save(T& object)
{
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args)
{
    return process(args...);
}


Error Serializer::process(uint64_t val)
{
    out_<<val;
    return Error::NoError;


}
Error Serializer::process(bool val)
{
    if (val)
        out_<<" True ";
    else 
        out_<<" False ";
    return Error::NoError;
}


template <class T, class ... Args>
Error Serializer::process(T&& val, Args&&... args)
{
    process(val);
    process(forward<Args>(args)...);
    return Error::NoError;

}



Deserializer::Deserializer( istream& in)
    : in_(in)
{
}

template <class T>
Error Deserializer::load(T& object)
{
    return object.serialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&... args)
{
    return process(args...);
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

template <class T, class... Args>
Error Deserializer::process(T &val, Args&... args)
    {
        process(val);
        process(args...);
        return Error::NoError;
    }



