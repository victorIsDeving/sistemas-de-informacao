.data 
	fileAddress: .asciiz "C:\\sistemas-informacao\\oac2-ACH2055\\ep1\\dados-para-teste\\dados_10-teste.txt"
	fileContent1: .space 1024
	.align 2 
	fileContent2: .space 2048
	.align 2 
	fileContent3: .space 2048
	float1: .float 11.111
	float2: .float 11.111
	float3: .float 11.111
	linebreakBuffer: .asciiz " \n"
	
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
	la $a1, fileContent1 #cria espaço para o conteúdo em a1
	li $a2, 1024 #espaço disponível para armazenar conteúdo lido do arquivo
	syscall #realiza a leitura
	move $s1, $a1 #salva o conteúdo em um registrador separado
        move $k0, $v0 #salva a quantidade de caracteres no arquivo
        	
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $s0 #coloca o descritor no registrador $a0
	syscall
        
        move  $a0, $s1
        jal lenArray
        move $s2, $t1 #salva a quantidade números na lista
        
        la $s3, fileContent2 #cria uma array para colocar as floats
        move $a1, $s1
        move $a3, $s3
        jal numbersToArray #passa os números para uma array de floats   	
       
#############
###sorting###
#############
	move $a2, $s2 #tamanho da array
	li $a1, 1 #1 para o quicksort, 2 para o bubblesort
	move $a0, $s3 #endereço da array com os floats
	
	subi $sp, $sp, 8 #espaço na pilha, sp = stack pointer
	sw $ra, 4($sp) #ra = return address da função
	sw $fp, 0($sp) #fp = frame pointer, para controle do stack construido antes da função
	move $fp, $sp #salva o valor de sp em fp, para saber a base do stack antes de chamar qualquer função
	
	jal ordena
endQuicksort:
endBubbleSort:
#writing into file
#abrir arquivo para escrita
	li $v0, 13 #abrir um arquivo
	la $a0, fileAddress #endereço do arquivo no argumento (cria um novo arquivo ou sobrescreve um já existente)
	li $a1, 1 #sinalização de escrita de arquivo, 0: leitura
	li $a2, 0
	syscall #descritor do arquivo para $v0
	move $s0, $v0 #cria uma cópia do descritor
	
	li $v0, 15 #instrução para escrever conteúdo no arquivo referenciado em $a0
	move $a0, $s0 #descriptor
	move $a1, $s1 #conteúdo
	move $a2, $k0 #caracteres para escrever no arquivo
	syscall #realiza a escrita	
	
	#linebreaker para separar conteúdos
	li $v0, 15 #instrução para escrever conteúdo no arquivo referenciado em $a0
	move $a0, $s0 #descriptor
	la $a1, linebreakBuffer #conteúdo
	li $a2, 2 #caracteres para escrever no arquivo
	syscall #realiza a escrita, depois do que foi escrito anteriormente
	
	li $t0, 0
	move $t1, $s3
	writeLoop:
		li $v0, 15 #instrução para escrever conteúdo no arquivo referenciado em $a0
		move $a0, $s0 #descriptor
		move $a1, $t1 #conteúdo
		li $a2, 8 #caracteres para escrever no arquivo
		syscall #realiza a escrita
		
		li $v0, 15 #instrução para escrever conteúdo no arquivo referenciado em $a0
		move $a0, $s0 #descriptor
		la $a1, linebreakBuffer #conteúdo
		li $a2, 2 #caracteres para escrever no arquivo
		syscall #realiza a escrita, depois do que foi escrito anteriormente
		
		addi  $t1, $t1, 4
		addi $t0, $t0, 1
		bne $t0, $s2, writeLoop
        	
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $s0 #coloca o descritor no registrador $a0
	syscall	
	
#####printar no console do mars o array ordenado
	li $t0, 0
	move $t1, $s3
	printLoop:
		li $v0, 2 #instrução para escrever conteúdo no arquivo referenciado em $a0
		l.s $f12, ($t1)
		syscall #realiza a escrita
		
		li $v0, 4 #instrução para escrever conteúdo no arquivo referenciado em $a0
		la $a0, linebreakBuffer #conteúdo
		syscall #realiza a escrita, depois do que foi escrito anteriormente
		
		addi  $t1, $t1, 4
		addi $t0, $t0, 1
		bne $t0, $s2, printLoop
	
#####end program
        li $v0, 10 # system call code for exit = 10
	syscall # call operating sys
	
#############
##functions##
#############
numbersToArray:
        li  $t8, 0 #posição na array resultado, para adicionar as floats
        move $t0, $a1 #cópia 1 do endereço do conteúdo lido no arquivo, para usar nos pontos
        move $t1, $a1 #cópia 2 do endereço do conteúdo lido no arquivo, para usar nos espaços
        l.s $f2, float1 #float para fazer as contas da parte inteira e da parte decimal
        l.s  $f4, float2 #float para adicionar na array
        l.s $f6, float3 #float para multiplicação pelas potências
        
