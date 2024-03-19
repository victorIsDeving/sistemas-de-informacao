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
li $s4, 10
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
        move $s5, $v0 #salva a quantidade de caracteres no arquivo
        	
	li $v0, 16 #fechar o arquivo que estiver aberto em $a0
	move $a0, $s0 #coloca o descritor no registrador $a0
	syscall

        la $s3, fileContent2 #cria uma array para colocar as floats
        move $a1, $s1
        move $a3, $s3
        jal numbersToArray   	
        
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
	move $a2, $s5 #caracteres para escrever no arquivo
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
		bne $t0, $s4, writeLoop
        	
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
		bne $t0, $s4, printLoop
	
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
	addi $a3, $a3, 4 #passa para a próxima posição
	
        addi $t1,$t1,3 #$t1 para o início do próximo número, pula um \r, um \n e cai no primeiro dígito do próximo número
        addi $t0,$t0,3 #$t2 para o início do próximo número
	j numbersToArrayLoop
endNumbersToArray:
	jr $ra
