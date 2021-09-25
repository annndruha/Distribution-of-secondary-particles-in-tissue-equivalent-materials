# Geant4 Домашние задания

**Репозиторий для выполнения домашних заданий по Geant4**

* [Домашнее задание 1](https://github.com/Annndruha/Geant4/blob/v1.0.0/B1/src/B1DetectorConstruction.cc) от 16.09.21 - Расположить бетонный куб на поверхности графитового параллилепипеда.


**Tricks**

* `.vscode/c_cpp_properties.json` настраивает пути к заголовочным файлам джанта, чтобы была корректная подсветка синтаксиса
* `autobuild.sh` пересобирает проект: удаляет build, выполняет cmake, make, запуск
* `.vscode/tasks.json` запускает `autobuild.sh` через хоткей ctrl+shift+b