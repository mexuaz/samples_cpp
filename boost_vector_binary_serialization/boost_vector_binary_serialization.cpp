#include <iostream>
#include <fstream>
#include <random> // random
#include <vector> // vector
#include <iterator> // ostream_iterator
#include <algorithm> // generate

#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

using namespace std;

template<typename T>
inline void print(const vector<T> &v, ostream& os = cout) {
    copy(v.cbegin(), v.cend(), ostream_iterator<T>(os, " "));
    os << endl;
}

int main() {
    const size_t n = 10;
    const char* testfile {"./testfile"};
    vector<unsigned> vec1(n), vec2(n);

    mt19937 eng{random_device()()};

    generate(vec1.begin(), vec1.end(), [&eng]() {
        return uniform_int_distribution<unsigned>{0, 100}(eng);
    });

    generate(vec2.begin(), vec2.end(), [&eng]() {
        return uniform_int_distribution<unsigned>{0, 100}(eng);
    });

    cout << "Test vector1: ";
    print(vec1);

    cout << "Test vector2: ";
    print(vec2);

    cout << "Serializing the vectors ..." << endl;
    ofstream ofs;
    ofs.exceptions(~ofs.goodbit);
    ofs.open(testfile, ios_base::out | ios_base::binary);

    boost::archive::binary_oarchive bo(ofs);
    bo << vec1 << vec2;

    ofs.close();

    cout << "Deserializing the vectors ..." << endl;
    ifstream ifs;
    ifs.exceptions(~ifs.goodbit);
    ifs.open(testfile, ios_base::in | ios_base::binary);

    boost::archive::binary_iarchive bi(ifs);
    decltype(vec1) vec3, vec4;
    bi >> vec3 >> vec4;

    ifs.close();

    cout << "Test vector1: ";
    print(vec1);

    cout << "Test vector2: ";
    print(vec2);

    if(vec1 == vec3 && vec2 == vec4) {
        cout << "Test Passed." << endl;
    } else {
        cout << "Test failed!" << endl;
    }

    return 0;
}
