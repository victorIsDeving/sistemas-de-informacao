# Inicializando peers
peer1 = Peer('localhost', 5000)
peer2 = Peer('localhost', 5001)
peer3 = Peer('localhost', 5002)

# Conectando peers
peer1.connect_to_peer('localhost', 5001)
peer2.connect_to_peer('localhost', 5000)
peer2.connect_to_peer('localhost', 5002)
peer3.connect_to_peer('localhost', 5001)

# Adicionando arquivos aos peers
peer1.files.append('file1.txt')
peer2.files.append('file2.txt')

# Iniciando peers
peer1.start()
peer2.start()
peer3.start()

# Exemplo de busca
# Você precisaria implementar uma forma de enviar uma mensagem de busca a partir de um cliente, mas aqui está um exemplo simples:
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 5000))
client_socket.send('SEARCH file2.txt'.encode())
response = client_socket.recv(1024).decode()
print(response)  # Deverá imprimir 'FOUND localhost:5001 file2.txt'
client_socket.close()
