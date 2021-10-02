# Geant4 Домашние задания

**Репозиторий для выполнения домашних заданий по Geant4**

* [Домашнее задание 1](https://github.com/Annndruha/Geant4/blob/v1.0.0/B1/src/B1DetectorConstruction.cc) от 16.09.21 - Расположить бетонный куб на поверхности графитового параллилепипеда.
* [Домашнее задание 2](https://github.com/Annndruha/Geant4/blob/v2.0.0/B1/vis.mac#L19) от 23.09.21 - Изменить цвета треков частиц и цвета объёмов через макросы визуализации.
* [Домашнее задание 3](https://github.com/Annndruha/Geant4/blob/v3.0.0/model/DosePlotter.ipynb) от 30.09.21 - Снять данные и построить гистограмму дозового распределения.


**Tricks**

* `scripts/autobuild_full.sh` - полностью пересобирает проект: удаляет build, выполняет cmake, make, запуск. Скрипт запускается руками.
* `scripts/autobuild.sh` - пересобирает при существующей папке buiild, выполняет cmake, make, запуск
* `.vscode/tasks.json` запускает `autobuild.sh` через хоткей `ctrl+shift+b`
* `.vscode/c_cpp_properties.json`- настраивает пути к заголовочным файлам джанта, чтобы была корректная подсветка синтаксиса.
* `install-geant.sh` - установка geant4.VV.VV.pVV в полностью автоматическом режиме (от 5 мин до 30 мин)
