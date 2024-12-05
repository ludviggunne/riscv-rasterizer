#!/usr/bin/env bash

make clean
rm -rf project-code
mkdir -p project-code

for file in lib include src Makefile Makefile.dtekv \
  Makefile.models Makefile.host scripts readme.txt res; do
  cp -r $file project-code
done

zip -r project-code.zip project-code

rm -rf project-code