numbersToArrayLoop:
	lb $t2, ($t1) #verificar se acabou os números do input
	beq $t2, 0, endNumbersToArray
	subi $t1,$t1,1 #posição antes do início do número seguinte
        li $s7, 0
        li $t6, -1 #contador de iterações para as potências de 10
        sub.s $f2, $f2, $f2 #resetar as floats para o próximo número
        sub.s $f4, $f4, $f4
        
	intPart:
		lb $t2, ($t0) #coloca o byte que está no endereço t2 em t4
        	beq $t2, 46, endIntPart #procura pelo próximo . que separa parte inteira e decimal
        	addi $t0, $t0, 1
        	j intPart
	endIntPart: #t0 tem endereço de um ponto que separa parte inteira e decimal
        
	loopInt: 
	#vai iterar do número menos significativo da parte inteira para o mais significativo
	#do endereço que tem um ponto até a base
	#e vai somando em f1 para montar a parte inteira do float
		subi $t0,$t0,1 #t0 anda do menos significativo para o mais significativo
		addi $t6,$t6,1 #iterações para a potência de 10
		beq $t0,$t1, endLoopInt #verifica se acabou a parte inteira do número
		li $t7, 0 #para iterar nas potências de 10
		li $t9, 0x3f800000  # 0x3f800000 is the encoding for 1.0 single precision float
		mtc1 $t9, $f6       # move that float to $f6
		li $t9, 0x41200000  # 0x41200000 is the encoding for 10.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		positivePowersOfTen:
			beq $t7,$t6,endPositivePowersOfTen
			addi $t7,$t7,1
			mul.s $f6, $f6, $f8
			j positivePowersOfTen
		endPositivePowersOfTen:
		lb $t2, ($t0) #coloca o byte em t2
		bne $t2, 48, int1 #ASCII 48 = 0
		li $t9, 0x00000000  # 0x00000000 is the encoding for 0.0 single precision float
		mtc1 $t9, $f4       # move that float to $f4
		j addIntToFloat
	int1:	bne $t2, 49, int2 #ASCII 49 = 1
		li $t9, 0x3f800000  # 0x3f800000 is the encoding for 1.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int2:	bne $t2, 50, int3 #ASCII 50 = 2
		li $t9, 0x40000000  # 0x40000000 is the encoding for 2.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int3:	bne $t2, 51, int4 #ASCII 51 = 3
		li $t9, 0x40400000  # 0x40400000 is the encoding for 3.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int4:	bne $t2, 52, int5 #ASCII 52 = 4
		li $t9, 0x40800000  # 0x40800000 is the encoding for 4.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int5:	bne $t2, 53, int6 #ASCII 53 = 5
		li $t9, 0x40a00000  # 0x40a00000 is the encoding for 5.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int6:	bne $t2, 54, int7 #ASCII 54 = 6
		li $t9, 0x40c00000  # 0x40c00000 is the encoding for 6.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int7:	bne $t2, 55, int8 #ASCII 55 = 7
		li $t9, 0x40e00000  # 0x40e00000 is the encoding for 7.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int8:	bne $t2, 56, int9 #ASCII 56 = 8
		li $t9, 0x41000000  # 0x41000000 is the encoding for 8.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addIntToFloat
	int9:	li $t9, 0x41100000  # 0x41100000000 is the encoding for 9.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8 #se não é nenhum dos outros só pode ser o 9
	addIntToFloat:
		add.s $f2,$f2,$f4
		j loopInt
	endLoopInt:
	#agora faço o mesmo para os decimais
	#preciso primeiro ajustar os registradores como fiz para os inteiros
        add $t0, $t0, $t6 #t0 nos pontos
        addi $t0,$t0,1 #adicionando mais um para ficar no .
        addi $t1,$t1,1 #$t1 buscando o próximo espaço
        li $t6, -1 #contador de iterações para as potências de 10 (agora negativas)
        
	decimalPart:
		lb $t2, ($t1) #coloca o byte que está no endereço t1 em t2
        	beq $t2, 32, endDecimalPart #procura pelo próximo espaço que separa dois números na lista
        	addi $t1, $t1, 1
        	j decimalPart
	endDecimalPart: #t1 tem endereço de um espaço que separa parte decimal do número atual e decimal
	
	loopDecimal: 
	#vai iterar do número mais significativo da parte decimal para o menos significativo
	#do endereço que tem um ponto até o que tem um espaço
	#e vai somando em f2 para montar a parte decimal do float
		addi $t0,$t0,1 #t0 anda do mais significativo para o menos significativo
        	addi $t6, $t6, 1 #contador de quantas vezes vamos multiplicar a base decimal
		beq $t0,$t1, endLoopDecimal #verifica se acabou a parte decimal do número
		li $t7, 0 #para iterar nas potências de 10
		li $t9, 0x3f800000  # 0x3f800000 is the encoding for 1.0 single precision float
		mtc1 $t9, $f6       # move that float to $f6
		li $t9, 0x41200000  # 0x41200000 is the encoding for 10.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		div.s $f6,$f6,$f8  #valor base = 0.1
		negativePowersOfTen:
			beq $t7,$t6,endNegativePowersOfTen
			addi $t7,$t7,1
			div.s $f6,$f6,$f8
			j negativePowersOfTen
		endNegativePowersOfTen:
		lb $t2, ($t0) #coloca o byte em t2
		bne $t2, 48, dec1 #ASCII 48 = 0
		li $t9, 0x00000000  # 0x00000000 is the encoding for 0.0 single precision float
		mtc1 $t9, $f4       # move that float to $f4
		j addDecimalToFloat
	dec1:	bne $t2, 49, dec2 #ASCII 49 = 1
		li $t9, 0x3f800000  # 0x3f800000 is the encoding for 1.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec2:	bne $t2, 50, dec3 #ASCII 50 = 2
		li $t9, 0x40000000  # 0x40000000 is the encoding for 2.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec3:	bne $t2, 51, dec4 #ASCII 51 = 3
		li $t9, 0x40400000  # 0x40400000 is the encoding for 3.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec4:	bne $t2, 52, dec5 #ASCII 52 = 4
		li $t9, 0x40800000  # 0x40800000 is the encoding for 4.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec5:	bne $t2, 53, dec6 #ASCII 53 = 5
		li $t9, 0x40a00000  # 0x40a00000 is the encoding for 5.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec6:	bne $t2, 54, dec7 #ASCII 54 = 6
		li $t9, 0x40c00000  # 0x40c00000 is the encoding for 6.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec7:	bne $t2, 55, dec8 #ASCII 55 = 7
		li $t9, 0x40e00000  # 0x40e00000 is the encoding for 7.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec8:	bne $t2, 56, dec9 #ASCII 56 = 8
		li $t9, 0x41000000  # 0x41000000 is the encoding for 8.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8
		j addDecimalToFloat
	dec9:	li $t9, 0x41100000  # 0x41100000000 is the encoding for 9.0 single precision float
		mtc1 $t9, $f8       # move that float to $f8
		mul.s $f4, $f6, $f8 #se não é nenhum dos outros só pode ser o 9
	addDecimalToFloat:
		add.s $f2,$f2,$f4
		j loopDecimal
	endLoopDecimal:
	s.s  $f2, ($a3)
	
	addi $a3, $a3, 4 #passa para a próxima posição da array resultado
	#essa parte aqui é bem importantante na formatação do arquivo input
	#com 2 é um arquivo que separa os números com uma quebra de linha
	addi $t1,$t1,2 #$t1 para o início do próximo número, pula um \r, um \n e cai no primeiro dígito do próximo número
        addi $t0,$t0,2 #$t2 para o início do próximo número
	j numbersToArrayLoop
endNumbersToArray:
	jr $ra

#Tamanho da array contado por espaços no arquivo original
lenArray:       #Fn returns the number of elements in an array
        li  $t1,0 #contagem de integers
        
loop:   lb  $t2,($a0)
        beqz $t2,endLoop
        bne $t2,32,notspace
        addi $t1,$t1,1
notspace: 
	addi $a0,$a0,1
        j   loop
endLoop: 
	jr  $ra
	
#Função de ordenação
ordena:
	bne $a1, 1, bubbleSort
quicksort:
	li $a3, 0
	addi $sp,$sp,-20    # allocate space for saving registers in the stack
	sw $ra,0($sp)       # save return address register in the stack
	sw $s4,4($sp)       # save $s4 register in the stack
	sw $s5,8($sp)       # save $s5 register in the stack
	sw $s6,12($sp)      # save $s6 register in the stack
	sw $s7,16($sp)      # save $s7 register in the stack
	bge $a3,$a2,endif1          #   if( l < r )
	# {  // divide and conquer
		move $s4,$a0                # save value of $a0
		move $s5,$a3                # save value of $a3
		move $s6,$a2                # save value of $a2
		jal partition               # j = partition( a, l, r);
		move $s7,$v0                # save return value in $s7 (j)
		move $a0,$s4                # load saved value of $a0
		move $a3,$s5                # load saved value of $a3
		addi $a2,$s7,-1             # load value of j-1
		jal  quicksort              # quickSort( a, l, j-1);
		move $a0,$s4                # load saved value of $a0
		addi $a3,$s7,1              # load value of j+1
		move $a2,$s6                # load saved value of $a2
		jal  quicksort              # quickSort( a, j+1, r);
	# }
	endif1:                         
	lw $ra,0($sp)       # restore contents of $ra from the stack
	lw $s4,4($sp)       # restore $s4 register from the stack
	lw $s5,8($sp)       # restore $s5 register from the stack
	lw $s6,12($sp)      # restore $s6 register from the stack
	lw $s7,16($sp)      # restore $s7 register from the stack
	addi $sp,$sp,20     # restore stack pointer
	
	j endQuicksort

