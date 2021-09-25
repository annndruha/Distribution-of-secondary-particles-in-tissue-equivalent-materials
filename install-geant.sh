# Актуальная версия скрипта
# http://hea.phys.msu.ru/static/data/install-geant.sh

# Preparing: определениечисла потоков
export N_THREADS=`lscpu | grep "CPU(s)" -m1 | cut -d: -f2 | tr ' ' '\0'`

# Preparing: установить всякие зависимости
sudo apt update
sudo apt install \
    build-essential binutils-gold gcc g++ cmake cmake-curses-gui \
    qt5-default \
    freeglut3-dev libqt5opengl5-dev \
    libglew-dev mesa-common-dev libglew1.5-dev libglm-dev \
    mesa-utils

# Загрузить исходники
# TODO Версия / имя джанта через переменную конфигурации
wget http://cern.ch/geant4-data/releases/geant4.10.07.p01.tar.gz
# Распаковать исходники

# Подготовить директории для сборки
tar xzf geant4.10.07.p01.tar.gz
mkdir build
cd build

# Запустить cmake
# TODO Добавить гибкое конфигурирование
cmake ../geant4.10.07.p01 \
    -DCMAKE_INSTALL_PREFIX=$HOME/g4install \
    -DGEANT4_BUILD_MULTITHREADED=ON \
    -DGEANT4_INSTALL_DATA=ON \
    -DGEANT4_INSTALL_DATADIR=$HOME/g4install/data \
    -DGEANT4_USE_QT=ON \
    -DGEANT4_USE_SYSTEM_CLHEP=OFF \
    -DGEANT4_USE_SYSTEM_EXPAT=OFF \
    -DGEANT4_USE_SYSTEM_ZLIB=OFF

# Запустить make & make install
make -j$N_THREADS
sudo make install

# Прописать конфигурации в .bashrc
echo "source $HOME/g4install/share/Geant4-10.7.1/geant4make/geant4make.sh" >> ~/.bashrc
