add $s4,$zero,$zero
loop: add $s3, $s1,$s2
addi $s4,$s4,1
bne $s4,10,loop
finish:
