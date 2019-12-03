#!/bin/bash

find . -type f -name \*.o -exec rm {} \;
find . -type f -name \*.exe -exec rm {} \;