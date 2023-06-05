import time
import pyudp

localIP     = "127.0.0.1"
localPort   = 55555

print("UDP server sending")
address = (localIP, localPort)
x=0;
udp = pyudp.Udp(localIP,localPort, False)

while(True):
    x=x+1;
    bytesToSend = str.encode(str(x))
    udp.send(bytesToSend)
    time.sleep(1)
