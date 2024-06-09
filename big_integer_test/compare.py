def compare_files(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        # 逐行比较两个文件内容
        line_number = 0
        tag = 1
        for line1, line2 in zip(f1, f2):
            line_number += 1
            if line1 != line2:
                print(f"文件 {file1}"
                      f" 的第 {line_number} 行与文件 {file2} 的第 {line_number} 行不同：")
                print(f"{file1}：{line1.strip()}")
                print(f"{file2}：{line2.strip()}")
                tag = 0
        # 如果文件长度不同，则文件不相同
        # if f1.read() != f2.read():
        #     tag = 0
    return tag

file1_path = "output.txt"
file2_path = "outputs.txt"

if compare_files(file1_path, file2_path)==1:
    print("same")
else:
    print("different")
