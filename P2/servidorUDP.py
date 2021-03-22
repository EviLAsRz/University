#importamos el modulo socket
import socket

HOST = 'localhost'
PORT = 1234

socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket_udp.bind((HOST, PORT))                                   #conectamos el host y el puerto 

print("En espera...")
mens,addr = socket_udp.recvfrom(1024)                           #cadena para almacenar el mensaje y los datos recibido del cliente (1024 bytes)

print("Recibo el mensaje: " + str(mens.decode("utf-8")))        #imprimo el mensaje recibido junto a la ip y puerto del cliente
print("IP cliente: " + str(addr[0]))
print("Puerto cliente: " + str(addr[1]))

socket_udp.close()      #cierre de conexion
