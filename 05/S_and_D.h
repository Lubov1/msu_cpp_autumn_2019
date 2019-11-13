#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdlib.h>
#include <exception>
#include <ostream>
#include <sstream>
using namespace std;

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
public:
    ostream& out_;
    static constexpr char Separator = ' ';
    Serializer(ostream& out);

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(forward<ArgsT>(args)...);
    }
    
private:

    Error process(uint64_t val);
    Error process(bool val);


    template <class T, class ... Args>
    Error process(T&& val, Args&&... args)
    {
        process(val);
        process(forward<Args>(args)...);
        return Error::NoError;

    }
};



class Deserializer
{
    istream& in_;

    static constexpr char Separator = ' ';
public:
    explicit Deserializer( istream& in);
    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

    
private:
    Error process(uint64_t& val);
    Error process(bool& value);
    template <class T, class... Args>
    Error process(T &val, Args&... args)
    {
        process(val);
        process(args...);
        return Error::NoError;
    }
};




