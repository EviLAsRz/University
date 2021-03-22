import socket

HOST = 'localhost'
PORT = 1234

socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket_udp.sendto("Hola, juego Among Us.".encode("utf-8"),(HOST, PORT))

socket_udp.close()