#————————————————–

# int partition(uint32_t a[], int l, int r) {

# On entry: a0=a[]

#           a1=l

#           a2=r

#————————————————–

partition:
	addi $sp,$sp,-16    # allocate space for saving registers in the stack
	sw $ra,0($sp)       # save return address register in the stack
	sw $s4,4($sp)       # save $s4 register in the stack
	sw $s5,8($sp)       # save $s5 register in the stack
	sw $s6,12($sp)      # save $s6 register in the stack
	sll $t4,$a3,2       # multiply l by 4 to get offset in array
	add $t4,$t4,$a0     # get address of a[l] in t4
	lw  $s4,($t4)       # pivot = a[l]; $s4 will be pivot
	move $s5,$a3        # i = l;  $s5 will be i
	addi $s6,$a2,1      # j = r+1;  $s6 will be j
	while1:                 # while( 1)
	# {
	do1: # do
		addi $s5,$s5,1      #   ++i;
		sll $t1,$s5,2       # multiply i by 4 to get offset in array
		add $t1,$t1,$a0     # get address of a[i] in t1
		lw  $t0,($t1)       # $t0 = a[i]
		bgt $t0,$s4,do2     # while( a[i] <= pivot && i <= r );
		bgt $s5,$a2,do2
		b   do1
	do2: # do
		addi $s6,$s6,-1     # –j;
		sll $t2,$s6,2       # multiply j by 4 to get offset in array
		add $t2,$t2,$a0     # get address of a[j] in t2
		subi $t2,$t2,4	    #correct address expected
		lw  $t0,($t2)       # $t0 = a[j]
		bgt $t0,$s4,do2     # while( a[j] > pivot );
		bge $s5,$s6,brk1    # if( i >= j ) break;
		lw $t0,($t1)        # t = a[i];
		lw $t3,($t2)        # a[i] = a[j];
		sw $t3,($t1)
		sw $t0,($t2)        # a[j] = t;
		b while1            
	# }
	brk1:
		lw $t0,($t4)        # t = a[l];
		lw $t3,($t2)        # a[l] = a[j];
		sw $t3,($t4)
		sw $t0,($t2)        # a[j] = t;
		move $v0,$s6        # return j;
		lw $ra,0($sp)       # restore contents of $ra from the stack
		lw $s4,4($sp)       # restore $s4 register from the stack
		lw $s5,8($sp)       # restore $s5 register from the stack
		lw $s6,12($sp)      # restore $s6 register from the stack
		addi $sp,$sp,16     # restore stack pointer
	
	jr $ra
bubbleSort:
	li $t0, 0 #primeiro loop
	move $t1, $a2 #segundo loop
	li $t3, 0 #temp para pegar o valor de t0 + 1
	move $t4, $a0 #cria uma cópia da array
	mul $t5, $a2, 4
	add $t4, $t4, $t5
	subi $t4, $t4, 4  #endereço do último elemento da array
	loop1:
		bge $t0,$a2,endLoop1
		addi $t3, $t0, 1
		addi $t5, $t4, 0
		loop2:
			ble $t1,$t3, endLoop2
			subi $t6, $t5, 4
			l.s $f1, ($t5)
			l.s $f3, ($t6)
			c.le.s $f1, $f3
			bc1f jumpLoop2
			move $t8, $t5
			move $t9, $t6
			jal trocaPosição
			jumpLoop2: 
			subi $t5, $t5, 4
			subi $t1, $t1, 1
			j loop2
		endLoop2:
		move $t1, $a2
		addi $t0, $t0, 1
		j loop1
	endLoop1:
		
	j endBubbleSort #volta para onde estava antes da chamada

trocaPosição: #recebe dois endereços, em t8 e t9, para trocar o conteúdo entre os dois
	l.s $f1, float1
	l.s $f3, float2
	l.s $f1, ($t8)
	l.s $f3, ($t9)
	s.s $f3, ($t8)
	s.s $f1, ($t9)
	
	jr $ra #volta na posição chamada dentro da função bubbleSort
