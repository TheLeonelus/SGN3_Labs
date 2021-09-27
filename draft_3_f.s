	.file	"draft_3.c"
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	48(%rsp), %rbp
	.seh_setframe	%rbp, 48
	.seh_endprologue
	movq	%rcx, 32(%rbp)
	movq	%rdx, 40(%rbp)
	movq	%r8, 48(%rbp)
	movq	%r9, 56(%rbp)
	leaq	40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rbx
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	32(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	a
	.bss
	.align 8
a:
	.space 8
	.globl	b
	.align 8
b:
	.space 8
	.globl	H
	.align 8
H:
	.space 8
	.globl	E
	.align 8
E:
	.space 8
	.globl	pastAreaValue
	.align 8
pastAreaValue:
	.space 8
	.globl	currentAreaValue
	.align 8
currentAreaValue:
	.space 8
	.globl	difference
	.align 8
difference:
	.space 8
	.globl	splitAmount
	.align 4
splitAmount:
	.space 4
	.globl	k
	.align 4
k:
	.space 4
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "\0"
.LC1:
	.ascii "\12Result: %lf\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	call	integralBordersInput
	call	precisionInput
	movl	$2, splitAmount(%rip)
	call	stepSize
	movl	$0, k(%rip)
	call	integralCalculation
	movq	%xmm0, %rax
	movq	%rax, currentAreaValue(%rip)
	movsd	currentAreaValue(%rip), %xmm0
	movsd	%xmm0, pastAreaValue(%rip)
	--------------------leaq	.LC0(%rip), %rcx --------------------
	--------------------call	printf_s --------------------
	jmp	.L4
.L6:
	movsd	currentAreaValue(%rip), %xmm0
	movsd	%xmm0, pastAreaValue(%rip)
	movl	splitAmount(%rip), %eax
	addl	%eax, %eax
	movl	%eax, splitAmount(%rip)
	call	stepSize
	call	integralCalculation
	movq	%xmm0, %rax
	movq	%rax, currentAreaValue(%rip)
	movsd	pastAreaValue(%rip), %xmm0
	movsd	currentAreaValue(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, difference(%rip)
	--------------------leaq	.LC0(%rip), %rcx --------------------
	--------------------call	printf_s --------------------
	movsd	E(%rip), %xmm0
	movsd	difference(%rip), %xmm1
	comisd	%xmm1, %xmm0
	ja	.L8
	jmp	.L4
.L8:
	movl	k(%rip), %eax
	addl	$1, %eax
	movl	%eax, k(%rip)
.L4:
	movl	k(%rip), %eax
	testl	%eax, %eax
	jle	.L6
	movsd	currentAreaValue(%rip), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rcx
	call	printf
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC2:
	.ascii "\12Input left border of the segment: \0"
.LC3:
	.ascii "%lf\0"
	.align 8
.LC4:
	.ascii "\12Input right border of the segment: \0"
.LC5:
	.ascii "Inappropriate input.\0"
.LC6:
	.ascii "%s\0"
	.text
	.globl	integralBordersInput
	.def	integralBordersInput;	.scl	2;	.type	32;	.endef
	.seh_proc	integralBordersInput
integralBordersInput:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	jmp	.L10
.L13:
	leaq	.LC2(%rip), %rcx
	call	printf_s
	leaq	a(%rip), %rdx
	leaq	.LC3(%rip), %rcx
	movq	__imp_scanf_s(%rip), %rax
	call	*%rax
	leaq	.LC4(%rip), %rcx
	call	printf_s
	leaq	b(%rip), %rdx
	leaq	.LC3(%rip), %rcx
	movq	__imp_scanf_s(%rip), %rax
	call	*%rax
	movsd	a(%rip), %xmm0
	movsd	b(%rip), %xmm1
	comisd	%xmm1, %xmm0
	jbe	.L15
	leaq	.LC5(%rip), %rdx
	leaq	.LC6(%rip), %rcx
	call	printf_s
	jmp	.L10
.L15:
	addl	$1, -4(%rbp)
.L10:
	cmpl	$0, -4(%rbp)
	jle	.L13
	nop
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC7:
	.ascii "\12Input precision of calculations: \0"
	.text
	.globl	precisionInput
	.def	precisionInput;	.scl	2;	.type	32;	.endef
	.seh_proc	precisionInput
precisionInput:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC7(%rip), %rcx
	call	printf_s
	leaq	E(%rip), %rdx
	leaq	.LC3(%rip), %rcx
	movq	__imp_scanf_s(%rip), %rax
	call	*%rax
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	stepSize
	.def	stepSize;	.scl	2;	.type	32;	.endef
	.seh_proc	stepSize
stepSize:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movsd	b(%rip), %xmm0
	movsd	a(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movl	splitAmount(%rip), %eax
	addl	%eax, %eax
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, H(%rip)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	xCalculation
	.def	xCalculation;	.scl	2;	.type	32;	.endef
	.seh_proc	xCalculation
xCalculation:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	16(%rbp), %xmm1
	movsd	H(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	a(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	fxCalculation
	.def	fxCalculation;	.scl	2;	.type	32;	.endef
	.seh_proc	fxCalculation
fxCalculation:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movsd	%xmm0, 16(%rbp)
	movsd	16(%rbp), %xmm0
	call	log
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	integralCalculation
	.def	integralCalculation;	.scl	2;	.type	32;	.endef
	.seh_proc	integralCalculation
integralCalculation:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$104, %rsp
	.seh_stackalloc	104
	leaq	96(%rsp), %rbp
	.seh_setframe	%rbp, 96
	.seh_endprologue
	movq	%rsp, %rax
	movq	%rax, %rdi
	movl	splitAmount(%rip), %eax
	addl	%eax, %eax
	addl	$1, %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -40(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %rcx
	movl	$0, %ebx
	movslq	%eax, %rdx
	leaq	0(,%rdx,8), %rbx
	movslq	%eax, %rdx
	movq	%rdx, %r10
	movl	$0, %r11d
	movslq	%eax, %rdx
	movq	%rdx, %r8
	movl	$0, %r9d
	cltq
	salq	$4, %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	leaq	32(%rsp), %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -48(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L23
.L24:
	movl	-12(%rbp), %eax
	movl	%eax, %ecx
	call	xCalculation
	movq	%xmm0, %rax
	movq	-48(%rbp), %rdx
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	%rax, (%rdx,%rcx,8)
	movq	-48(%rbp), %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	movq	(%rax,%rdx,8), %rax
	movq	%rbx, %rsi
	shrq	$3, %rsi
	movq	%rax, %xmm0
	call	fxCalculation
	movq	%xmm0, %rax
	movq	-48(%rbp), %rdx
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	addq	%rsi, %rcx
	movq	%rax, (%rdx,%rcx,8)
	addl	$1, -12(%rbp)
.L23:
	movl	splitAmount(%rip), %eax
	addl	%eax, %eax
	addl	$1, %eax
	cmpl	%eax, -12(%rbp)
	jle	.L24
	movl	$1, -8(%rbp)
	jmp	.L25
.L26:
	movq	%rbx, %rcx
	shrq	$3, %rcx
	movl	-8(%rbp), %eax
	addl	%eax, %eax
	leal	-1(%rax), %edx
	movq	-48(%rbp), %rax
	movslq	%edx, %rdx
	addq	%rcx, %rdx
	movsd	(%rax,%rdx,8), %xmm0
	movsd	-32(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -32(%rbp)
	addl	$1, -8(%rbp)
.L25:
	movl	splitAmount(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jle	.L26
	movl	$1, -4(%rbp)
	jmp	.L27
.L28:
	movq	%rbx, %rcx
	shrq	$3, %rcx
	movl	-4(%rbp), %eax
	leal	(%rax,%rax), %edx
	movq	-48(%rbp), %rax
	movslq	%edx, %rdx
	addq	%rcx, %rdx
	movsd	(%rax,%rdx,8), %xmm0
	movsd	-24(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	addl	$1, -4(%rbp)
.L27:
	movl	splitAmount(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L28
	movsd	H(%rip), %xmm0
	movsd	.LC8(%rip), %xmm2
	movapd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movq	%rbx, %rdx
	shrq	$3, %rdx
	movq	-48(%rbp), %rax
	movsd	(%rax,%rdx,8), %xmm2
	movsd	-32(%rbp), %xmm3
	movsd	.LC9(%rip), %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	movsd	-24(%rbp), %xmm0
	addsd	%xmm0, %xmm0
	addsd	%xmm0, %xmm2
	shrq	$3, %rbx
	movq	%rbx, %rcx
	movl	splitAmount(%rip), %eax
	addl	%eax, %eax
	leal	1(%rax), %edx
	movq	-48(%rbp), %rax
	movslq	%edx, %rdx
	addq	%rcx, %rdx
	movsd	(%rax,%rdx,8), %xmm0
	addsd	%xmm2, %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	movq	%rdi, %rsp
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leaq	8(%rbp), %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC8:
	.long	0
	.long	1074266112
	.align 8
.LC9:
	.long	0
	.long	1074790400
	.ident	"GCC: (Rev5, Built by MSYS2 project) 10.3.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	printf_s;	.scl	2;	.type	32;	.endef
	.def	log;	.scl	2;	.type	32;	.endef
