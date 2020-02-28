#!/bin/bash

## Primary values for customizing
BASHDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
INSTALLDIR="/usr/local/opencv-cpu"
QTDIR="$HOME/Qt5.12.3/5.12.3/gcc_64"
SOURCEDIR="$HOME/git/opencv"

echo "Making essential directories ..."
mkdir -p "$SOURCEDIR"

## declare an array variable of strings
declare -a arr=("opencv" 
                "opencv_contrib"
                "opencv_extra"
                "opencv_3rdparty"
                "training_toolbox_tensorflow"
                "cvat"
                "dldt"
                "open_model_zoo"
                "ade"
                "opencv_attic"
                )

## loop through the above array
for i in "${arr[@]}"
do
   echo "downloading/updating $i ..."
   if [ -d "$SOURCEDIR/$i" ]; then
    git -C "$SOURCEDIR/$i" pull &
   else
    git clone "https://github.com/opencv/$i" "$SOURCEDIR/$i" &
   fi
done

wait

echo "Building opencv in $BASHDIR"

# The cuda seprate compiler is an option for windows and does not work in Linux environment and will cause mulitple definition error
# One must change the complete compiler to version compatible with cuda
# inorder to find which version is compatible with cuda first run without changing the compiler and log output will let you know

cmake \
-DENABLE_CXX11=ON \
-DCMAKE_BUILD_TYPE:STRING="Release" \
-DCMAKE_INSTALL_PREFIX:PATH="$INSTALLDIR" \
-DOPENCV_EXTRA_MODULES_PATH:PATH="../../opencv_contrib/modules" \
-DOPENCV_TEST_DATA_PATH:PATH="../../opencv_extra/testdata" \
-DOPENCV_ENABLE_NONFREE:BOOL="1" \
-DENABLE_FAST_MATH:BOOL="1" \
-DBUILD_DOCS:BOOL="1" \
-DBUILD_EXAMPLES:BOOL="1" \
-DINSTALL_C_EXAMPLES:BOOL="1" \
-DINSTALL_PYTHON_EXAMPLES:BOOL="1" \
-DOPENCV_PYTHON3_VERSION:BOOL="1" \
-DWITH_INF_ENGINE=ON \
-DWITH_OPENGL:BOOL="1" \
-DWITH_CUDA:BOOL=0 \
-DCUDA_VERBOSE_BUILD:BOOL=0 \
-DCMAKE_C_COMPILER:FILEPATH="/usr/bin/gcc-7" \
-DCMAKE_C_COMPILER_RANLIB:FILEPATH="/usr/bin/gcc-ranlib-7" \
-DCMAKE_C_COMPILER_AR:FILEPATH="/usr/bin/gcc-ar-7" \
-DCMAKE_CXX_COMPILER:FILEPATH="/usr/bin/g++-7" \
-DCMAKE_CXX_COMPILER_RANLIB:FILEPATH="/usr/bin/gcc-ranlib-7" \
-DCMAKE_CXX_COMPILER_AR:FILEPATH="/usr/bin/gcc-ar-7" \
-DCUDA_FAST_MATH:BOOL=0 \
-DWITH_QT:BOOL="1" \
-DQT_QMAKE_EXECUTABLE:FILEPATH="$QTDIR/bin/qmake" \
-DQt5Core_DIR:PATH="$QTDIR/lib/cmake/Qt5Core" \
-DQt5Gui_DIR:PATH="$QTDIR/lib/cmake/Qt5Gui" \
-DQt5Widgets_DIR:PATH="$QTDIR/lib/cmake/Qt5Widgets" \
-DQt5Concurrent_DIR:PATH="$QTDIR/lib/cmake/Qt5Concurrent" \
-DQt5Test_DIR:PATH="$QTDIR/lib/cmake/Qt5Test" \
-DQt5OpenGL_DIR:PATH="$QTDIR/lib/cmake/Qt5OpenGL" \
-DANT_EXECUTABLE:FILEPATH="/usr/bin/ant" \
-DOPENCV_GENERATE_PKGCONFIG:BOOL=1 \
"$SOURCEDIR/opencv"

echo "Start making opencv ..."
make -j7

echo "Building the documents ..."
cd ./doc/
make -j7 doxygen

echo "Execute sudo make install if you want to install the build objects to directories"
