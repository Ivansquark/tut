import socket

class Udp(object):
    def __init__(self, IP, PORT, receive = False):
        self.UDP_Socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)        
        if(receive):
            self.UDP_Socket.bind((IP, PORT))
        self.IP = IP
        self.PORT = PORT
    def send(self, data):
        self.UDP_Socket.sendto(data, (self.IP, self.PORT));
    def receive(self):
        data = self.UDP_Socket.recvfrom(1024);
        print("received message: %s", data)
