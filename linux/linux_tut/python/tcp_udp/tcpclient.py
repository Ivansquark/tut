import time
import pytcp
import fileinput

tcpClient = pytcp.Tcp("192.168.1.5", 55555, True)
x=0;
while True:
    print("non block");
    for line in fileinput.input():
       if(line == 'exit\n'):
           print("opa");
           exit();
       tcpClient.send(str.encode(str(line)))
    x = tcpClient.read();
    if x:
        print(str(x))
        
        #x=x+1
        #//tcpClient.send(str.encode(str(x)))
        #time.sleep(1)
