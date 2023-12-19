import pyudp

udp = pyudp.Udp("127.0.0.1", 55555, True)

while(True):
    udp.receive()
