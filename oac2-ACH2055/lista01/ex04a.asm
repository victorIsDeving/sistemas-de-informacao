		.data
array1:		.space	20		#  declare 20 bytes of storage to hold array of 5 integers
		.text
		la $s0, array1		#  load base address of array into register $s0
		li $t1, 0		#  $t1 = 0   ("load immediate")
		sw $t1, 0($s0)		#  first array element set to 0; indirect addressing
		li $t1, 1		#  $t1 = 1
		sw $t1, 4($s0)		#  second array element set to 1
		li $t1, 2		#  $t1 = 2
		sw $t1, 8($s0)		#  third array element set to 2
		li $t1, 3
		sw $t1, 12($s0)
		li $t1, 4
		sw $t1, 16($s0)
main:
li $t0,0 #a
li $t4,1 #i
loop:	addi $t4,$t4,-1
	sll $s1,$t4,2
	addu $s1,$s0,$s1
	lw $s1,($s1)
	add $t0,$t0,$s1
	addi $t4,$t4,2
	bne $t4,6,loop
