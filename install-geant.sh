#!/bin/sh

# Актуальная версия скрипта:
# http://hea.phys.msu.ru/static/data/install-geant.sh

# Чтобы запустить скрипт сделайте из этого текста файл с расширением .sh
# Поместите в папку для установки (рекомендуется ~/g4install)
# и запустите из терминала командой: sudo sh ./install-geant.sh

# =====================================================================
NAME_VERSION=geant4-v11.0.0
SHARE_NAME=Geant4-11.0.0
# Geant4-11.0.0 first released 10 December 2021
# При изменением версии проверьте что новая версия доступна по ссылке:
# http://cern.ch/geant4-data/releases/ВАША_ВЕРСИЯ.tar.gz
# =====================================================================

# Определение числа потоков
export N_THREADS=`lscpu | grep "CPU(s)" -m1 | cut -d: -f2 | tr ' ' '\0'`

# Установка зависимостей
sudo apt update
sudo apt install \
    build-essential binutils-gold gcc g++ cmake cmake-curses-gui \
    qt5-default \
    freeglut3-dev libqt5opengl5-dev \
    libglew-dev mesa-common-dev libglew1.5-dev libglm-dev \
    mesa-utils

# Загрузка исходников
wget http://cern.ch/geant4-data/releases/${NAME_VERSION}.tar.gz

# Распаковка исходников
tar xzf ${NAME_VERSION}.tar.gz
# Подготовка директории для сборки (build)
mkdir build
cd build

# Запуск cmake
cmake ../${NAME_VERSION} \
    -DCMAKE_INSTALL_PREFIX=$HOME/g4install \
    -DGEANT4_BUILD_MULTITHREADED=ON \
    -DGEANT4_INSTALL_DATA=ON \
    -DGEANT4_INSTALL_DATADIR=$HOME/g4install/data \
    -DGEANT4_USE_QT=ON \
    -DGEANT4_USE_SYSTEM_CLHEP=OFF \
    -DGEANT4_USE_SYSTEM_EXPAT=OFF \
    -DGEANT4_USE_SYSTEM_ZLIB=OFF

# Запуск make & make install
make -j$N_THREADS
sudo make install

# Конфигурирование .bashrc
echo "source $HOME/g4install/share/${SHARE_NAME}/geant4make/geant4make.sh" >> ~/.bashrc
