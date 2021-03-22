
# 1) Se importa el socket TCP

import socket
HOST = 'localhost'
PORT = 2000

socketServidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  #SOCK_STREAM indica conexión TCP
                                                                    #AF_INET simboliza que podemos usar el socket en diferentes maquinas

# 2) Asociamos el socket al puerto

socketServidor.bind((HOST,PORT))

# 3) Servidor escucha las peticiones de conexion de los clientes, puediendo deja hasta 1 cliente en espera

socketServidor.listen(1)
print("En espera")

# 4) Servidor acepta conexion con cliente, devolviendo un socket para tenderle (s_cliente) y su respectiva hebra para atenderlo

socket_cliente,addr =socketServidor.accept()

# 5) La hebra espera a recibir el mensaje del cliente, y posteriormente lo imprime

mensaje = socket_cliente.recv(1024)
print("Mensaje recibido:["+ mensaje.decode("utf-8")+"]del cliente con direccion "+ str(addr))

# 6) Sercidor envia mensaje al cliente

socket_cliente.send("Hola cliente,soy el servidor".encode("utf-8"))

# 7) Servidor cierra la conexion , y por lo tanto el socket, con el cliente, después de que este lo haya solicitado

socket_cliente.close()

# 8) Servidor cierra conexion

socketServidor.close()