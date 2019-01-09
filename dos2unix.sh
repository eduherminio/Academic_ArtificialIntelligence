#!/bin/bash
find *.sh | xargs dos2unix
find *.h | xargs dos2unix
find *.cpp | xargs dos2unix
find *.txt | xargs dos2unix
