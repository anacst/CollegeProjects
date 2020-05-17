# Recursive factorial

# int fact(int n) {
# 	if (n < 1) return 1;
# 	else return (n * fact(n-1));
# }

fact: 	addi	$sp, $sp, -8	# Add two itens of 4 bytes in stack 
	sw	$sp, 0($a0)	# Save argument (n)
	sw	$sp, 4($ra)	# Save return address	
	slti 	$t0 $a0, 1	# Check condition n < 1,and save result to $t0: if true, $t0 = 1, else $t0 = 0
	beq  	$t0 $zero call	# If condition is false, do recursive call, else
	addi	$v0, $zero, 1	# 	set return value to 1...
	addi	$sp, $sp, 8	# 	pop 2 itens from stack...
	jr	$ra		#	and return
	
call: 	addi 	$a0, $a0, -1	# Decrease n -> (n-1)
	jal 	fact		# Recursive call to function fact with argument n-1 -> fact(n-1)
	lw 	$a0, 0($sp)	# Restore argument value (previous n)
	lw 	$ra, 4($sp)	# Restore return address
	addi 	$sp, $sp, 8	# Pop 2 restored itens from stack
	mul	$v0, $v0, $a0	# Multiply argument by value returned from last call to recursive function -> (n * fact(n-1))
	jr	$ra		# Return to where function was first called
	