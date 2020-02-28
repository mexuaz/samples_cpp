# Google flatbuffers

## Install on computer
* $ git clone https://github.com/google/flatbuffers
* $ mkdir build
* $ cd build
* $ cmake -G "Unix Makefiles" -DCMAKE\_BUILD\_TYPE=Release ../flatbuffers
* $ make
Will install to /usr/local by default
* $ sudo make install


## Instructions to use scheme file for C++
* create scheme file with extension .fbs
* $ flatc --cpp test_kcd.fbs


## References
* [Main](https://google.github.io/flatbuffers/)
* [CPP](https://google.github.io/flatbuffers/md__cpp_usage.html)
* [Tutorial](https://google.github.io/flatbuffers/flatbuffers_guide_tutorial.html)
* [git](https://github.com/google/flatbuffers)
* [Schema](https://google.github.io/flatbuffers/md__schemas.html)