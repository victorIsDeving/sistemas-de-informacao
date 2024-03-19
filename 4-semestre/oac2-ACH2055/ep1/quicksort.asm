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
	la $a0,array1      # set first argument to a
	move $a1,$0        # set second argument to 0
	li $a2,4           # set third argument to 4

	jal quicksort       # quickSort(a,0,99);

	li $v0,10           # terminate program using syscall 10
	syscall

#————————————————–

#void quickSort( uint32_t a[], int l, int r)

# On entry: a0=a[]

#           a1=l

#           a2=r

#————————————————–

quicksort:
	addi $sp,$sp,-20    # allocate space for saving registers in the stack
	sw $ra,0($sp)       # save return address register in the stack
	sw $s0,4($sp)       # save $s0 register in the stack
	sw $s1,8($sp)       # save $s1 register in the stack
	sw $s2,12($sp)      # save $s2 register in the stack
	sw $s3,16($sp)      # save $s3 register in the stack
	bge $a1,$a2,endif1          #   if( l < r )
	# {  // divide and conquer
		move $s0,$a0                # save value of $a0
		move $s1,$a1                # save value of $a1
		move $s2,$a2                # save value of $a2
		jal partition               # j = partition( a, l, r);
		move $s3,$v0                # save return value in $s3 (j)
		move $a0,$s0                # load saved value of $a0
		move $a1,$s1                # load saved value of $a1
		addi $a2,$s3,-1             # load value of j-1
		jal  quicksort              # quickSort( a, l, j-1);
		move $a0,$s0                # load saved value of $a0
		addi $a1,$s3,1              # load value of j+1
		move $a2,$s2                # load saved value of $a2
		jal  quicksort              # quickSort( a, j+1, r);
	# }
	endif1:                         
	lw $ra,0($sp)       # restore contents of $ra from the stack
	lw $s0,4($sp)       # restore $s0 register from the stack
	lw $s1,8($sp)       # restore $s1 register from the stack
	lw $s2,12($sp)      # restore $s2 register from the stack
	lw $s3,16($sp)      # restore $s3 register from the stack
	addi $sp,$sp,20     # restore stack pointer
	
	jr $ra

#————————————————–

# int partition(uint32_t a[], int l, int r) {

# On entry: a0=a[]

#           a1=l

#           a2=r

#————————————————–

partition:
	addi $sp,$sp,-16    # allocate space for saving registers in the stack
	sw $ra,0($sp)       # save return address register in the stack
	sw $s0,4($sp)       # save $s0 register in the stack
	sw $s1,8($sp)       # save $s1 register in the stack
	sw $s2,12($sp)      # save $s2 register in the stack
	sll $t4,$a1,2       # multiply l by 4 to get offset in array
	add $t4,$t4,$a0     # get address of a[l] in t4
	lw  $s0,($t4)       # pivot = a[l]; $s0 will be pivot
	move $s1,$a1        # i = l;  $s1 will be i
	addi $s2,$a2,1      # j = r+1;  $s2 will be j
	while1:                 # while( 1)
	# {
	do1: # do
		addi $s1,$s1,1      #   ++i;
		sll $t1,$s1,2       # multiply i by 4 to get offset in array
		add $t1,$t1,$a0     # get address of a[i] in t1
		lw  $t0,($t1)       # $t0 = a[i]
		bgt $t0,$s0,do2     # while( a[i] <= pivot && i <= r );
		bgt $s1,$a2,do2
		b   do1
	do2: # do
		addi $s2,$s2,-1     # –j;
		sll $t2,$s2,2       # multiply j by 4 to get offset in array
		add $t2,$t2,$a0     # get address of a[j] in t2
		lw  $t0,($t2)       # $t0 = a[j]
		bgt $t0,$s0,do2     # while( a[j] > pivot );
		bge $s1,$s2,brk1    # if( i >= j ) break;
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
		move $v0,$s2        # return j;
		lw $ra,0($sp)       # restore contents of $ra from the stack
		lw $s0,4($sp)       # restore $s0 register from the stack
		lw $s1,8($sp)       # restore $s1 register from the stack
		lw $s2,12($sp)      # restore $s2 register from the stack
		addi $sp,$sp,16     # restore stack pointer
	
	jr $ra
