@echo off

python big_integer_test\make.py

@REM g++ -o -std=c++2b main main.cpp
output\main.exe

python big_integer_test\compare.py

pause
