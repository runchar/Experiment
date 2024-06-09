import subprocess
import os


data_make_path = r"./big_integer_test/make.py"
data_compare_path=r"./big_integer_test/compare.py"
run_cpp_path=r"./main.cpp"

subprocess.call(["python", data_make_path])

print("random data has been generated\n")

compile_command = ["g++", "-Wall", "-Wextra", "-g3", "-std=c++2b", "main.cpp", "-o", "main"]
subprocess.run(compile_command)

os.system('cls')

print("running...\n")

subprocess.run("main")

print("comparing...\n")

# subprocess.call(["python", data_compare_path])
print("compare result: ")
output = subprocess.run(["python", data_compare_path])


# print(output)

os.remove("main.exe")
os.remove("inputs.txt")
os.remove("outputs.txt")
os.remove("output.txt")

