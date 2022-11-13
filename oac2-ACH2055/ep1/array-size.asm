.data 
	fileAddress: .asciiz "C:\\sistemas-informacao\\oac2-ACH2055\\ep1\\dados-para-teste\\dados_10.txt"
	fileContent: .space 1024
	
.text
main:
	li $v0, 13 #abrir um arquivo
	la $a0, fileAddress #endereço do arquivo no argumento
	li $a1, 0 #sinalização de leitura de arquivo, 1: escrita
	li $a2, 0
	syscall #descritor do arquivo para $v0
	move $s0, $v0 #cria uma cópia do descritor
	
	li $v0, 14 #instrução para ler conteúdo do arquivo referenciado em $v0
	move $a0, $s0
	la $a1, fileContent #cria espaço para o conteúdo em a1
	li $a2, 1024 #espaço disponível para armazenar conteúdo lido do arquivo
	syscall #realiza a leitura
	move $s1, $v0 #salva a quantidade de caracteres no arquivo
	move $s0, $a1 #salva endereço do buffer em $s0
        
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $s0 #coloca o descritor no registrador $a0
	syscall
        
        move  $a0, $s0
        jal lenArray
        move $s2, $t1 #salva a quantidade números na lista
        
        li $v0, 1 #impressão da INTEGER armazenada em $a0
	move $a0, $t1 #coloca a quantidade de elementos em array1
	syscall
        
        li $v0, 10 # system call code for exit = 10
	syscall # call operating sys

lenArray:       #Fn returns the number of elements in an array
        li  $t1,0 #contagem de integers
        
loop:   lb  $t2,($a0)
        beqz $t2,endLoop
        bne $t2,32,notspace
        addi $t1,$t1,1
notspace: addi $a0,$a0,1
        j   loop
endLoop: jr  $ra
