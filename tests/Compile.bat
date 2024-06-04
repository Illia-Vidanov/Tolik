g++ -g main.cpp -std=c++17 -Wall --max-errors=10 -Wshadow ^
-IC:\Programming\c++\Tolik\libs\gcem ^
-IC:\Programming\c++\Tolik\libs\Eigen\Eigen ^
-IC:/Programming/c++/Tolik/src ^
-LC:/Programming/c++/Tolik/build/lib -lTolik ^
-o main.exe

if errorlevel 1 goto end
main.exe
:end