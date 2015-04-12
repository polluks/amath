#!/bin/sh

rm -f amath.lha
rm -Rf amath
rm -Rf dist
mkdir dist

./configure AMIGA NOTEST -m68000
make
mv amath dist/amath.000
make clean
./configure AMIGA NOTEST -m68020
make
mv amath dist/amath.020
make clean
./configure AMIGA NOTEST -m68030
make
mv amath dist/amath.030
make clean
./configure AMIGA NOTEST -m68040
make
mv amath dist/amath.040
make clean
./configure AMIGA NOTEST -m68060
make
mv amath dist/amath.060
make clean
./configure AMIGA NOTEST "-m68020 -m68881"
make
mv amath dist/amath.020f
make clean
./configure AMIGA NOTEST "-m68030 -m68881"
make
mv amath dist/amath.030f
make clean
./configure AMIGA TEST -m68000
make
mv amath dist/amath-test.000
make clean
./configure AMIGA TEST -m68020
make
mv amath dist/amath-test.020
make clean
./configure AMIGA TEST -m68030
make
mv amath dist/amath-test.030
make clean
./configure AMIGA TEST -m68040
make
mv amath dist/amath-test.040
make clean
./configure AMIGA TEST -m68060
make
mv amath dist/amath-test.060
make clean
./configure AMIGA TEST "-m68020 -m68881"
make
mv amath dist/amath-test.020f
make clean
./configure AMIGA TEST "-m68030 -m68881"
make
mv amath dist/amath-test.030f
make clean

cd dist
touch hashkeys
sha1 amath.000 >>hashkeys
sha1 amath.020 >>hashkeys
sha1 amath.030 >>hashkeys
sha1 amath.040 >>hashkeys
sha1 amath.060 >>hashkeys
sha1 amath.020f >>hashkeys
sha1 amath.030f >>hashkeys
sha1 amath-test.000 >>hashkeys
sha1 amath-test.020 >>hashkeys
sha1 amath-test.030 >>hashkeys
sha1 amath-test.040 >>hashkeys
sha1 amath-test.060 >>hashkeys
sha1 amath-test.020f >>hashkeys
sha1 amath-test.030f >>hashkeys
sha256 amath.000 >>hashkeys
sha256 amath.020 >>hashkeys
sha256 amath.030 >>hashkeys
sha256 amath.040 >>hashkeys
sha256 amath.060 >>hashkeys
sha256 amath.020f >>hashkeys
sha256 amath.030f >>hashkeys
sha256 amath-test.000 >>hashkeys
sha256 amath-test.020 >>hashkeys
sha256 amath-test.030 >>hashkeys
sha256 amath-test.040 >>hashkeys
sha256 amath-test.060 >>hashkeys
sha256 amath-test.020f >>hashkeys
sha256 amath-test.030f >>hashkeys
cd ..

cp amath.readme dist/
cp LICENSE dist/
cp COPYRIGHT dist/
cp HISTORY dist/

mkdir dist/script
cp script/* dist/script/
date -u >dist/buid_date 

mv dist amath
lha-ac a amath.lha amath
