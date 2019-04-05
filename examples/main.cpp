#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

#include <teestream.h>


template <typename char_type,
          typename traits,
          typename T>
std::basic_ostream<char_type, traits> & operator<<(
        std::basic_ostream<char_type, traits> & stream,
        std::vector<T> const & vector
    )
{
    auto iterator = std::begin(vector);
    if (iterator < std::end(vector)) {
        stream << *iterator;
        ++iterator;
    }
    while (iterator < std::end(vector)) {
        stream << ", " << *iterator;
        ++iterator;
    }
    return stream;
}

template <typename char_type,
          typename traits>
void test1(std::basic_ostream<char_type, traits> & stream)
{
    const double pi = 3.141592653589793238;
    stream << "Here we are in a test function!" << '\n';
    stream << "pi = " << pi << '\n';
    stream << std::setprecision(std::numeric_limits<double>::digits10);
    stream << "pi = " << pi << '\n';
}

template <typename char_type,
          typename traits>
void test2(std::basic_ostream<char_type, traits> & stream)
{
    std::vector<int> v;
    v.push_back(2);
    v.push_back(5);
    v.push_back(7);
    v.push_back(8);
    v.push_back(4);
    v.push_back(1);

    stream << "Vector: " << v << '\n';

    stream << std::endl;

    const std::vector<int> & vr = v;

    size_t max_index = std::distance(vr.begin(), std::max_element(vr.begin(), vr.end()));

    stream << "Max element is " << vr[max_index] << " at index " << max_index << '\n';
}

void test_normal()
{
    std::ofstream log("data.log");
    teestream stream(std::cout, log);

    stream << "Hello world!" << '\n';

    std::string name = "Claudio";
    stream << "My name is " << name << '\n';
    stream << "I am " << 26 << " years old" << '\n';
    stream << "Goodbye!" << std::endl;

    test1(stream);
    test2(stream);
}

void test_wide()
{
    std::wofstream log("wdata.log");
    wteestream stream(std::wcout, log);

    stream << "Hello world!" << '\n';

    std::wstring name = L"Claudio";
    stream << "My name is " << name << '\n';
    stream << "I am " << 26 << " years old" << '\n';
    stream << "Goodbye!" << std::endl;

    test1(stream);
    test2(stream);
}

int main()
{
    std::cout << "Testing on std::cout" << '\n';
    test_normal();
    std::cout << "\n\n\n";
    std::cout << "Testing on std::wcout" << '\n';
    test_wide();
}
