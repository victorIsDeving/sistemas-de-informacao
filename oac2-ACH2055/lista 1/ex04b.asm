		.data
array1:		.space	40		#  declare 40 bytes of storage to hold array of 10 integers
		.text
		la $s0, array1		#  load base address of array into register $s0
		li $t5, 20		#  $t1 = 0   ("load immediate")
		sw $t5, 40($s0)		#  last array element set to 15; indirect addressing
main:
li $t0,1 #a
li $t1,5 #b
li $t2,0 #c
li $t3,0 #d
slt $t4,$t2,$t0
beq $t4,$zero,else
	addi $t1,$t1,5
	sw $t1,40($s0)
	j finish
else: mult $t0,$t1
mflo $t3
li $t4,2
mult $t3,$t4
mflo $t3
lw $t4,40($s0) 
div $t4,$t3
mflo $t4
sw $t4,40($s0)
finish: