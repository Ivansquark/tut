import time
import pytcp

tcpClient = pytcp.Tcp("192.168.1.5", 55555, True)
x=0;
while True:
    x=x+1
    tcpClient.send(str.encode(str(x)))
    time.sleep(1)
