#!/bin/sh
# ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==*
## \~russian @brief Сценарий автоматической установки Geant4 для Ubuntu-like систем
## \~russian @date 14 апреля 2022
## \~russian @version 0.4
## \~russian @authors Сергей Золотов   aka @ignobillium ignobillium@yandex.ru
## \~russian @authors Андрей Маракулин aka @annndruha   a.p.marakulin@gmail.com
## 
## \~russian @example Чтобы установить Geant4, пропишите в терминале: sh ./install-geant.sh
## В начале исполнения скрипт попросит ввести пароль для установки недостающих зависимостей.
## Если вы просматриваете код скрипта из браузера, скопируйте содержимое
## в файл с расширением .sh и запустите: sh имя_вашего_файла.sh
# ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==*

# Актуальную версию скрипта можно найти по адресу:
# http://hea.phys.msu.ru/static/data/install-geant.sh

# ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==*

echo "===================================================================="
echo "==* Checking script version                                         "
echo "==*                                                              *=="

export VERSION=0.4 # Текущая версия скрипта

# TODO обработка ошибки если не удалось загрузить данные из интернета
# Сравниваем её с актуальной, по необходимости загружаем новую обновляем
export API_REQUEST=http://hea.phys.msu.ru/api/script_version
export ACTUAL_VERSION=$(curl -f "$API_REQUEST")

echo "Current version: $VERSION"
echo "Actual version:  $ACTUAL_VERSION"

if [ $VERSION != $RESULT ]; then
    echo "===================================================================="
    echo "==* Download and execute actual script                              "
    echo "==*                                                              *=="
    curl http://hea.phys.msu.ru/static/data/install-geant.sh | sh
    exit 0  
fi

# ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==* ==*

NAME_VERSION=geant4-v11.0.0
SHARE_NAME=Geant4-11.0.0

# Geant4-11.0.0 first released 10 December 2021
# При изменением версии проверьте что новая версия доступна по ссылке:
# http://cern.ch/geant4-data/releases/NAME_VERSION.tar.gz


# Установка (недостающих) зависимостей
echo "====================================================================="
echo "==* G4 ${NAME_VERSION} installation starting... ====================="
echo "==* Installing required packages...             ====================="
echo "==*                                                               *=="

# TODO загрузить репозитории на hea.phys.msu.ru как на зеркало
sudo apt update
sudo apt install                                            \
    libglm-dev                                               \
    cmake cmake-curses-gui                                    \
    mesa-utils mesa-common-dev                                 \
    build-essential binutils-gold gcc g++                       \
    freeglut3-dev libglew-dev libqt5opengl5-dev   \
    qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools             \
    > log.txt

# TODO загрузить исходники на hea.phys.msu.ru как на зеркало
# Скачиваем исходники Geant4
echo "===================================================================="
echo "==* Downloading Geant4 sources from cern.ch... ====================="
echo "==*                                                              *=="

mkdir $HOME/g4install
cd $HOME/g4install

if [ -f "${NAME_VERSION}.tar.gz" ]; then
    echo "File ${NAME_VERSION}.tar.gz already exists. No need to download."
else 
    wget http://cern.ch/geant4-data/releases/${NAME_VERSION}.tar.gz
    tar xzf ${NAME_VERSION}.tar.gz
fi

# Сборка исходников
echo "===================================================================="
echo "==* Configuring Geant4 via CMake                                    "
echo "==*                                                              *=="

if [ ! -d "build" ]; then
    mkdir build
fi
cd build

cmake ../${NAME_VERSION} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$HOME/g4install \
    -DGEANT4_INSTALL_DATA=ON \
    -DGEANT4_INSTALL_DATADIR=$HOME/g4install/data \
    -DGEANT4_BUILD_MULTITHREADED=ON \
    -DGEANT4_USE_QT=ON \
    -DGEANT4_USE_SYSTEM_CLHEP=OFF \
    -DGEANT4_USE_SYSTEM_EXPAT=OFF \
    -DGEANT4_USE_SYSTEM_ZLIB=OFF \
    -DGEANT4_INSTALL_EXAMPLES=OFF

echo "===================================================================="
echo "==* Building Geant4                                                 "
echo "==*                                                              *=="

# Определение числа потоков
export N_THREADS=`lscpu | grep "CPU(s)" -m1 | cut -d: -f2 | tr ' ' '\0'`

# Сборка
make -j$N_THREADS install

echo "===================================================================="
if [ -d "$HOME/g4install/share/${SHARE_NAME}" ]; then
    echo "==* Installation completed successfully ============================"
    echo "==*                                                              *=="
    # Пишем в .bashrc sh-срипт, задающий необходимые для работы Geant4 переменные окружения
    echo "source $HOME/g4install/share/${SHARE_NAME}/geant4make/geant4make.sh" >> ~/.bashrc

    echo "===================================================================="
    echo "==* Removing temporal files ========================================"
    echo "==*                                                              *=="
    rm    -f $HOME/g4install/${NAME_VERSION}.tar.gz && echo "rm -f $HOME/g4install/${NAME_VERSION}.tar.gz"
    rm -r -f $HOME/g4install/${NAME_VERSION} && echo "rm -r -f $HOME/g4install/${NAME_VERSION}"
    rm -r -f $HOME/g4install/build && echo "rm -r -f $HOME/g4install/build"
else
    # TODO добавить лог, к которому отсылать пользователя в случае возникновения ошибки 
    echo "==* An error occurs while installation process  ===================="
    echo "==*                                                              *=="
fi
echo "===================================================================="
