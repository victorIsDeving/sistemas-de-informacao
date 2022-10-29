.data 
	fileAddress: .asciiz "C:\\sistemas-informacao\\oac2-ACH2055\\ep1\\lista-aleatoria.txt"
	fileContent: .space 1024
	string: .asciiz "1.1 1.1 1.1 1.1 1.1 11.1 1.1 1.1 11.1 11.1 " #43 caracteres
	finalString: .space 128
	
.text
	la $s1, string #S1 tem a string resultado que vou adicionar no final
	la $s2, finalString #S2 tem a concatenação da string lida no arquivo original com a string que quero adicionar ao final do arquivo
	
#abrir arquivo para leitura e pegar o texto original
	li $v0, 13 #abrir um arquivo
	la $a0, fileAddress #endereço do arquivo no argumento
	li $a1, 0 #sinalização de leitura de arquivo, 1: escrita
	li $a2, 0
	syscall #descritor do arquivo para $v0
	move $t0, $v0 #cria uma cópia do descritor
	
	move $a0, $t0
	li $v0, 14 #instrução para ler conteúdo do arquivo referenciado em $v0
	la $a1, fileContent #cria espaço para o conteúdo em a1
	li $a2, 1024 #espaço disponível para armazenar conteúdo lido do arquivo
	syscall #realiza a leitura
	move $s0, $a1 #coloca a string em $s0
	
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $t0 #coloca o descritor no registrador $a0
	syscall

#abrir arquivo para escrita
	li $v0, 13 #abrir um arquivo
	la $a0, fileAddress #endereço do arquivo no argumento
	li $a1, 1 #sinalização de escrita de arquivo, 0: leitura
	li $a2, 0
	syscall #descritor do arquivo para $v0
	move $t0, $v0 #cria uma cópia do descritor

	move $a0, $s0
	move $a2, $s2
	jal copyString
	
	#colocar quebra de linha no arquivo, para separar input de output
	li $t1, 13
   	sb $t1, ($a2)
   	addi $a2, $a2, 1
	li $t1, 10
   	sb $t1, ($a2)
   	addi $a2, $a2, 1
	li $t1, 13
   	sb $t1, ($a2)
   	addi $a2, $a2, 1
	li $t1, 10
   	sb $t1, ($a2)
   	addi $a2, $a2, 1
	# pra fazer output mais organizado :)
	
	move $a0, $s1
	jal copyString
	
	li $v0, 15 #instrução para escrever conteúdo no arquivo referenciado em $v0
	move $a0, $t0
	la $a1, ($s2) #conteúdo concatenado das strings
	li $a2, 90 #caracteres para escrever no arquivo, esse é o total para 2 cópias da array (original e ordenada) + quebra de linha para separar as cópias
	syscall #realiza a escrita (cria um novo arquivo ou sobrescreve um já existente)
	
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $t0 #coloca o descritor no registrador $a0
	syscall

	j finishProgram #termina o programa


copyString: lb $t1, ($a0)              # get character at address  
  	beqz $t1, endCpy
   	sb $t1, ($a2)                  # else store current character in the buffer  
   	addi $a0, $a0, 1               # string1 pointer points a position forward  
   	addi $a2, $a2, 1               # same for finalStr pointer  
   	j copyString                   # loop
endCpy:	jr $ra

finishProgram: