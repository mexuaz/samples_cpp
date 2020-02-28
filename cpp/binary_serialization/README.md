# samples_cpp

## C++ Serialization


### Boost serializtion

#### CONS

* Only C++
* Needs to link to boost serialization components

#### PROS

* Fastest
* Simple to implement
* Works very good with stl
* Does not require to compiler scheme file
* Serialize to multiple formats (binary, text, xml and ...)


### Google Flatbuffers


#### CONS

* Offset size is limited to signed integer (2^31-1)
* Difficult to modify serialized object

#### PROS

* Cross language
* Very fast
* Simple to implement
* Can be use by simply adding a few source files


### Google Protobuffers

#### CONS

* Requiers pthraed
* Need to install the library and build agains objects
* More complicated

#### PROS

* Cross language
* fast
* Offset size is as big as unsigned long
* More professional options