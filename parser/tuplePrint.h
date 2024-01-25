#pragma warning( disable : 4100 )

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <stdexcept>

template <size_t Index, typename... Args>
struct TuplePrinter {
    static void print(std::ostream& os, const std::tuple<Args...>& t) {
        
        TuplePrinter<Index - 1, Args...>::print(os, t);
        os <<  std::get<Index - 1>(t) << " ";
    }
};

template <typename... Args>
struct TuplePrinter<0, Args...> {
    static void print(std::ostream& os, const std::tuple<Args...>& t) {
    }
};

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
    TuplePrinter<sizeof...(Args), Args...>::print(os, t);
    return os;
}