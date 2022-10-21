		.data
array1:		.space	20		#  declare 20 bytes of storage to hold array of 5 integers
		.text
		la $s0, array1		#  load base address of array into register $s0
		li $t5, 1		#  $t5 = 1   ("load immediate")
		sw $t5, 0($s0)		#  first array element set to 1; indirect addressing
		sw $t5, 4($s0)
		sw $t5, 8($s0)
		sw $t5, 12($s0)
		sw $t5, 16($s0)
		sw $t5, 20($s0)
main:
li $t0,0 #a
li $t1,0 #b
li $t2,1 #c
li $t3,3 #d
li $t4,0 #i
li $a0,5 #loop repetition
loop:	slt $t5,$t4,$a0
	beq $t5,$zero,end
		sll $t5,$t4,2
		addu $t5,$s0,$t5
		lw $t6,($t5)
		addi $t6,$t6,1
		sw $t6,($t5)
		beq $t6,$10,notif
			addi $t0,$t0,1
		notif: li $a1,2	
		mult $t2,$a1
		mflo $t1
		add $t1,$t1,$t3
	addi $t4,$t4,1
	slt $t5,$t4,$a0
	li $a2,1
	beq $t5,$a2,loop
end: