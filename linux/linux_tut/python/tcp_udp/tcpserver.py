import pytcp

tcp = pytcp.Tcp("192.168.1.200", 55555)

while True:
    x = tcp.read();
    if x:
        print(str(x))
