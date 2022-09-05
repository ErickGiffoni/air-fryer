#!/bin/bash

rm */*.gch
gcc fryItAll.c uart/* pid/* lcd/* crc/* gpio/* -lwiringPi -lpthread