import socket
import threading
import random
import sys
import statistics


def send_message(sock, message):
    print(f"Encaminhando mensagem \"{message.strip()}\" para `{sock.getpeername()[0]}:{sock.getpeername()[1]}`")
    sock.send(message.encode())
    print(f"    Envio feito com sucesso: \"{message.strip()}\"")


def calculate_stats(hops):
    if not hops:
        return 0, 0
    mean = statistics.mean(hops)
    stddev = statistics.stdev(hops) if len(hops) > 1 else 0
    return mean, stddev


def sending(message, destination: tuple):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect(destination)
        print(f"Encaminhando mensagem \"{message.strip()}\" para `{s.getpeername()[0]}:{s.getpeername()[1]}`")
        s.send(message.encode())
        print(f"    Envio feito com sucesso: \"{message.strip()}\"")
        s.close()
        return True
    except Exception as e:
        print(f"Erro ao conectar com {destination[0]}:{destination[1]}: \n    {e}")
    return False


class Peer:
    def __init__(self, host, port, known_neighbors=None, files=None):
        self.host = host
        self.port = port
        self.neighbors_file = known_neighbors if known_neighbors else []
        self.know_neighbors = []
        self.files = files if files else {}
        self.seq_number = 0
        self.default_ttl = 100
        self.running = True
        self.server_socket = None
        self.received_messages = {}  # armazenar msgs recebidas
        self.noh_mae = None
        self.vizinho_ativo = None
        self.vizinhos_candidatos = []
        self.flooding_count = 0
        self.random_walk_count = 0
        self.dfs_count = 0
        self.flooding_hops = []
        self.random_walk_hops = []
        self.dfs_hops = []

    def start(self):
        self.process_neighbors()
        threading.Thread(target=self.listen).start()
        self.show_menu()

    def listen(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        while self.running:
            try:
                conn, addr = self.server_socket.accept()
                threading.Thread(target=self.handle_connection, args=(conn,)).start()
            except Exception as e:
                if self.running:
                    print(f"Erro ao aceitar conexão: {e}")
        self.server_socket.close()

    def process_neighbors(self):
        for n in self.neighbors_file:
            self.seq_number += 1
            header = [f"{self.host}:{self.port}", str(self.seq_number), "1", "HELLO"]
            message = f"{' '.join(header)}\n"
            print(f"Verificar status do vizinho `{n[0]}:{n[1]}`")
            if sending(message, n):
                print(f"    Vizinho {n[0]}:{n[1]} está online.")
            else:
                print(f"    Vizinho {n[0]}:{n[1]} não está online.")
            self.know_neighbors.append(n)
            print(f"    Adicionando vizinho {n[0]}:{n[1]} na tabela.")

    def list_neighbors(self):
        if not self.know_neighbors:
            print(f"Nenhum vizinho.")
        else:
            print(f"Há {len(self.know_neighbors)} vizinho(s) na tabela:")
            for i, n in enumerate(self.know_neighbors):
                print(f"    [{i}] {n[0]} {n[1]}")

    def send_hello_message(self):
        if len(self.know_neighbors) == 0:
            print(f"Não tem vizinhos para enviar mensagens.")
            return
        print(f"Escolha o vizinho:")
        self.list_neighbors()
        while True:
            choice = input("")
            try:
                choice = int(choice)
                if choice in range(len(self.know_neighbors)):
                    self.seq_number += 1
                    header = [f"{self.host}:{self.port}", str(self.seq_number), "1", "HELLO"]
                    message = f"{' '.join(header)}\n"
                    sending(message, self.know_neighbors[choice])
                    break
                else:
                    print(f"Escolha um vizinho válido")
            except ValueError as e:
                print(f"{e}\n Escolha um vizinho válido")

    def key_check(self, key, origin, seq_numb, mode, hop_count, last_hop_port):
        if key in self.files:
            print(f"Chave encontrada!")
            value = self.files[key]
            header_new = [origin, seq_numb, str(self.default_ttl), "VAL"]
            args = [mode, key, value, str(hop_count)]
            message = f"{' '.join(header_new)} {' '.join(args)}\n"
            sending(message, ('localhost', last_hop_port))
            return True
        return False

    def handle_connection(self, conn):
        data = conn.recv(1024).decode().strip()
        if not data:
            conn.close()
            return
        print(f"Mensagem recebida: \"{data}\"")  # Log da mensagem recebida
        parts = data.split()
        origin = parts[0]
        seq_numb = parts[1]
        ttl = int(parts[2])
        operation = parts[3]
        msg_id = f"{origin}({seq_numb})"
        header = [origin, seq_numb, str(ttl - 1), operation]
        if operation == 'HELLO':
            origin_host, origin_port = origin.split(':')
            origin_port = int(origin_port)
            if (origin_host, origin_port) not in self.know_neighbors:
                self.know_neighbors.append((origin_host, origin_port))
                print(f"Adicionando vizinho na tabela: {origin_host}:{origin_port}")
            else:
                print(f"Vizinho já está na tabela: {origin_host}:{origin_port}")
            # conn.send(self.create_message('HELLO', [], origin_port).encode())
        elif operation == 'BYE':
            origin_host, origin_port = origin.split(':')
            origin_port = int(origin_port)
            if (origin_host, origin_port) in self.know_neighbors:
                self.know_neighbors.remove((origin_host, origin_port))
                print(f"Removendo vizinho da tabela: {origin_host}:{origin_port}")
        elif operation == 'SEARCH':
            mode = parts[4]
            last_hop_port = int(parts[5])
            key = parts[6]
            hop_count = int(parts[7])
            if ttl - 1 == 0:
                print("TTL igual a zero, descartando mensagem")
                conn.close()
                return
            if mode == 'FL':
                self.flooding_count += 1
                if self.key_check(key, origin, seq_numb, mode, hop_count, last_hop_port):
                    conn.close()
                    return
                if msg_id in self.received_messages:
                    print("Flooding: Mensagem repetida!")
                    conn.close()
                    return
                self.received_messages[msg_id] = last_hop_port
                hop_count += 1
                args = ["FL", str(self.port), key, str(hop_count)]
                self.flood_search(header, args, last_hop_port)
            if mode == 'RW':
                self.random_walk_count += 1
                if self.key_check(key, origin, seq_numb, mode, hop_count, last_hop_port):
                    conn.close()
                    return
                self.received_messages[msg_id] = last_hop_port
                hop_count += 1
                args = ["RW", str(self.port), key, str(hop_count)]
                self.random_walk_search(header, args, last_hop_port)
            if mode == 'BP':
                self.dfs_count += 1
                if self.key_check(key, origin, seq_numb, mode, hop_count, last_hop_port):
                    conn.close()
                    return
                hop_count += 1
                args = ["BP", str(self.port), key, str(hop_count)]
                self.dfs_search(header, args, last_hop_port)
        elif operation == 'VAL':
            key = parts[5]
            value = parts[6]
            mode = parts[4]
            hop_count = int(parts[7])
            if origin == f"{self.host}:{self.port}":
                if mode == 'FL':
                    self.flooding_hops.append(hop_count)
                elif mode == 'RW':
                    self.random_walk_hops.append(hop_count)
                elif mode == 'BP':
                    self.dfs_hops.append(hop_count)
                print(f"Valor encontrado! Chave: {key} valor: {value}")
            else:
                back_port = self.received_messages[msg_id]
                sending(data, ('localhost', back_port))
        conn.close()

    def search(self, search_type):
        if not self.know_neighbors:
            print("Vc não tem um vizinho para mandar mensagens :/")
            return
        key = input(f"Digite o termo a ser buscado: ")
        if key in self.files:
            print(f"Valor na tabela local!\n    chave: {key} valor: {self.files[key]}")
            return
        self.seq_number += 1
        header = [f"{self.host}:{self.port}", str(self.seq_number), str(self.default_ttl), "SEARCH"]
        if search_type == 'FLOOD':
            args = ["FL", str(self.port), key, "1"]
            self.flood_search(header, args, 0)
        elif search_type == 'RANDOM_WALK':
            args = ["RW", str(self.port), key, "1"]
            self.random_walk_search(header, args, 0)
        else:
            args = ["BP", str(self.port), key, "1"]
            self.dfs_search(header, args, self.port)

    def flood_search(self, header, args, last_hop):
        message = f"{' '.join(header)} {' '.join(args)}\n"
        for neighbor in self.know_neighbors:
            if neighbor[1] != last_hop:
                sending(message, neighbor)

    def random_walk_search(self, header, args, last_hop):
        message = f"{' '.join(header)} {' '.join(args)}\n"
        neighbors = [n for n in self.know_neighbors if n[1] != last_hop]
        if len(neighbors) > 0:
            neighbor = random.choice([n for n in self.know_neighbors if n[1] != last_hop])
            sending(message, neighbor)

    def dfs_search(self, header, args, last_hop):
        origin = header[0]
        seq_numb = header[1]
        msg_id = f"{origin}({seq_numb})"
        last_hop_tuple = ('localhost', last_hop)

        if msg_id not in self.received_messages:
            self.vizinhos_candidatos = [n for n in self.know_neighbors if n[1] != last_hop]
            self.noh_mae = int(last_hop)
            self.received_messages[msg_id] = last_hop

        if last_hop_tuple in self.vizinhos_candidatos:
            self.vizinhos_candidatos.remove(('localhost', int(last_hop)))

        if self.noh_mae == self.port and self.vizinho_ativo == last_hop_tuple and not self.vizinhos_candidatos:
            print(f"BP: Não foi possível localizar a chave {args[2]} :/")
            self.noh_mae = None
            self.vizinhos_candidatos = []
            return

        if self.vizinho_ativo and self.vizinho_ativo != last_hop_tuple:
            print("BP: ciclo detectado, devolvendo a mensagem...")
            nxt = last_hop_tuple
        elif not self.vizinhos_candidatos:
            print("BP: nenhum vizinho encontrou a chave :/")
            nxt = ('localhost', self.noh_mae)
        else:
            nxt = random.choice(self.vizinhos_candidatos)
            self.vizinho_ativo = nxt
            self.vizinhos_candidatos.remove(nxt)

        message = f"{' '.join(header)} {' '.join(args)}\n"
        sending(message, nxt)

    def show_menu(self):
        while True:
            print("\nEscolha o comando:")
            print("[0] Listar vizinhos")
            print("[1] HELLO")
            print("[2] SEARCH (flooding)")
            print("[3] SEARCH (random walk)")
            print("[4] SEARCH (busca em profundidade)")
            print("[5] Estatísticas")
            print("[6] Alterar valor padrão de TTL")
            print("[9] Sair")
            choice = input("")

            if choice == '0':
                self.list_neighbors()
            elif choice == '1':
                self.send_hello_message()
            elif choice == '2':
                self.search('FLOOD')
            elif choice == '3':
                self.search('RANDOM_WALK')
            elif choice == '4':
                self.search('DFS')
            elif choice == '5':
                self.show_statistics()
            elif choice == '6':
                self.change_ttl()
            elif choice == '9':
                print("Saindo...")
                self.exit()
                sys.exit()
            else:
                print("Opção inválida, tente novamente.")

    def change_ttl(self):
        new_ttl = int(input("Digite o novo valor padrão de TTL: "))
        self.default_ttl = new_ttl
        print(f"Valor padrão de TTL alterado para {self.default_ttl}.")

    def exit(self):
        self.running = False
        if self.server_socket:
            try:
                self.server_socket.close()
            except Exception as e:
                print(f"Erro ao fechar o socket do servidor: {e}")
        self.seq_number += 1
        header = [f"{self.host}:{self.port}", str(self.seq_number), "1", "BYE"]
        message = f"{' '.join(header)}\n"
        for neighbor in self.know_neighbors:
            sending(message, neighbor)
        print(f"Conexões encerradas, saindo...")

    def show_statistics(self):
        flooding_mean, flooding_stddev = calculate_stats(self.flooding_hops)
        rw_mean, rw_stddev = calculate_stats(self.random_walk_hops)
        dfs_mean, dfs_stddev = calculate_stats(self.dfs_hops)

        print("Estatísticas")
        print(f"    Total de mensagens de flooding vistas: {self.flooding_count}")
        print(f"    Total de mensagens de random walk vistas: {self.random_walk_count}")
        print(f"    Total de mensagens de busca em profundidade vistas: {self.dfs_count}")
        print(f"    Média de saltos até encontrar destino por flooding: {flooding_mean:.2f}")
        print(f"    Desvio padrão de saltos até encontrar destino por flooding: {flooding_stddev:.2f}")
        print(f"    Média de saltos até encontrar destino por random walk: {rw_mean:.2f}")
        print(f"    Desvio padrão de saltos até encontrar destino por random walk: {rw_stddev:.2f}")
        print(f"    Média de saltos até encontrar destino por busca em profundidade: {dfs_mean:.2f}")
        print(f"    Desvio padrão de saltos até encontrar destino por busca em profundidade: {dfs_stddev:.2f}")
