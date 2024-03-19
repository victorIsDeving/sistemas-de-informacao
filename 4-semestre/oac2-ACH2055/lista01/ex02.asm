# a) a = b + 100
addi $a,$b,100

# b) x[10] = x[11] + c
lw $t0,44($s0)
add $t1,$t0,$c
sw $t1,40($s0)