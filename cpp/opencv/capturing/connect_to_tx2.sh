#!/bin/bash
gst-launch-1.0 -e nvcamerasrc ! 'video/x-raw(memory:NVMM),width=640, height=480, framerate=30/1, format=NV12' ! nvvidconv flip-method=2 ! nvegltransform ! nveglglessink

#gst-launch-1.0 -ev nvcamerasrc ! nvvidconv ! ximagesink
#gst-launch-1.0 -ev nvcamerasrc ! nvoverlaysink