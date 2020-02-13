#include <iostream>
#include <fstream>
#include <random> // random
#include <vector> // vector
#include <iterator> // ostream_iterator
#include <algorithm> // generate

#include "proto/vectors.pb.h"

using namespace std;

template<typename T>
inline void print(const vector<T> &v, ostream& os = cout) {
    copy(v.cbegin(), v.cend(), ostream_iterator<T>(os, " "));
    os << endl;
}

int main() {
    const size_t n = 10;
    const char* testfile {"./testfile"};
    vector<unsigned long> vec1(n), vec2(n);

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

    Proto3Data data_out;
    *data_out.mutable_vec1() = {vec1.cbegin(), vec1.cend()};
    *data_out.mutable_vec2() = {vec2.cbegin(), vec2.cend()};
    data_out.SerializeToOstream(&ofs);
    ofs.clear();
    ofs.close();

    cout << "Deserializing the vectors ..." << endl;
    ifstream ifs;
    // This does not work for proto3
    // ifs.exceptions(~(ifs.goodbit | ifs.eofbit));
    ifs.open(testfile, ios_base::in | ios_base::binary);

    if(!ifs.good()) {
        throw runtime_error("Failed to open the file.");
    }

    Proto3Data data_in;
    data_in.ParseFromIstream(&ifs);

    auto convertVec = [](const ::google::protobuf::RepeatedField<unsigned long>& s, vector<uint64_t>& d) {
        d.clear();
        d.resize(s.size());
        copy(s.cbegin(), s.cend(), d.begin());
    };

    decltype(vec1) vec3, vec4;
    convertVec(data_in.vec1(), vec3);
    convertVec(data_in.vec2(), vec4);

    ifs.close();

    cout << "Test vector3: ";
    print(vec3);

    cout << "Test vector4: ";
    print(vec4);

    if(vec1 == vec3 && vec2 == vec4) {
        cout << "Test Passed." << endl;
    } else {
        cout << "Test failed!" << endl;
    }

    return 0;
}
