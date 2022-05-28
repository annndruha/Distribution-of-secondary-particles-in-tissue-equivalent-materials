cd ..
rm -r build
mkdir build

cp linac_gamma_hist.txt build/linac_gamma_hist.txt
cp linac_e-_hist.txt build/linac_e-_hist.txt
cp linac_e+_hist.txt build/linac_e+_hist.txt
cp linac_neutron_hist.txt build/linac_neutron_hist.txt
cd build
cmake ..
make
./main