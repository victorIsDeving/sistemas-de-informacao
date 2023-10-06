import os
from collections import deque

class Process:
    def __init__(self, name, commands):
        self.name = name
        self.commands = commands
        self.PC = 0
        self.X = 0
        self.Y = 0
        self.state = "READY"
        self.blocked_counter = 0
        self.swaps = 0
        self.instructions = 0

    def execute_next(self):
        if self.PC < len(self.commands):
            cmd = self.commands[self.PC]
            self.PC += 1
            self.instructions += 1

            if "X=" in cmd:
                self.X = int(cmd.split('=')[1])
            elif "Y=" in cmd:
                self.Y = int(cmd.split('=')[1])
            elif "E/S" in cmd:
                self.state = "BLOCKED"
                self.blocked_counter = 2
                self.swaps += 1
            elif "COM" in cmd:
                pass
            elif "SAIDA" in cmd:
                self.state = "TERMINATED"
                self.swaps += 1
            return cmd
        return None

class Scheduler:
    def __init__(self, quantum):
        self.ready_queue = deque()
        self.blocked_queue = deque()
        self.processes = {}
        self.quantum = quantum

    def load_programs(self, dir_path="C:\sistemas-informacao\so-ACH2044\ep1\programas"):
        files = sorted(os.listdir(dir_path))
        for f in files:
            if f.endswith(".txt") and not f == "quantum.txt":
                with open(os.path.join(dir_path, f), 'r') as fp:
                    lines = fp.readlines()
                    name = lines[0].strip()
                    commands = [cmd.strip() for cmd in lines[1:]]
                    process = Process(name, commands)
                    self.ready_queue.append(process)
                    self.processes[name] = process

    def run(self):
        log_file_name = f"log{self.quantum}.txt"
        with open(log_file_name, 'w') as log_file:
            while self.ready_queue or self.blocked_queue:
                if self.ready_queue:
                    current_process = self.ready_queue.popleft()
                    current_process.state = "RUNNING"

                    for _ in range(self.quantum):
                        if current_process.state == "RUNNING":
                            cmd = current_process.execute_next()
                            if cmd is None or current_process.state == "BLOCKED":
                                break

                if current_process.state == "RUNNING":
                    self.ready_queue.append(current_process)
                elif current_process.state == "BLOCKED":
                    self.blocked_queue.append(current_process)
                elif current_process.state == "TERMINATED":
                    log_file.write(f"Process {current_process.name} finished with X={current_process.X} and Y={current_process.Y}\n")

            for process in list(self.blocked_queue):
                process.blocked_counter -= 1
                if process.blocked_counter == 0:
                    process.state = "READY"
                    self.ready_queue.append(process)
                    self.blocked_queue.remove(process)

        total_swaps = sum(process.swaps for process in self.processes.values())
        total_instructions = sum(process.instructions
                    for process in self.processes.values())
        average_swaps = total_swaps / len(self.processes)
        average_instructions = total_instructions / len(self.processes)

        print(f"Média de trocas de processo: {average_swaps:.2f}")
        print(f"Média de instruções por quantum: {average_instructions:.2f}")

if __name__ == "__main__":
    with open('C:\sistemas-informacao\so-ACH2044\ep1\programas\quantum.txt','r') as q:
        quantum = int(q.read().strip())
    scheduler = Scheduler(quantum)
    scheduler.load_programs()
    scheduler.run()
