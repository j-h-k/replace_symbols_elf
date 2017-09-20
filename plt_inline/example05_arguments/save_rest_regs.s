.section .text
.globl save_regs 
.type save_regs, @function
save_regs:	
	popq %rax #dummy
	pushq %rdi
	pushq %rsi
	pushq %rdx
	pushq %rcx
	pushq %r8
	pushq %r9
	jmp *%rax

.section .text
.globl rest_regs
.type rest_regs, @function
rest_regs:
	popq %rax #dummy
	popq %r9
	popq %r8
	popq %rcx
	popq %rdx
	popq %rsi
	popq %rdi
	jmp *%rax
