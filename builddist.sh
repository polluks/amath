#!/bin/sh

rm -f amath.lha
rm -Rf amath
rm -Rf dist
mkdir dist

GCC295=Y

REGTEST=N 
./configure -m68000 m68k-amigaos- -noixemul
make
mv amath dist/amath.000
make clean
./configure -m68020 m68k-amigaos- -noixemul
make
mv amath dist/amath.020
make clean
./configure -m68030 m68k-amigaos- -noixemul
make
mv amath dist/amath.030
make clean
./configure -m68040 m68k-amigaos- -noixemul
make
mv amath dist/amath.040
make clean
./configure -m68060 m68k-amigaos- -noixemul
make
mv amath dist/amath.060
make clean
./configure "-m68020 -m68881" m68k-amigaos- -noixemul
make
mv amath dist/amath.020f
make clean
./configure "-m68030 -m68881" m68k-amigaos- -noixemul
make
mv amath dist/amath.030f
make clean

REGTEST=Y
./configure -m68000 m68k-amigaos- -noixemul
make
mv amath dist/amath-test.000
make clean
./configure -m68020 m68k-amigaos- -noixemul
make
mv amath dist/amath-test.020
make clean
./configure -m68030 m68k-amigaos- -noixemul
make
mv amath dist/amath-test.030
make clean
./configure -m68040 m68k-amigaos- -noixemul
make
mv amath dist/amath-test.040
make clean
./configure -m68060 m68k-amigaos- -noixemul
make
mv amath dist/amath-test.060
make clean
./configure "-m68020 -m68881" m68k-amigaos- -noixemul
make
mv amath dist/amath-test.020f
make clean
./configure "-m68030 -m68881" m68k-amigaos- -noixemul
make
mv amath dist/amath-test.030f
make clean

cd dist
touch hashkeys
sha1sum amath.000 >>hashkeys
sha1sum amath.020 >>hashkeys
sha1sum amath.030 >>hashkeys
sha1sum amath.040 >>hashkeys
sha1sum amath.060 >>hashkeys
sha1sum amath.020f >>hashkeys
sha1sum amath.030f >>hashkeys
sha1sum amath-test.000 >>hashkeys
sha1sum amath-test.020 >>hashkeys
sha1sum amath-test.030 >>hashkeys
sha1sum amath-test.040 >>hashkeys
sha1sum amath-test.060 >>hashkeys
sha1sum amath-test.020f >>hashkeys
sha1sum amath-test.030f >>hashkeys
sha256sum amath.000 >>hashkeys
sha256sum amath.020 >>hashkeys
sha256sum amath.030 >>hashkeys
sha256sum amath.040 >>hashkeys
sha256sum amath.060 >>hashkeys
sha256sum amath.020f >>hashkeys
sha256sum amath.030f >>hashkeys
sha256sum amath-test.000 >>hashkeys
sha256sum amath-test.020 >>hashkeys
sha256sum amath-test.030 >>hashkeys
sha256sum amath-test.040 >>hashkeys
sha256sum amath-test.060 >>hashkeys
sha256sum amath-test.020f >>hashkeys
sha256sum amath-test.030f >>hashkeys
cd ..

make amigacatalogs

#cp amath.readme dist/
cp LICENSE dist/
cp COPYRIGHT dist/
cp HISTORY dist/

mkdir dist/script
cp script/* dist/script/
date -u >dist/buid_date 

mv dist amath
#lha-ac a amath.lha amath
