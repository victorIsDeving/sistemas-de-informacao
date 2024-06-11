import threading
import time
from class_peer import Peer


def start_peer(peer):
    peer.start()


def main():
    # Inicializando os peers
    peer1 = Peer('localhost', 5000, known_neighbors=[('localhost', 5001)])
    peer2 = Peer('localhost', 5001, known_neighbors=[('localhost', 5000), ('localhost', 5002)])
    peer3 = Peer('localhost', 5002, known_neighbors=[('localhost', 5001)])

    # Adicionando arquivos aos peers
    peer3.files['key1'] = 'value1'  # Peer3 possui a chave 'key1'

    # Iniciando os peers em threads separadas
    print(f"Starting {peer1.host}:{peer1.port}")
    threading.Thread(target=start_peer, args=(peer1,)).start()
    time.sleep(2)
    print(f"Starting {peer2.host}:{peer2.port}")
    threading.Thread(target=start_peer, args=(peer2,)).start()
    time.sleep(2)
    print(f"Starting {peer3.host}:{peer3.port}")
    threading.Thread(target=start_peer, args=(peer3,)).start()
    time.sleep(2)

    # Executando a busca por flooding no peer1
    peer1.search('FLOOD')

    # Aguardando para garantir que a busca foi concluída
    time.sleep(5)

    # Exibindo as estatísticas de cada peer
    print(f"Statistics {peer1.host}:{peer1.port}")
    peer1.show_statistics()
    print(f"Statistics {peer2.host}:{peer2.port}")
    peer2.show_statistics()
    print(f"Statistics {peer3.host}:{peer3.port}")
    peer3.show_statistics()

    # Finalizando os peers
    peer1.exit()
    peer2.exit()
    peer3.exit()


if __name__ == "__main__":
    main()
