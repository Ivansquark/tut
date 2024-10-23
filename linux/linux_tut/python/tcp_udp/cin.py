import fileinput

for line in fileinput.input():
    if(line == 'exit\n'):
        print("opa");
        exit();
    print(line);

