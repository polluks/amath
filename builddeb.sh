#! /bin/sh

# Build a debian package for amd64

rm -Rf amath

# Build
sh configure
make clean
make
mv amath amath.tmp
make clean

# Create filesystem layout
rm -Rf amath

mkdir -p amath/DEBIAN
mkdir -p amath/usr/bin
mkdir -p amath/usr/share/doc/amath
mkdir -p amath/usr/local/share/amath

mv amath.tmp amath/usr/bin/amath

# Copy documentation
cp LICENSE amath/usr/share/doc/amath/
cp HISTORY amath/usr/share/doc/amath/
cp build/debian/README amath/usr/share/doc/amath/

# Copy scripts
cp script/* amath/usr/local/share/amath/

# Make the package
cp build/debian/control-amd64 amath/DEBIAN/control
dpkg-deb --build amath
mv amath.deb amath-1.6.3_amd64.deb

# Build a debian package for i386

rm -Rf amath

# Build
sh configure -m32
make clean
make
mv amath amath.tmp
make clean

# Create filesystem layout
rm -Rf amath

mkdir -p amath/DEBIAN
mkdir -p amath/usr/bin
mkdir -p amath/usr/share/doc/amath
mkdir -p amath/usr/local/share/amath

mv amath.tmp amath/usr/bin/amath

# Copy documentation
cp LICENSE amath/usr/share/doc/amath/
cp HISTORY amath/usr/share/doc/amath/
cp build/debian/README amath/usr/share/doc/amath/

# Copy scripts
cp script/* amath/usr/local/share/amath/

# Make the package
cp build/debian/control-i386 amath/DEBIAN/control
dpkg-deb --build amath
mv amath.deb amath-1.6.3_i386.deb

# Cleanup
#rm -Rf amath
