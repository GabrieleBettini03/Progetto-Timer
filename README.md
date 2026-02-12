# Prerequisiti:



CMake 3.16+



MinGW64 (1310)



Prima di eseguire il programma:



* Aprire cmd in {percorso\_della\_cartella\_del\_progetto}/Progetto-Timer



* Eseguire i seguenti comandi:



mkdir build

cd build

cmake -G "MinGW Makefiles" ..

cmake --build .



(Alternativamente fare il build da CLion e poi da cmd nella cartella di build eseguire il resto dei comandi)



..\\Qt\\6.10.2\\mingw\_64\\bin\\windeployqt.exe Progetto\_Timer.exe

..\\Qt\\6.10.2\\mingw\_64\\bin\\windeployqt.exe UnitTesting\_Timer.exe

