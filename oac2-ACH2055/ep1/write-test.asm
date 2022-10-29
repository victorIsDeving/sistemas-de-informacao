.data 
	fileAddress: .asciiz "C:\\sistemas-informacao\\oac2-ACH2055\\ep1\\lista-aleatoria.txt"
	string: .asciiz "1.1 1.1 1.1 1.1 1.1 11.1 1.1 1.1 11.1 11.1 " #42 caracteres
	
.text
	li $v0, 13 #abrir um arquivo
	la $a0, fileAddress #endereço do arquivo no argumento
	li $a1, 1 #sinalização de escrita de arquivo, 0: leitura
	li $a2, 0
	syscall #descritor do arquivo para $v0
	move $t0, $v0 #cria uma cópia do descritor
	
	li $v0, 15 #instrução para escrever conteúdo no arquivo referenciado em $v0
	move $a0, $t0
	la $a1, string #conteúdo
	li $a2, 43 #caracteres para escrever no arquivo
	syscall #realiza a escrita (cria um novo arquivo ou sobrescreve um já existente)
	
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $s0 #coloca o descritor no registrador $a0
	syscall