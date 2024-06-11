import sys
from class_peer import Peer


def parse_neighbors_file(file_name):
    neighs = []
    file_path = f'./{file_name}'
    try:
        with open(file_path, 'r') as f:
            for line in f:
                line = line.strip()
                if line:
                    host_file, port_file = line.split(':')
                    neighs.append((host_file, int(port_file)))
    except FileNotFoundError:
        print(f"    Arquivo {file_name} não encontrado.")
    return neighs


def parse_key_value_file(file_name):
    key_files = {}
    file_path = f'./{file_name}'
    try:
        with open(file_path, 'r') as f:
            for line in f:
                line = line.strip()
                if line:
                    key, value = line.split(':')
                    key_files[key] = value
    except FileNotFoundError:
        print(f"    Arquivo {file_name} não encontrado.")
    return key_files


if len(sys.argv) < 2:
    print("Uso: python file.py <endereco>:<porta> [vizinhos.txt [lista_chave_valor.txt]]")
    sys.exit(1)

address = sys.argv[1]
host, port = address.split(':')
port = int(port)

neighbors_file = sys.argv[2] if len(sys.argv) > 2 else None
key_value_file = sys.argv[3] if len(sys.argv) > 3 else None

neighbors = parse_neighbors_file(neighbors_file) if neighbors_file else []
keys = parse_key_value_file(key_value_file) if key_value_file else {}

peer = Peer(host, port, neighbors, keys)
peer.start()
