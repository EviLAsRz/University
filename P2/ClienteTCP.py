#Cliente TCP

# 1) Importamos el socket TCP

import socket
HOST = 'localhost' 
PORT = 2000
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #SOCK_STREAM indica conexión TCP
                                                      #AF_INET simboliza que podemos usar el socket en diferentes maquinas

# 2) Cliente se conecta a un servidor que esté aceptando conexiones

sock.connect((HOST,PORT))

# 3) Envia un mensaje para el socket

sock.send("Soy el cliente".encode("utf-8")) # utf-8 es la codificacion para poder codificar el mensaje

# 4) Recibe el mensaje del servidor del puerto 1024 y lo muestra

mensaje = sock.recv(1024)
print("Mensaje recibido:["+mensaje.decode("utf-8")+"]del servidor")

# 5) Cierra la conexion con el servidor

sock.close()