#!/bin/sh

# Чтобы запустить скрипт сделайте из этого текста файл с расширением .sh
# Поместите в папку для установки и запустите из терминала командой: sudo sh ./install-geant.sh

NAME_VERSION=geant4.10.07.p02
# Перед изменением версии проверьте что она доступна по адресу ниже:
# http://cern.ch/geant4-data/releases/ВАША_ВЕРСИЯ.tar.gz

# Актуальная версия скрипта
# http://hea.phys.msu.ru/static/data/install-geant.sh

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
# Подготовка директории для сборки (build)
tar xzf ${NAME_VERSION}.tar.gz
mkdir build
cd build

# Запуск cmake
# TODO: Добавить гибкое конфигурирование
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
echo "source $HOME/g4install/share/Geant4-10.7.1/geant4make/geant4make.sh" >> ~/.bashrc
