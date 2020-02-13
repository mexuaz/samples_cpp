#include <iostream>
#include <random> // random
#include <vector> // vector
#include <iterator> // ostream_iterator
#include <algorithm> // generate

#include "fb/vectors_generated.h"
#include "fb/flatbuffers/util.h"


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


    flatbuffers::FlatBufferBuilder fbb;

    auto ser_out = vectors::CreateFlbDataDirect(fbb, &vec1, &vec2);


    vectors::FinishFlbDataBuffer(fbb, ser_out);

    if (!flatbuffers::SaveFile(
            testfile,
            reinterpret_cast<char *>(fbb.GetBufferPointer()),
            fbb.GetSize(),
            true)) {
        throw runtime_error("Could not serialize the file.");
    }


    cout << "Deserializing the vectors ..." << endl;


    string content;
    if(!flatbuffers::LoadFile(testfile, true, &content)) {
        throw std::runtime_error("Could not load the binary file.");
    }

    auto ser_in = vectors::GetFlbData(content.data());

    // the vector type in flatbuffers
    auto convertVec = [](const flatbuffers::Vector<unsigned long>* s, vector<unsigned long>& d) {
        if(!s) {
            throw runtime_error("Null pointer vector!");
        }
        d.clear();
        d.resize(s->size());
        copy(s->cbegin(), s->cend(), d.begin());
    };

    decltype(vec1) vec3, vec4;
    convertVec(ser_in->Vec1(), vec3);
    convertVec(ser_in->Vec2(), vec4);


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
