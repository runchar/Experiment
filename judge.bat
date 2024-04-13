@echo off

setlocal EnableDelayedExpansion

@REM set g++="C:\MinGW\bin\g++.exe"
@REM set linker="C:\MinGW\bin\g++.exe"

g++ main.cpp -std=c++2b -o main.exe
g++ test.cpp -std=c++2b -o test.exe

main.exe > main_output.txt
test.exe > test_output.txt

fc /w main_output.txt test_output.txt > compare_result.txt

if %errorlevel% == 0 (
    echo s
) else (
    echo w
    type compare_result.txt
)

pause

del main.exe test.exe main_output.txt test_output.txt compare_result.txt
