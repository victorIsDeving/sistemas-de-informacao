import threading
import time
from class_peer import Peer


def start_peer(peer):
    peer.start()


def main():
    # Inicializando os peers
    peer1 = Peer('localhost', 5000, known_neighbors=[('localhost', 5001)])
    peer2 = Peer('localhost', 5001, known_neighbors=[('localhost', 5000), ('localhost', 5002)])
    peer3 = Peer('localhost', 5002, known_neighbors=[('localhost', 5001), ('localhost', 5003)])
    peer4 = Peer('localhost', 5003, known_neighbors=[('localhost', 5002),])

    peer3.files['key1'] = 'value1'
    peer4.files['key2'] = 'value2'

    print(f"Starting {peer1.host}:{peer1.port}")
    threading.Thread(target=start_peer, args=(peer1,)).start()
    time.sleep(2)
    print(f"Starting {peer2.host}:{peer2.port}")
    threading.Thread(target=start_peer, args=(peer2,)).start()
    time.sleep(2)
    print(f"Starting {peer3.host}:{peer3.port}")
    threading.Thread(target=start_peer, args=(peer3,)).start()
    time.sleep(2)
    print(f"Starting {peer4.host}:{peer4.port}")
    threading.Thread(target=start_peer, args=(peer4,)).start()
    time.sleep(2)

    print(f"Searches")
    print(f"Flood {peer1.host}:{peer1.port} for `key1`")
    peer1.search('FLOOD')
    time.sleep(5)

    print(f"Flood {peer1.host}:{peer1.port} for `key2`")
    peer1.search('FLOOD')
    time.sleep(5)

    print(f"Statistics {peer1.host}:{peer1.port}")
    peer1.show_statistics()
    print(f"Statistics {peer2.host}:{peer2.port}")
    peer2.show_statistics()
    print(f"Statistics {peer3.host}:{peer3.port}")
    peer3.show_statistics()
    print(f"Statistics {peer4.host}:{peer4.port}")
    peer4.show_statistics()

    peer1.exit()
    peer2.exit()
    peer3.exit()
    peer4.exit()


if __name__ == "__main__":
    main()
