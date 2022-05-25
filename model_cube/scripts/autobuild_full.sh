cd ..
rm -r build
mkdir build
cp linac_e_hist.dat build/linac_e_hist.dat
cp linac_gamma_hist.dat build/linac_gamma_hist.dat
cd build
cmake ..
make
./main