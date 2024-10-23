import socket
import os

class Tcp(object):
    Client = False
    def __init__(self, IP, PORT, client = False):
        self.IP = IP
        self.PORT = PORT
        self.tcpSock = socket.socket(family=socket.AF_INET,
                                     type=socket.SOCK_STREAM);
        self.tcpSock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.Client = client
        if(client == True):            
            self.tcpSock.connect((IP, PORT))
        else:
            self.tcpSock.bind((IP, PORT))
            # get max number of connections
            self.tcpSock.listen(1)
            self.conn, self.addr = self.tcpSock.accept()
    def __del__(self):
        print('Destructor called, Employee deleted.')
        port = PORT
        converted_port = str(PORT)
        string = PORT + "/tcp"
        cmd = "echo 1 | sudo -S fuser -k " + string
        #cmd = "echo 1 | sudo -S fuser -k PORT/tcp"
        returned_value = os.system(cmd)  # returns the exit code in unix
        print('returned value:', returned_value)

    def send(self, data):
        self.tcpSock.sendall(data)
    def read(self):
        while True:
            if self.Client:
                data = self.tcpSock.recv(1024)
            else:
                data = self.conn.recv(1024)
            if not data:
                break
            else:
                return data
        return 0    
    def close(self):
        self.conn.close()
