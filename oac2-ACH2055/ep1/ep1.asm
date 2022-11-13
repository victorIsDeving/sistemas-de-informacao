.data 
	fileAddress: .asciiz "C:\\sistemas-informacao\\oac2-ACH2055\\ep1\\lista-aleatoria.txt"
	fileContent: .space 1024
	
.text
	li $v0, 13 #abrir um arquivo
	la $a0, fileAddress #endereço do arquivo no argumento
	li $a1, 0 #sinalização de leitura de arquivo, 1: leitura
	li $a2, 0
	syscall #descritor do arquivo para $v0
	move $s0, $v0 #cria uma cópia do descritor
	
	move $a0, $s0
	li $v0, 14 #instrução para ler conteúdo do arquivo referenciado em $v0
	la $a1, fileContent #cria espaço para o conteúdo em a1
	li $a2, 1024 #espaço disponível para armazenar conteúdo lido do arquivo
	syscall #realiza a leitura
	
	li $v0, 4 #impressão da string armazenada em $a0
	move $a0, $a1 #coloca a string em $a0
	syscall
	
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $s0 #coloca o descritor no registrador $a0