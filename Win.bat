make clean

cd build

cmake .. -G "MinGW Makefiles"
make
copy ..\libs\Windows\*.dll .\
xcopy /E /I ..\rsc .\rsc
Main.exe

cd ..
