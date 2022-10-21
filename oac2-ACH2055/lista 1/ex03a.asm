beq $s1,$zero,finish
loop: add $s3,$s1,$s2
addi $s1, $s1,-1
bne $s1,$zero,loop
finish:
