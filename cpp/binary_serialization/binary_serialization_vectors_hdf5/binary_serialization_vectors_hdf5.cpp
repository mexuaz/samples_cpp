#include <iostream>
#include <fstream>
#include <random> // random
#include <vector> // vector
#include <iterator> // ostream_iterator
#include <algorithm> // generate

#include "highfive/H5File.hpp"
#include "highfive/H5DataSet.hpp"



using namespace std;
using namespace HighFive;

template<typename T>
inline void print(const vector<T> &v, ostream& os = cout) {
    copy(v.cbegin(), v.cend(), ostream_iterator<T>(os, " "));
    os << endl;
}

int main() {
    const size_t n = 10;
    const char* testfile {"./testfile.h5"};
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

    // we create a new hdf5 file
    HighFive::File file(testfile, File::ReadWrite | File::Create | File::Truncate);

    // let's create a dataset of native integer with the size of the vector 'data'
    HighFive::DataSet dataset_vec1 = file.createDataSet<unsigned>("/vec1",  DataSpace::From(vec1));
    HighFive::DataSet dataset_vec2 = file.createDataSet<unsigned>("/vec2",  DataSpace::From(vec2));

    // let's write our vector of int to the HDF5 dataset
    dataset_vec1.write(vec1);
    dataset_vec2.write(vec2);


    cout << "Deserializing the vectors ..." << endl;

    decltype(vec1) vec3, vec4;
    dataset_vec1.read(vec3);
    dataset_vec2.read(vec4);


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
