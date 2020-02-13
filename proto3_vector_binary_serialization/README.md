# Google Protobuf

## Install on computer
Download the latest package from here: 
<https://github.com/protocolbuffers/protobuf/releases/>

or download the proper version from here: 
<https://github.com/protocolbuffers/protobuf/releases/tag/v3.9.1>

$ `wget https://github.com/protocolbuffers/protobuf/releases/download/v3.9.1/protobuf-cpp-3.9.1.tar.gz`

$ `gnuzip protobuf-cpp-3.9.1.tar.gz`

$ `cd protobuf-3.9.1`

$ `./configure`

$ `make -j8`

$ `sudo make install`

$ `sudo ldconfig # refresh shared library cache.`

## For Compute Canada

$ `module load protobuf/3.9.1`

## For python3 bindings

$ `pip3 install protobuf3==3.9.1`

$ `pip3 install protobuf3`

## Debian Packages

\# `apt install libprotobuf-dev libprotoc-dev -y`

## Validate the installation by:

$ `protoc --version`

libprotoc 3.9.1

## Compile proto file to generate C++ and Python3 files

$ `protoc --cpp_out=. --python3_out=. foo.proto`