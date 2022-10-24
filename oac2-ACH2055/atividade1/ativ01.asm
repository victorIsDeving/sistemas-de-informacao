.globl main
main:
	li $a0,1 #atribuições
	li $a1,2
	li $a2,3
	li $a3,4
	li $t0,5
	li $t1,6
	
	subi $sp,$sp,16 #espaço na pilha, sp = stack pointer
	sw $ra,12($sp) #ra = return address da função
	sw $fp,8($sp) #fp = frame pointer, para controle do stack construido antes da função
	sw $t0,4($sp) #salva 5o argumento
	sw $t1,0($sp) #salva 6o argumento
	move $fp,$sp #salva o valor de sp em fp, para saber a base do stack antes de chamar qualquer função
	
	jal calculaRaiz
	
	sw $fp,8($sp) #limpando o que foi alocado para a função
	sw $ra,12($sp) 
	subi $sp,$sp,16 
	
	jr $ra #termina o programa
	
.globl calculaRaiz
calculaRaiz:
	subi $sp,$sp,12 #espaço para manipular dentro da função e receber o resultado de sqrt
	sw $t3,8($sp) #salva para multiplicação
	sw $t2,4($sp) #salva para resultado de calculaDelta
	sw $t1,0($sp) #salva para resultado de sqrt
	
	jal calculaDelta
	jal sqrt
	
	
	li $t7,-1 #aritmética
	mult $a1,$t7
	mflo $t3
	add $t3,$t3,$t1
	
	add $v0,$t3,$zero #resultado da função
	
	lw $t1,0($sp)  #limpando o que foi alocado para a função
	lw $t2,4($sp)
	lw $t3,8($sp)
	subi $sp,$sp,12
	
	jr $fp  #volta para onde estava antes da chamada
.globl sqrt
sqrt:
	li $t1,1
	jr $ra #volta para onde estava antes da chamada
	
.globl calculaDelta
calculaDelta:
	subi $sp,$sp,8 #espaço para manipular dentro da função
	sw $t5,4($sp) #salva para resultado de 4*b
	sw $t4,0($sp) #salva para resultado de 4*a*c
	
	li $t7,4 #aritmética
	mult $a1,$t7
	mflo $t5
	mult $a0,$t7
	mflo $t4
	mult $t4,$a2
	mflo $t4
	sub $t5,$t5,$t4
	
	move $t2,$t5 #passa o resultado para calculaRaiz
	
	lw $t4,0($sp) #limpando o que foi alocado para a função
	lw $t5,4($sp) 
	addi $sp,$sp,8
	
	jr $ra #volta para onde estava antes da chamada