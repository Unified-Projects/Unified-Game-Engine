cd build

cmake .. -G "MinGW Makefiles"
make
copy ..\libs\Windows\*.dll .\
xcopy /E /I /Y ..\rsc .\rsc
Main.exe

cd ..
