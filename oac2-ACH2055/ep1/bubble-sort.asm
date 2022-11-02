		.data
array1:		.space	20		#  declare 20 bytes of storage to hold array of 5 floats
float1:		.float 45.6
float2:		.float 15.4
float3:		.float 4.9
float4:		.float 4.8
float5:		.float 1.2
floatTmp1:	.float 0.0
floatTmp2:	.float 0.0
		.text
		la $s0, array1		#  load base address of array into register $s0
		l.s $f1, float1		#  $f1 = 15.4   ("load immediate")
		s.s $f1, 0($s0)		#  first array element; indirect addressing
		l.s $f1, float2		#  $f1 = 4.8
		s.s $f1, 4($s0)		#  second array element
		l.s $f1, float3		#  $f1 = 4.9
		s.s $f1, 8($s0)		#  third array element
		l.s $f1, float4
		s.s $f1, 12($s0)
		l.s $f1, float5
		s.s $f1, 16($s0)
main:
	li $s1, 5 #tamanho da array hard coded
	move $a0, $s0
	move $a1, $s1
	
	subi $sp, $sp, 8 #espaço na pilha, sp = stack pointer
	sw $ra, 4($sp) #ra = return address da função
	sw $fp, 0($sp) #fp = frame pointer, para controle do stack construido antes da função
	move $fp, $sp #salva o valor de sp em fp, para saber a base do stack antes de chamar qualquer função
	
	jal bubbleSort
	
	sw $fp, 0($sp) #limpando o que foi alocado para a função
	sw $ra, 4($sp) 
	addi $sp, $sp, 8 
	
	la $a2, 0($s0)
	la $a3, 4($s0)
	
	li $v0, 10 # system call code for exit = 10
	syscall # call operating sys

trocaPosição: #recebe dois endereços, em a2 e a3, para trocar o conteúdo entre as duas
	l.s $f1, floatTmp1
	l.s $f3, floatTmp2
	l.s $f1, ($a2)
	l.s $f3, ($a3)
	s.s $f3, ($a2)
	s.s $f1, ($a3)
	
	jr $ra #volta na posição chamada dentro da função bubbleSort

bubbleSort:
	li $t0, 0 #primeiro loop
	move $t1, $s1 #segundo loop
	li $t3, 0
	move $t4, $a0 #cria uma cópia da array
	addi $t4, $t4, 16 #4*4 endereço do último elemento da array
	loop1:
		bge $t0,$s1,endLoop1
		addi $t3, $t0, 1
		addi $t5, $t4, 0
		loop2:
			ble $t1,$t3, endLoop2
			subi $t6, $t5, 4
			l.s $f1, ($t5)
			l.s $f3, ($t6)
			c.le.s $f1, $f3
			bc1f jumpLoop2
			move $a2, $t5
			move $a3, $t6
			jal trocaPosição
			jumpLoop2: 
			subi $t5, $t5, 4
			subi $t1, $t1, 1
			j loop2
		endLoop2:
		move $t1, $s1
		addi $t0, $t0, 1
		j loop1
	endLoop1:
		
	jr $fp  #volta para onde estava antes da chamada
	
	
	
	
	
	
	
	
	
	
	
	