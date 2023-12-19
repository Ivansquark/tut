import time
import pytcp

tcpClient = pytcp.Tcp("127.0.0.1", 44444, 1)
x=0;
while True:
    x=x+1
    tcpClient.send(str.encode(str(x)))
    time.sleep(1)
