import pytcp

tcp = pytcp.Tcp("192.168.0.106", 44444)

while True:
    x = tcp.read();
    if x:
        print(str(x))
