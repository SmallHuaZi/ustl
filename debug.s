	.file	"debug.cpp"
	.text
	.section	.text._ZnwmPv,"axG",@progbits,_ZnwmPv,comdat
	.weak	_ZnwmPv
	.type	_ZnwmPv, @function
_ZnwmPv:
.LFB1234:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1234:
	.size	_ZnwmPv, .-_ZnwmPv
	.text
	.type	_ZL18__gthread_active_pv, @function
_ZL18__gthread_active_pv:
.LFB1516:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1516:
	.size	_ZL18__gthread_active_pv, .-_ZL18__gthread_active_pv
	.section	.text._ZL20__gthread_mutex_lockP15pthread_mutex_t,"axG",@progbits,_ZNSt5mutex4lockEv,comdat
	.type	_ZL20__gthread_mutex_lockP15pthread_mutex_t, @function
_ZL20__gthread_mutex_lockP15pthread_mutex_t:
.LFB1530:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	_ZL18__gthread_active_pv
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L6
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	pthread_mutex_lock@PLT
	jmp	.L7
.L6:
	movl	$0, %eax
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1530:
	.size	_ZL20__gthread_mutex_lockP15pthread_mutex_t, .-_ZL20__gthread_mutex_lockP15pthread_mutex_t
	.section	.text._ZL22__gthread_mutex_unlockP15pthread_mutex_t,"axG",@progbits,_ZNSt5mutex6unlockEv,comdat
	.type	_ZL22__gthread_mutex_unlockP15pthread_mutex_t, @function
_ZL22__gthread_mutex_unlockP15pthread_mutex_t:
.LFB1533:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	_ZL18__gthread_active_pv
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L9
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	pthread_mutex_unlock@PLT
	jmp	.L10
.L9:
	movl	$0, %eax
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1533:
	.size	_ZL22__gthread_mutex_unlockP15pthread_mutex_t, .-_ZL22__gthread_mutex_unlockP15pthread_mutex_t
	.section	.text._ZNSt5mutex4lockEv,"axG",@progbits,_ZNSt5mutex4lockEv,comdat
	.align 2
	.weak	_ZNSt5mutex4lockEv
	.type	_ZNSt5mutex4lockEv, @function
_ZNSt5mutex4lockEv:
.LFB2104:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZL20__gthread_mutex_lockP15pthread_mutex_t
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.L13
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	_ZSt20__throw_system_errori@PLT
.L13:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2104:
	.size	_ZNSt5mutex4lockEv, .-_ZNSt5mutex4lockEv
	.section	.text._ZNSt5mutex6unlockEv,"axG",@progbits,_ZNSt5mutex6unlockEv,comdat
	.align 2
	.weak	_ZNSt5mutex6unlockEv
	.type	_ZNSt5mutex6unlockEv, @function
_ZNSt5mutex6unlockEv:
.LFB2106:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZL22__gthread_mutex_unlockP15pthread_mutex_t
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2106:
	.size	_ZNSt5mutex6unlockEv, .-_ZNSt5mutex6unlockEv
	.section	.text._ZN4ustl9exceptionD2Ev,"axG",@progbits,_ZN4ustl9exceptionD5Ev,comdat
	.align 2
	.weak	_ZN4ustl9exceptionD2Ev
	.type	_ZN4ustl9exceptionD2Ev, @function
_ZN4ustl9exceptionD2Ev:
.LFB2196:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN4ustl9exceptionE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2196:
	.size	_ZN4ustl9exceptionD2Ev, .-_ZN4ustl9exceptionD2Ev
	.weak	_ZN4ustl9exceptionD1Ev
	.set	_ZN4ustl9exceptionD1Ev,_ZN4ustl9exceptionD2Ev
	.section	.text._ZN4ustl9exceptionD0Ev,"axG",@progbits,_ZN4ustl9exceptionD5Ev,comdat
	.align 2
	.weak	_ZN4ustl9exceptionD0Ev
	.type	_ZN4ustl9exceptionD0Ev, @function
_ZN4ustl9exceptionD0Ev:
.LFB2198:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl9exceptionD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2198:
	.size	_ZN4ustl9exceptionD0Ev, .-_ZN4ustl9exceptionD0Ev
	.section	.rodata
	.align 8
.LC0:
	.string	"the size of the requested memory exceeds the maximum vlaue"
	.section	.text._ZN4ustl9bad_alloc7messageEv,"axG",@progbits,_ZN4ustl9bad_alloc7messageEv,comdat
	.align 2
	.weak	_ZN4ustl9bad_alloc7messageEv
	.type	_ZN4ustl9bad_alloc7messageEv, @function
_ZN4ustl9bad_alloc7messageEv:
.LFB2201:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L18
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	jmp	.L20
.L18:
	leaq	.LC0(%rip), %rax
.L20:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2201:
	.size	_ZN4ustl9bad_alloc7messageEv, .-_ZN4ustl9bad_alloc7messageEv
	.weak	_ZN4ustl15allocator_basic12_S_free_listE
	.section	.bss._ZN4ustl15allocator_basic12_S_free_listE,"awG",@nobits,_ZN4ustl15allocator_basic12_S_free_listE,comdat
	.align 32
	.type	_ZN4ustl15allocator_basic12_S_free_listE, @gnu_unique_object
	.size	_ZN4ustl15allocator_basic12_S_free_listE, 128
_ZN4ustl15allocator_basic12_S_free_listE:
	.zero	128
	.weak	_ZN4ustl15allocator_basic13_S_free_startE
	.section	.bss._ZN4ustl15allocator_basic13_S_free_startE,"awG",@nobits,_ZN4ustl15allocator_basic13_S_free_startE,comdat
	.align 8
	.type	_ZN4ustl15allocator_basic13_S_free_startE, @gnu_unique_object
	.size	_ZN4ustl15allocator_basic13_S_free_startE, 8
_ZN4ustl15allocator_basic13_S_free_startE:
	.zero	8
	.weak	_ZN4ustl15allocator_basic11_S_free_endE
	.section	.bss._ZN4ustl15allocator_basic11_S_free_endE,"awG",@nobits,_ZN4ustl15allocator_basic11_S_free_endE,comdat
	.align 8
	.type	_ZN4ustl15allocator_basic11_S_free_endE, @gnu_unique_object
	.size	_ZN4ustl15allocator_basic11_S_free_endE, 8
_ZN4ustl15allocator_basic11_S_free_endE:
	.zero	8
	.weak	_ZN4ustl15allocator_basic12_S_heap_sizeE
	.section	.bss._ZN4ustl15allocator_basic12_S_heap_sizeE,"awG",@nobits,_ZN4ustl15allocator_basic12_S_heap_sizeE,comdat
	.align 8
	.type	_ZN4ustl15allocator_basic12_S_heap_sizeE, @gnu_unique_object
	.size	_ZN4ustl15allocator_basic12_S_heap_sizeE, 8
_ZN4ustl15allocator_basic12_S_heap_sizeE:
	.zero	8
	.section	.text._ZN4ustl15allocator_basic16_M_get_free_listEm,"axG",@progbits,_ZN4ustl15allocator_basic16_M_get_free_listEm,comdat
	.align 2
	.weak	_ZN4ustl15allocator_basic16_M_get_free_listEm
	.type	_ZN4ustl15allocator_basic16_M_get_free_listEm, @function
_ZN4ustl15allocator_basic16_M_get_free_listEm:
.LFB2206:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	shrq	$4, %rax
	salq	$3, %rax
	leaq	-8(%rax), %rdx
	leaq	_ZN4ustl15allocator_basic12_S_free_listE(%rip), %rax
	addq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2206:
	.size	_ZN4ustl15allocator_basic16_M_get_free_listEm, .-_ZN4ustl15allocator_basic16_M_get_free_listEm
	.text
	.align 2
	.globl	_ZN4ustl15allocator_basic9_M_refillEm
	.type	_ZN4ustl15allocator_basic9_M_refillEm, @function
_ZN4ustl15allocator_basic9_M_refillEm:
.LFB2207:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$20, -56(%rbp)
	leaq	-56(%rbp), %rdx
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm
	movq	%rax, -32(%rbp)
	movq	-80(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic16_M_get_free_listEm
	movq	%rax, -24(%rbp)
	movq	-32(%rbp), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	$0, -40(%rbp)
	jmp	.L24
.L25:
	movq	-48(%rbp), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	%rax, -48(%rbp)
	addq	$1, -40(%rbp)
.L24:
	movq	-56(%rbp), %rax
	subq	$2, %rax
	cmpq	%rax, -40(%rbp)
	jb	.L25
	movq	-40(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movq	$0, (%rax)
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L27
	call	__stack_chk_fail@PLT
.L27:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2207:
	.size	_ZN4ustl15allocator_basic9_M_refillEm, .-_ZN4ustl15allocator_basic9_M_refillEm
	.section	.text._ZN4ustl9exceptionC2Ev,"axG",@progbits,_ZN4ustl9exceptionC5Ev,comdat
	.align 2
	.weak	_ZN4ustl9exceptionC2Ev
	.type	_ZN4ustl9exceptionC2Ev, @function
_ZN4ustl9exceptionC2Ev:
.LFB2211:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN4ustl9exceptionE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2211:
	.size	_ZN4ustl9exceptionC2Ev, .-_ZN4ustl9exceptionC2Ev
	.weak	_ZN4ustl9exceptionC1Ev
	.set	_ZN4ustl9exceptionC1Ev,_ZN4ustl9exceptionC2Ev
	.section	.text._ZN4ustl9bad_allocC2Ev,"axG",@progbits,_ZN4ustl9bad_allocC5Ev,comdat
	.align 2
	.weak	_ZN4ustl9bad_allocC2Ev
	.type	_ZN4ustl9bad_allocC2Ev, @function
_ZN4ustl9bad_allocC2Ev:
.LFB2213:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl9exceptionC2Ev
	leaq	16+_ZTVN4ustl9bad_allocE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2213:
	.size	_ZN4ustl9bad_allocC2Ev, .-_ZN4ustl9bad_allocC2Ev
	.weak	_ZN4ustl9bad_allocC1Ev
	.set	_ZN4ustl9bad_allocC1Ev,_ZN4ustl9bad_allocC2Ev
	.text
	.align 2
	.globl	_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm
	.type	_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm, @function
_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm:
.LFB2208:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	movq	-96(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, -64(%rbp)
	movq	_ZN4ustl15allocator_basic11_S_free_endE(%rip), %rax
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rdx
	subq	%rdx, %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	cmpq	%rax, -64(%rbp)
	ja	.L31
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, _ZN4ustl15allocator_basic13_S_free_startE(%rip)
	movq	-24(%rbp), %rax
	jmp	.L32
.L31:
	movq	-56(%rbp), %rax
	cmpq	%rax, -96(%rbp)
	ja	.L33
	movq	-64(%rbp), %rax
	movl	$0, %edx
	divq	-96(%rbp)
	movq	%rax, %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	movq	-96(%rbp), %rdx
	imulq	%rdx, %rax
	movq	%rax, -64(%rbp)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, _ZN4ustl15allocator_basic13_S_free_startE(%rip)
	movq	-24(%rbp), %rax
	jmp	.L32
.L33:
	movq	-64(%rbp), %rbx
	movq	_ZN4ustl15allocator_basic12_S_heap_sizeE(%rip), %rax
	shrq	$4, %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZN4ustl12align_extendEmm
	addl	$1, %eax
	movl	%eax, %ecx
	salq	%cl, %rbx
	movq	%rbx, %rax
	movq	%rax, -64(%rbp)
	cmpq	$0, -56(%rbp)
	jle	.L34
	movq	-56(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic16_M_get_free_listEm
	movq	%rax, -48(%rbp)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rax
	movq	-48(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, (%rax)
.L34:
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, _ZN4ustl15allocator_basic13_S_free_startE(%rip)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rax
	testq	%rax, %rax
	jne	.L35
	movq	-96(%rbp), %rax
	movq	%rax, -72(%rbp)
	jmp	.L36
.L38:
	movq	-96(%rbp), %rax
	shrq	$4, %rax
	leaq	0(,%rax,8), %rdx
	leaq	_ZN4ustl15allocator_basic12_S_free_listE(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L37
	movq	-32(%rbp), %rax
	movq	%rax, _ZN4ustl15allocator_basic13_S_free_startE(%rip)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, _ZN4ustl15allocator_basic11_S_free_endE(%rip)
	movq	-104(%rbp), %rdx
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm
	jmp	.L32
.L37:
	addq	$16, -72(%rbp)
.L36:
	cmpq	$256, -72(%rbp)
	jbe	.L38
	movl	$16, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	movq	$0, (%rbx)
	movq	$0, 8(%rbx)
	movq	%rbx, %rdi
	call	_ZN4ustl9bad_allocC1Ev
	leaq	_ZN4ustl9bad_allocD1Ev(%rip), %rax
	movq	%rax, %rdx
	leaq	_ZTIN4ustl9bad_allocE(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	__cxa_throw@PLT
.L35:
	movq	_ZN4ustl15allocator_basic12_S_heap_sizeE(%rip), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, _ZN4ustl15allocator_basic12_S_heap_sizeE(%rip)
	movq	_ZN4ustl15allocator_basic13_S_free_startE(%rip), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, _ZN4ustl15allocator_basic11_S_free_endE(%rip)
	movq	-104(%rbp), %rdx
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm
	nop
.L32:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2208:
	.size	_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm, .-_ZN4ustl15allocator_basic14_M_alloc_chuckEmPm
	.section	.text._ZN4ustl12align_extendEmm,"axG",@progbits,_ZN4ustl12align_extendEmm,comdat
	.weak	_ZN4ustl12align_extendEmm
	.type	_ZN4ustl12align_extendEmm, @function
_ZN4ustl12align_extendEmm:
.LFB2220:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	subq	$1, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-16(%rbp), %rax
	notq	%rax
	andq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2220:
	.size	_ZN4ustl12align_extendEmm, .-_ZN4ustl12align_extendEmm
	.section	.text._ZN4ustl14align_compressEmm,"axG",@progbits,_ZN4ustl14align_compressEmm,comdat
	.weak	_ZN4ustl14align_compressEmm
	.type	_ZN4ustl14align_compressEmm, @function
_ZN4ustl14align_compressEmm:
.LFB2221:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	subq	$1, -16(%rbp)
	movq	-16(%rbp), %rax
	notq	%rax
	andq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2221:
	.size	_ZN4ustl14align_compressEmm, .-_ZN4ustl14align_compressEmm
	.section	.text._ZN4ustl16_list_node_basic8_M_resetEv,"axG",@progbits,_ZN4ustl16_list_node_basic8_M_resetEv,comdat
	.align 2
	.weak	_ZN4ustl16_list_node_basic8_M_resetEv
	.type	_ZN4ustl16_list_node_basic8_M_resetEv, @function
_ZN4ustl16_list_node_basic8_M_resetEv:
.LFB2350:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2350:
	.size	_ZN4ustl16_list_node_basic8_M_resetEv, .-_ZN4ustl16_list_node_basic8_M_resetEv
	.section	.text._ZN4ustl16_list_node_basic7_M_hookEPS0_,"axG",@progbits,_ZN4ustl16_list_node_basic7_M_hookEPS0_,comdat
	.align 2
	.weak	_ZN4ustl16_list_node_basic7_M_hookEPS0_
	.type	_ZN4ustl16_list_node_basic7_M_hookEPS0_, @function
_ZN4ustl16_list_node_basic7_M_hookEPS0_:
.LFB2351:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2351:
	.size	_ZN4ustl16_list_node_basic7_M_hookEPS0_, .-_ZN4ustl16_list_node_basic7_M_hookEPS0_
	.section	.text._ZN4ustl16_list_node_basic9_M_unhookEv,"axG",@progbits,_ZN4ustl16_list_node_basic9_M_unhookEv,comdat
	.align 2
	.weak	_ZN4ustl16_list_node_basic9_M_unhookEv
	.type	_ZN4ustl16_list_node_basic9_M_unhookEv, @function
_ZN4ustl16_list_node_basic9_M_unhookEv:
.LFB2352:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	8(%rdx), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl16_list_node_basic8_M_resetEv
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2352:
	.size	_ZN4ustl16_list_node_basic9_M_unhookEv, .-_ZN4ustl16_list_node_basic9_M_unhookEv
	.section	.text._ZN4ustl16_list_node_basic10_M_transerEPS0_S1_,"axG",@progbits,_ZN4ustl16_list_node_basic10_M_transerEPS0_S1_,comdat
	.align 2
	.weak	_ZN4ustl16_list_node_basic10_M_transerEPS0_S1_
	.type	_ZN4ustl16_list_node_basic10_M_transerEPS0_S1_, @function
_ZN4ustl16_list_node_basic10_M_transerEPS0_S1_:
.LFB2353:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2353:
	.size	_ZN4ustl16_list_node_basic10_M_transerEPS0_S1_, .-_ZN4ustl16_list_node_basic10_M_transerEPS0_S1_
	.section	.text._ZN4ustl16_list_node_basicC2Ev,"axG",@progbits,_ZN4ustl16_list_node_basicC5Ev,comdat
	.align 2
	.weak	_ZN4ustl16_list_node_basicC2Ev
	.type	_ZN4ustl16_list_node_basicC2Ev, @function
_ZN4ustl16_list_node_basicC2Ev:
.LFB2355:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2355:
	.size	_ZN4ustl16_list_node_basicC2Ev, .-_ZN4ustl16_list_node_basicC2Ev
	.weak	_ZN4ustl16_list_node_basicC1Ev
	.set	_ZN4ustl16_list_node_basicC1Ev,_ZN4ustl16_list_node_basicC2Ev
	.section	.text._ZN4ustl12_list_header11_M_inc_sizeEi,"axG",@progbits,_ZN4ustl12_list_header11_M_inc_sizeEi,comdat
	.align 2
	.weak	_ZN4ustl12_list_header11_M_inc_sizeEi
	.type	_ZN4ustl12_list_header11_M_inc_sizeEi, @function
_ZN4ustl12_list_header11_M_inc_sizeEi:
.LFB2358:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdx
	movl	-12(%rbp), %eax
	cltq
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 24(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2358:
	.size	_ZN4ustl12_list_header11_M_inc_sizeEi, .-_ZN4ustl12_list_header11_M_inc_sizeEi
	.section	.text._ZN4ustl12_list_header11_M_dec_sizeEi,"axG",@progbits,_ZN4ustl12_list_header11_M_dec_sizeEi,comdat
	.align 2
	.weak	_ZN4ustl12_list_header11_M_dec_sizeEi
	.type	_ZN4ustl12_list_header11_M_dec_sizeEi, @function
_ZN4ustl12_list_header11_M_dec_sizeEi:
.LFB2359:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rcx
	subq	%rcx, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 24(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2359:
	.size	_ZN4ustl12_list_header11_M_dec_sizeEi, .-_ZN4ustl12_list_header11_M_dec_sizeEi
	.section	.text._ZNK4ustl12_list_header7_M_lastEv,"axG",@progbits,_ZNK4ustl12_list_header7_M_lastEv,comdat
	.align 2
	.weak	_ZNK4ustl12_list_header7_M_lastEv
	.type	_ZNK4ustl12_list_header7_M_lastEv, @function
_ZNK4ustl12_list_header7_M_lastEv:
.LFB2360:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2360:
	.size	_ZNK4ustl12_list_header7_M_lastEv, .-_ZNK4ustl12_list_header7_M_lastEv
	.section	.text._ZNK4ustl12_list_header8_M_firstEv,"axG",@progbits,_ZNK4ustl12_list_header8_M_firstEv,comdat
	.align 2
	.weak	_ZNK4ustl12_list_header8_M_firstEv
	.type	_ZNK4ustl12_list_header8_M_firstEv, @function
_ZNK4ustl12_list_header8_M_firstEv:
.LFB2361:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2361:
	.size	_ZNK4ustl12_list_header8_M_firstEv, .-_ZNK4ustl12_list_header8_M_firstEv
	.section	.text._ZN4ustl12_list_headerC2Ev,"axG",@progbits,_ZN4ustl12_list_headerC5Ev,comdat
	.align 2
	.weak	_ZN4ustl12_list_headerC2Ev
	.type	_ZN4ustl12_list_headerC2Ev, @function
_ZN4ustl12_list_headerC2Ev:
.LFB2365:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl16_list_node_basicC2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2365:
	.size	_ZN4ustl12_list_headerC2Ev, .-_ZN4ustl12_list_headerC2Ev
	.weak	_ZN4ustl12_list_headerC1Ev
	.set	_ZN4ustl12_list_headerC1Ev,_ZN4ustl12_list_headerC2Ev
	.text
	.globl	main
	.type	main, @function
main:
.LFB2610:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movl	%edi, -132(%rbp)
	movq	%rsi, -144(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$16, -80(%rbp)
	movl	$16, -76(%rbp)
	movl	$3, -72(%rbp)
	movl	$7, -68(%rbp)
	movl	$11, -64(%rbp)
	movl	$9, -60(%rbp)
	movl	$26, -56(%rbp)
	movl	$18, -52(%rbp)
	movl	$14, -48(%rbp)
	movl	$15, -44(%rbp)
	movl	$19, -40(%rbp)
	movl	$30, -36(%rbp)
	movl	$40, -32(%rbp)
	movl	$32, -28(%rbp)
	movl	$45, -24(%rbp)
	movl	$32, -20(%rbp)
	movl	$45, -16(%rbp)
	movl	$16, -12(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEEC1INS1_INS_10_list_implIiS2_EEEEEEv
	leaq	-80(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-96(%rbp), %rax
	addq	$72, %rax
	movq	%rax, -88(%rbp)
	jmp	.L56
.L57:
	movq	-104(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -116(%rbp)
	leaq	-116(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi
	addq	$4, -104(%rbp)
.L56:
	movq	-104(%rbp), %rax
	cmpq	-88(%rbp), %rax
	jne	.L57
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE4sortEv
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L59
	call	__stack_chk_fail@PLT
.L59:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2610:
	.size	main, .-main
	.weak	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8_S_mutexE
	.section	.bss._ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8_S_mutexE,"awG",@nobits,_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8_S_mutexE,comdat
	.align 32
	.type	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8_S_mutexE, @gnu_unique_object
	.size	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8_S_mutexE, 40
_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8_S_mutexE:
	.zero	40
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEEC2INS1_INS_10_list_implIiS2_EEEEEEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEEC5INS1_INS_10_list_implIiS2_EEEEEEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEEC2INS1_INS_10_list_implIiS2_EEEEEEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEEC2INS1_INS_10_list_implIiS2_EEEEEEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEEC2INS1_INS_10_list_implIiS2_EEEEEEv:
.LFB2959:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-9(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm
	movq	-24(%rbp), %rdx
	movq	%rax, (%rdx)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	leaq	-9(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L61
	call	__stack_chk_fail@PLT
.L61:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2959:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEEC2INS1_INS_10_list_implIiS2_EEEEEEv, .-_ZN4ustl4listIiNS_9allocatorIiEEEC2INS1_INS_10_list_implIiS2_EEEEEEv
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEEC1INS1_INS_10_list_implIiS2_EEEEEEv
	.set	_ZN4ustl4listIiNS_9allocatorIiEEEC1INS1_INS_10_list_implIiS2_EEEEEEv,_ZN4ustl4listIiNS_9allocatorIiEEEC2INS1_INS_10_list_implIiS2_EEEEEEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi, @function
_ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi:
.LFB2961:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl7forwardIKiEEOT_RS2_
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv
	movq	%rax, %rcx
	movq	-24(%rbp), %rax
	movq	%rbx, %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2961:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi, .-_ZN4ustl4listIiNS_9allocatorIiEEE9push_backERKi
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE4sortEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE4sortEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE4sortEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE4sortEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE4sortEv:
.LFB2962:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$576, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -584(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-568(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEEC1INS1_INS_10_list_implIiS2_EEEEEEv
	leaq	-544(%rbp), %rax
	movl	$63, %ebx
	movq	%rax, %r12
	jmp	.L64
.L65:
	movq	%r12, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEEC1INS1_INS_10_list_implIiS2_EEEEEEv
	addq	$8, %r12
	subq	$1, %rbx
.L64:
	testq	%rbx, %rbx
	jns	.L65
	movq	$0, -560(%rbp)
.L71:
	movq	-584(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv
	movq	%rax, %rbx
	leaq	-568(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv
	movq	%rax, %rsi
	movq	-584(%rbp), %rdx
	leaq	-568(%rbp), %rax
	movq	%rbx, %rcx
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_
	movq	$0, -552(%rbp)
	jmp	.L66
.L69:
	leaq	-544(%rbp), %rdx
	movq	-552(%rbp), %rax
	salq	$3, %rax
	addq	%rax, %rdx
	leaq	-568(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_
	addq	$1, -552(%rbp)
.L66:
	movq	-552(%rbp), %rax
	cmpq	-560(%rbp), %rax
	je	.L67
	leaq	-544(%rbp), %rdx
	movq	-552(%rbp), %rax
	salq	$3, %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv
	testq	%rax, %rax
	je	.L67
	movl	$1, %eax
	jmp	.L68
.L67:
	movl	$0, %eax
.L68:
	testb	%al, %al
	jne	.L69
	leaq	-544(%rbp), %rdx
	movq	-552(%rbp), %rax
	salq	$3, %rax
	addq	%rax, %rdx
	leaq	-568(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_
	movq	-552(%rbp), %rax
	cmpq	-560(%rbp), %rax
	jne	.L70
	addq	$1, -560(%rbp)
.L70:
	movq	-584(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv
	testq	%rax, %rax
	setne	%al
	testb	%al, %al
	jne	.L71
	movq	$1, -552(%rbp)
	jmp	.L72
.L73:
	leaq	-544(%rbp), %rdx
	movq	-552(%rbp), %rax
	salq	$3, %rax
	addq	%rax, %rdx
	leaq	-568(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_
	addq	$1, -552(%rbp)
.L72:
	movq	-552(%rbp), %rax
	cmpq	-560(%rbp), %rax
	jne	.L73
	leaq	-568(%rbp), %rdx
	movq	-584(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_
	nop
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L74
	call	__stack_chk_fail@PLT
.L74:
	addq	$576, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2962:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE4sortEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE4sortEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv:
.LFB2963:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv
	movq	%rax, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE3endEv
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -32(%rbp)
	jmp	.L76
.L79:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEdeEv
	movl	(%rax), %ebx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEdeEv
	movl	(%rax), %eax
	cmpl	%eax, %ebx
	sete	%al
	testb	%al, %al
	je	.L77
	movq	-32(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE
	jmp	.L78
.L77:
	movq	-32(%rbp), %rax
	movq	%rax, -48(%rbp)
.L78:
	movq	-48(%rbp), %rax
	movq	%rax, -32(%rbp)
.L76:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEppEv
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN4ustlneENS_14_list_iteratorIiEES1_
	testb	%al, %al
	jne	.L79
	nop
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L80
	call	__stack_chk_fail@PLT
.L80:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2963:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE6uniqueEv
	.weak	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE
	.section	.bss._ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE,"awG",@nobits,_ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE,comdat
	.align 32
	.type	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE, @gnu_unique_object
	.size	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE, 40
_ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE:
	.zero	40
	.section	.text._ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm,"axG",@progbits,_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm,comdat
	.align 2
	.weak	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm
	.type	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm, @function
_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm:
.LFB3051:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3051
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	$0, -80(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L82
	movq	-96(%rbp), %rax
	salq	$5, %rax
	movq	%rax, -72(%rbp)
	cmpq	$256, -72(%rbp)
	jbe	.L83
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	jmp	.L84
.L83:
	movq	-72(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic16_M_get_free_listEm
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8_S_mutexE(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSt11unique_lockISt5mutexEC1ERS0_
.LEHE0:
	cmpq	$0, -56(%rbp)
	jne	.L85
	movq	-72(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZN4ustl14align_compressEmm
	movq	%rax, %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB1:
	call	_ZN4ustl15allocator_basic9_M_refillEm
	movq	%rax, -80(%rbp)
	jmp	.L86
.L85:
	movq	-56(%rbp), %rax
	movq	(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rax
	movq	%rax, -80(%rbp)
.L86:
	cmpq	$0, -80(%rbp)
	jne	.L87
	movl	$16, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	movq	$0, (%rbx)
	movq	$0, 8(%rbx)
	movq	%rbx, %rdi
	call	_ZN4ustl9bad_allocC1Ev
	leaq	_ZN4ustl9bad_allocD1Ev(%rip), %rax
	movq	%rax, %rdx
	leaq	_ZTIN4ustl9bad_allocE(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	__cxa_throw@PLT
.LEHE1:
.L87:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexED1Ev
.L82:
	movq	-80(%rbp), %rax
.L84:
	movq	-24(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L89
	jmp	.L91
.L90:
	endbr64
	movq	%rax, %rbx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
.L91:
	call	__stack_chk_fail@PLT
.L89:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3051:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm,"aG",@progbits,_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm,comdat
.LLSDA3051:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3051-.LLSDACSB3051
.LLSDACSB3051:
	.uleb128 .LEHB0-.LFB3051
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB3051
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L90-.LFB3051
	.uleb128 0
	.uleb128 .LEHB2-.LFB3051
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE3051:
	.section	.text._ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm,"axG",@progbits,_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm,comdat
	.size	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm, .-_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE8allocateEm
	.section	.text._ZN4ustl10_list_implIiNS_9allocatorIiEEEC2Ev,"axG",@progbits,_ZN4ustl10_list_implIiNS_9allocatorIiEEEC5Ev,comdat
	.align 2
	.weak	_ZN4ustl10_list_implIiNS_9allocatorIiEEEC2Ev
	.type	_ZN4ustl10_list_implIiNS_9allocatorIiEEEC2Ev, @function
_ZN4ustl10_list_implIiNS_9allocatorIiEEEC2Ev:
.LFB3060:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl12_list_headerC1Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3060:
	.size	_ZN4ustl10_list_implIiNS_9allocatorIiEEEC2Ev, .-_ZN4ustl10_list_implIiNS_9allocatorIiEEEC2Ev
	.weak	_ZN4ustl10_list_implIiNS_9allocatorIiEEEC1Ev
	.set	_ZN4ustl10_list_implIiNS_9allocatorIiEEEC1Ev,_ZN4ustl10_list_implIiNS_9allocatorIiEEEC2Ev
	.section	.text._ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_,"axG",@progbits,_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_,comdat
	.align 2
	.weak	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_
	.type	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_, @function
_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_:
.LFB3058:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$32, %edi
	call	_ZnwmPv
	movq	%rax, %rbx
	movq	$0, (%rbx)
	movq	$0, 8(%rbx)
	movq	$0, 16(%rbx)
	movq	$0, 24(%rbx)
	movq	%rbx, %rdi
	call	_ZN4ustl10_list_implIiNS_9allocatorIiEEEC1Ev
	movq	%rbx, %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3058:
	.size	_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_, .-_ZN4ustl9allocatorINS_10_list_implIiNS0_IiEEEEE9constructIS3_JEEEPT_S7_DpOT0_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv:
.LFB3062:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	_ZNK4ustl12_list_header7_M_lastEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3062:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE6_M_endEv
	.section	.text._ZN4ustl7forwardIKiEEOT_RS2_,"axG",@progbits,_ZN4ustl7forwardIKiEEOT_RS2_,comdat
	.weak	_ZN4ustl7forwardIKiEEOT_RS2_
	.type	_ZN4ustl7forwardIKiEEOT_RS2_, @function
_ZN4ustl7forwardIKiEEOT_RS2_:
.LFB3063:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3063:
	.size	_ZN4ustl7forwardIKiEEOT_RS2_, .-_ZN4ustl7forwardIKiEEOT_RS2_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_, @function
_ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_:
.LFB3064:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl7forwardIOKiEEOT_RS3_
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl16_list_node_basic7_M_hookEPS0_
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZN4ustl12_list_header11_M_inc_sizeEi
	movq	-16(%rbp), %rdx
	leaq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEC1EPNS_16_list_node_basicE
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L101
	call	__stack_chk_fail@PLT
.L101:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3064:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_, .-_ZN4ustl4listIiNS_9allocatorIiEEE9_M_insertIJKiEEENS_14_list_iteratorIiEEPNS_16_list_node_basicEDpOT_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE5beginEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv:
.LFB3065:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv
	movq	%rax, %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEC1EPNS_16_list_node_basicE
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L104
	call	__stack_chk_fail@PLT
.L104:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3065:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_, @function
_ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_:
.LFB3066:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	cmpq	-40(%rbp), %rax
	je	.L109
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEppEv
	movq	%rax, %rcx
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZN4ustl12_list_header11_M_inc_sizeEi
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZN4ustl12_list_header11_M_dec_sizeEi
	jmp	.L105
.L109:
	nop
.L105:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L108
	call	__stack_chk_fail@PLT
.L108:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3066:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_, .-_ZN4ustl4listIiNS_9allocatorIiEEE6spliceENS_14_list_iteratorIiEERS3_S5_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv:
.LFB3067:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	24(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3067:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE4sizeEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_, @function
_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_:
.LFB3068:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-80(%rbp), %rax
	cmpq	-72(%rbp), %rax
	je	.L122
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv
	movq	%rax, -64(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE3endEv
	movq	%rax, -56(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE5beginEv
	movq	%rax, -48(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE3endEv
	movq	%rax, -40(%rbp)
	jmp	.L115
.L120:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEdeEv
	movl	(%rax), %ebx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEdeEv
	movl	(%rax), %eax
	cmpl	%eax, %ebx
	setl	%al
	testb	%al, %al
	je	.L116
	movq	-48(%rbp), %rax
	movq	%rax, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEppEv
	movq	%rax, %rcx
	movq	-48(%rbp), %rdx
	movq	-64(%rbp), %rsi
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_
	movq	-32(%rbp), %rax
	movq	%rax, -48(%rbp)
	jmp	.L117
.L116:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEppEv
.L117:
	movq	-40(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustlneENS_14_list_iteratorIiEES1_
	testb	%al, %al
	je	.L115
	movq	-40(%rbp), %rcx
	movq	-48(%rbp), %rdx
	movq	-64(%rbp), %rsi
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_
.L115:
	movq	-40(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustlneENS_14_list_iteratorIiEES1_
	testb	%al, %al
	je	.L118
	movq	-56(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustlneENS_14_list_iteratorIiEES1_
	testb	%al, %al
	je	.L118
	movl	$1, %eax
	jmp	.L119
.L118:
	movl	$0, %eax
.L119:
	testb	%al, %al
	jne	.L120
	movq	-72(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm
	jmp	.L112
.L122:
	nop
.L112:
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L121
	call	__stack_chk_fail@PLT
.L121:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3068:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_, .-_ZN4ustl4listIiNS_9allocatorIiEEE5mergeERS3_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_, @function
_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_:
.LFB3069:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3069:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_, .-_ZN4ustl4listIiNS_9allocatorIiEEE4swapERS3_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE3endEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE3endEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE3endEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE3endEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE3endEv:
.LFB3070:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEC1EPNS_16_list_node_basicE
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L126
	call	__stack_chk_fail@PLT
.L126:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3070:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE3endEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE3endEv
	.section	.text._ZN4ustl14_list_iteratorIiEppEv,"axG",@progbits,_ZN4ustl14_list_iteratorIiEppEv,comdat
	.align 2
	.weak	_ZN4ustl14_list_iteratorIiEppEv
	.type	_ZN4ustl14_list_iteratorIiEppEv, @function
_ZN4ustl14_list_iteratorIiEppEv:
.LFB3071:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	8(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl14_list_iteratorIiEC1EPNS_16_list_node_basicE
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L129
	call	__stack_chk_fail@PLT
.L129:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3071:
	.size	_ZN4ustl14_list_iteratorIiEppEv, .-_ZN4ustl14_list_iteratorIiEppEv
	.section	.text._ZN4ustlneENS_14_list_iteratorIiEES1_,"axG",@progbits,_ZN4ustlneENS_14_list_iteratorIiEES1_,comdat
	.weak	_ZN4ustlneENS_14_list_iteratorIiEES1_
	.type	_ZN4ustlneENS_14_list_iteratorIiEES1_, @function
_ZN4ustlneENS_14_list_iteratorIiEES1_:
.LFB3072:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	cmpq	%rax, %rdx
	setne	%al
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3072:
	.size	_ZN4ustlneENS_14_list_iteratorIiEES1_, .-_ZN4ustlneENS_14_list_iteratorIiEES1_
	.section	.text._ZN4ustl14_list_iteratorIiEdeEv,"axG",@progbits,_ZN4ustl14_list_iteratorIiEdeEv,comdat
	.align 2
	.weak	_ZN4ustl14_list_iteratorIiEdeEv
	.type	_ZN4ustl14_list_iteratorIiEdeEv, @function
_ZN4ustl14_list_iteratorIiEdeEv:
.LFB3073:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	_ZN4ustl10_list_nodeIiE9_M_valptrEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3073:
	.size	_ZN4ustl14_list_iteratorIiEdeEv, .-_ZN4ustl14_list_iteratorIiEdeEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE, @function
_ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE:
.LFB3074:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl16_list_node_basic9_M_unhookEv
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZN4ustl12_list_header11_M_dec_sizeEi
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3074:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE, .-_ZN4ustl4listIiNS_9allocatorIiEEE8_M_eraseEPNS_16_list_node_basicE
	.section	.text._ZNSt11unique_lockISt5mutexEC2ERS0_,"axG",@progbits,_ZNSt11unique_lockISt5mutexEC5ERS0_,comdat
	.align 2
	.weak	_ZNSt11unique_lockISt5mutexEC2ERS0_
	.type	_ZNSt11unique_lockISt5mutexEC2ERS0_, @function
_ZNSt11unique_lockISt5mutexEC2ERS0_:
.LFB3113:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt11__addressofISt5mutexEPT_RS1_
	movq	-8(%rbp), %rdx
	movq	%rax, (%rdx)
	movq	-8(%rbp), %rax
	movb	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexE4lockEv
	movq	-8(%rbp), %rax
	movb	$1, 8(%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3113:
	.size	_ZNSt11unique_lockISt5mutexEC2ERS0_, .-_ZNSt11unique_lockISt5mutexEC2ERS0_
	.weak	_ZNSt11unique_lockISt5mutexEC1ERS0_
	.set	_ZNSt11unique_lockISt5mutexEC1ERS0_,_ZNSt11unique_lockISt5mutexEC2ERS0_
	.section	.text._ZNSt11unique_lockISt5mutexED2Ev,"axG",@progbits,_ZNSt11unique_lockISt5mutexED5Ev,comdat
	.align 2
	.weak	_ZNSt11unique_lockISt5mutexED2Ev
	.type	_ZNSt11unique_lockISt5mutexED2Ev, @function
_ZNSt11unique_lockISt5mutexED2Ev:
.LFB3116:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3116
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	8(%rax), %eax
	testb	%al, %al
	je	.L138
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexE6unlockEv
.L138:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3116:
	.section	.gcc_except_table._ZNSt11unique_lockISt5mutexED2Ev,"aG",@progbits,_ZNSt11unique_lockISt5mutexED5Ev,comdat
.LLSDA3116:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3116-.LLSDACSB3116
.LLSDACSB3116:
.LLSDACSE3116:
	.section	.text._ZNSt11unique_lockISt5mutexED2Ev,"axG",@progbits,_ZNSt11unique_lockISt5mutexED5Ev,comdat
	.size	_ZNSt11unique_lockISt5mutexED2Ev, .-_ZNSt11unique_lockISt5mutexED2Ev
	.weak	_ZNSt11unique_lockISt5mutexED1Ev
	.set	_ZNSt11unique_lockISt5mutexED1Ev,_ZNSt11unique_lockISt5mutexED2Ev
	.section	.text._ZN4ustl7forwardIOKiEEOT_RS3_,"axG",@progbits,_ZN4ustl7forwardIOKiEEOT_RS3_,comdat
	.weak	_ZN4ustl7forwardIOKiEEOT_RS3_
	.type	_ZN4ustl7forwardIOKiEEOT_RS3_, @function
_ZN4ustl7forwardIOKiEEOT_RS3_:
.LFB3118:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3118:
	.size	_ZN4ustl7forwardIOKiEEOT_RS3_, .-_ZN4ustl7forwardIOKiEEOT_RS3_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_, @function
_ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_:
.LFB3119:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl7forwardIKiEEOT_RS2_
	movq	%rax, %r12
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl10_list_nodeIiE9_M_valptrEv
	movq	%rax, %rbx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv
	movq	%r12, %rdx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_
	movq	-24(%rbp), %rax
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3119:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_, .-_ZN4ustl4listIiNS_9allocatorIiEEE14_M_create_nodeIJKiEEEPNS_10_list_nodeIiEEDpOT_
	.section	.text._ZN4ustl14_list_iteratorIiEC2EPNS_16_list_node_basicE,"axG",@progbits,_ZN4ustl14_list_iteratorIiEC5EPNS_16_list_node_basicE,comdat
	.align 2
	.weak	_ZN4ustl14_list_iteratorIiEC2EPNS_16_list_node_basicE
	.type	_ZN4ustl14_list_iteratorIiEC2EPNS_16_list_node_basicE, @function
_ZN4ustl14_list_iteratorIiEC2EPNS_16_list_node_basicE:
.LFB3121:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3121:
	.size	_ZN4ustl14_list_iteratorIiEC2EPNS_16_list_node_basicE, .-_ZN4ustl14_list_iteratorIiEC2EPNS_16_list_node_basicE
	.weak	_ZN4ustl14_list_iteratorIiEC1EPNS_16_list_node_basicE
	.set	_ZN4ustl14_list_iteratorIiEC1EPNS_16_list_node_basicE,_ZN4ustl14_list_iteratorIiEC2EPNS_16_list_node_basicE
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv:
.LFB3123:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	_ZNK4ustl12_list_header8_M_firstEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3123:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE8_M_beginEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_, @function
_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_:
.LFB3124:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-16(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl16_list_node_basic10_M_transerEPS0_S1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3124:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_, .-_ZN4ustl4listIiNS_9allocatorIiEEE10_M_transerENS_14_list_iteratorIiEES5_S5_
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm, @function
_ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm:
.LFB3125:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 24(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3125:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm, .-_ZN4ustl4listIiNS_9allocatorIiEEE11_M_set_sizeEm
	.section	.text._ZN4ustl10_list_nodeIiE9_M_valptrEv,"axG",@progbits,_ZN4ustl10_list_nodeIiE9_M_valptrEv,comdat
	.align 2
	.weak	_ZN4ustl10_list_nodeIiE9_M_valptrEv
	.type	_ZN4ustl10_list_nodeIiE9_M_valptrEv, @function
_ZN4ustl10_list_nodeIiE9_M_valptrEv:
.LFB3126:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$16, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3126:
	.size	_ZN4ustl10_list_nodeIiE9_M_valptrEv, .-_ZN4ustl10_list_nodeIiE9_M_valptrEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE, @function
_ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE:
.LFB3127:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv
	movq	%rax, %rcx
	movq	-16(%rbp), %rax
	movl	$1, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3127:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE, .-_ZN4ustl4listIiNS_9allocatorIiEEE11_M_put_nodeEPNS_16_list_node_basicE
	.section	.text._ZSt11__addressofISt5mutexEPT_RS1_,"axG",@progbits,_ZSt11__addressofISt5mutexEPT_RS1_,comdat
	.weak	_ZSt11__addressofISt5mutexEPT_RS1_
	.type	_ZSt11__addressofISt5mutexEPT_RS1_, @function
_ZSt11__addressofISt5mutexEPT_RS1_:
.LFB3172:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3172:
	.size	_ZSt11__addressofISt5mutexEPT_RS1_, .-_ZSt11__addressofISt5mutexEPT_RS1_
	.section	.text._ZNSt11unique_lockISt5mutexE4lockEv,"axG",@progbits,_ZNSt11unique_lockISt5mutexE4lockEv,comdat
	.align 2
	.weak	_ZNSt11unique_lockISt5mutexE4lockEv
	.type	_ZNSt11unique_lockISt5mutexE4lockEv, @function
_ZNSt11unique_lockISt5mutexE4lockEv:
.LFB3173:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L154
	movl	$1, %edi
	call	_ZSt20__throw_system_errori@PLT
.L154:
	movq	-8(%rbp), %rax
	movzbl	8(%rax), %eax
	testb	%al, %al
	je	.L155
	movl	$35, %edi
	call	_ZSt20__throw_system_errori@PLT
.L155:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	_ZNSt5mutex4lockEv
	movq	-8(%rbp), %rax
	movb	$1, 8(%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3173:
	.size	_ZNSt11unique_lockISt5mutexE4lockEv, .-_ZNSt11unique_lockISt5mutexE4lockEv
	.section	.text._ZNSt11unique_lockISt5mutexE6unlockEv,"axG",@progbits,_ZNSt11unique_lockISt5mutexE6unlockEv,comdat
	.align 2
	.weak	_ZNSt11unique_lockISt5mutexE6unlockEv
	.type	_ZNSt11unique_lockISt5mutexE6unlockEv, @function
_ZNSt11unique_lockISt5mutexE6unlockEv:
.LFB3174:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	8(%rax), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L157
	movl	$1, %edi
	call	_ZSt20__throw_system_errori@PLT
.L157:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L159
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	_ZNSt5mutex6unlockEv
	movq	-8(%rbp), %rax
	movb	$0, 8(%rax)
.L159:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3174:
	.size	_ZNSt11unique_lockISt5mutexE6unlockEv, .-_ZNSt11unique_lockISt5mutexE6unlockEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv:
.LFB3175:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3175:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE11_M_get_nodeEv
	.section	.text._ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv,"axG",@progbits,_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv,comdat
	.align 2
	.weak	_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv
	.type	_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv, @function
_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv:
.LFB3176:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3176:
	.size	_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv, .-_ZN4ustl4listIiNS_9allocatorIiEEE21_M_get_node_allocatorEv
	.section	.text._ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_,"axG",@progbits,_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_,comdat
	.weak	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_
	.type	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_, @function
_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_:
.LFB3177:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl7forwardIKiEEOT_RS2_
	movq	%rax, %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3177:
	.size	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_, .-_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE9constructIiJKiEEEPT_RS4_S9_DpOT0_
	.section	.text._ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm,"axG",@progbits,_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm,comdat
	.weak	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm
	.type	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm, @function
_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm:
.LFB3178:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3178:
	.size	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm, .-_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE10deallocateERS4_Pvm
	.section	.text._ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m,"axG",@progbits,_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m,comdat
	.weak	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m
	.type	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m, @function
_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m:
.LFB3223:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3223:
	.size	_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m, .-_ZN4ustl15allocate_traitsINS_9allocatorINS_10_list_nodeIiEEEEE8allocateERS4_m
	.section	.text._ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_,"axG",@progbits,_ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_,comdat
	.align 2
	.weak	_ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_
	.type	_ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_, @function
_ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_:
.LFB3224:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl7forwardIKiEEOT_RS2_
	movl	(%rax), %ebx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$4, %edi
	call	_ZnwmPv
	movl	%ebx, (%rax)
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3224:
	.size	_ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_, .-_ZN4ustl9allocatorINS_10_list_nodeIiEEE9constructIiJKiEEEPT_S7_DpOT0_
	.section	.text._ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm,"axG",@progbits,_ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm,comdat
	.align 2
	.weak	_ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm
	.type	_ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm, @function
_ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm:
.LFB3225:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-88(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, -64(%rbp)
	cmpq	$0, -80(%rbp)
	je	.L171
	cmpq	$0, -88(%rbp)
	je	.L171
	cmpq	$256, -64(%rbp)
	jbe	.L173
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L171
.L173:
	movq	$0, -56(%rbp)
	movq	-64(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic16_M_get_free_listEm
	movq	%rax, -48(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, -40(%rbp)
	leaq	-32(%rbp), %rax
	leaq	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexEC1ERS0_
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, (%rax)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexED1Ev
.L171:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L174
	call	__stack_chk_fail@PLT
.L174:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3225:
	.size	_ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm, .-_ZN4ustl9allocatorINS_10_list_nodeIiEEE10deallocateEPvm
	.section	.text._ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm,"axG",@progbits,_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm,comdat
	.align 2
	.weak	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm
	.type	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm, @function
_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm:
.LFB3250:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3250
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	$0, -80(%rbp)
	cmpq	$0, -96(%rbp)
	je	.L176
	movq	-96(%rbp), %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, -72(%rbp)
	cmpq	$256, -72(%rbp)
	jbe	.L177
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	jmp	.L178
.L177:
	movq	-72(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN4ustl15allocator_basic16_M_get_free_listEm
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)
	leaq	-48(%rbp), %rax
	leaq	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8_S_mutexE(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB3:
	call	_ZNSt11unique_lockISt5mutexEC1ERS0_
.LEHE3:
	cmpq	$0, -56(%rbp)
	jne	.L179
	movq	-72(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZN4ustl14align_compressEmm
	movq	%rax, %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB4:
	call	_ZN4ustl15allocator_basic9_M_refillEm
	movq	%rax, -80(%rbp)
	jmp	.L180
.L179:
	movq	-56(%rbp), %rax
	movq	(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rax
	movq	%rax, -80(%rbp)
.L180:
	cmpq	$0, -80(%rbp)
	jne	.L181
	movl	$16, %edi
	call	__cxa_allocate_exception@PLT
	movq	%rax, %rbx
	movq	$0, (%rbx)
	movq	$0, 8(%rbx)
	movq	%rbx, %rdi
	call	_ZN4ustl9bad_allocC1Ev
	leaq	_ZN4ustl9bad_allocD1Ev(%rip), %rax
	movq	%rax, %rdx
	leaq	_ZTIN4ustl9bad_allocE(%rip), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	__cxa_throw@PLT
.LEHE4:
.L181:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexED1Ev
.L176:
	movq	-80(%rbp), %rax
.L178:
	movq	-24(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L183
	jmp	.L185
.L184:
	endbr64
	movq	%rax, %rbx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11unique_lockISt5mutexED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB5:
	call	_Unwind_Resume@PLT
.LEHE5:
.L185:
	call	__stack_chk_fail@PLT
.L183:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3250:
	.section	.gcc_except_table._ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm,"aG",@progbits,_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm,comdat
.LLSDA3250:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3250-.LLSDACSB3250
.LLSDACSB3250:
	.uleb128 .LEHB3-.LFB3250
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB3250
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L184-.LFB3250
	.uleb128 0
	.uleb128 .LEHB5-.LFB3250
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE3250:
	.section	.text._ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm,"axG",@progbits,_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm,comdat
	.size	_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm, .-_ZN4ustl9allocatorINS_10_list_nodeIiEEE8allocateEm
	.weak	_ZTVN4ustl9bad_allocE
	.section	.data.rel.ro.local._ZTVN4ustl9bad_allocE,"awG",@progbits,_ZTVN4ustl9bad_allocE,comdat
	.align 8
	.type	_ZTVN4ustl9bad_allocE, @object
	.size	_ZTVN4ustl9bad_allocE, 40
_ZTVN4ustl9bad_allocE:
	.quad	0
	.quad	_ZTIN4ustl9bad_allocE
	.quad	_ZN4ustl9bad_allocD1Ev
	.quad	_ZN4ustl9bad_allocD0Ev
	.quad	_ZN4ustl9bad_alloc7messageEv
	.section	.text._ZN4ustl9bad_allocD2Ev,"axG",@progbits,_ZN4ustl9bad_allocD5Ev,comdat
	.align 2
	.weak	_ZN4ustl9bad_allocD2Ev
	.type	_ZN4ustl9bad_allocD2Ev, @function
_ZN4ustl9bad_allocD2Ev:
.LFB3270:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVN4ustl9bad_allocE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl9exceptionD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3270:
	.size	_ZN4ustl9bad_allocD2Ev, .-_ZN4ustl9bad_allocD2Ev
	.weak	_ZN4ustl9bad_allocD1Ev
	.set	_ZN4ustl9bad_allocD1Ev,_ZN4ustl9bad_allocD2Ev
	.section	.text._ZN4ustl9bad_allocD0Ev,"axG",@progbits,_ZN4ustl9bad_allocD5Ev,comdat
	.align 2
	.weak	_ZN4ustl9bad_allocD0Ev
	.type	_ZN4ustl9bad_allocD0Ev, @function
_ZN4ustl9bad_allocD0Ev:
.LFB3272:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4ustl9bad_allocD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3272:
	.size	_ZN4ustl9bad_allocD0Ev, .-_ZN4ustl9bad_allocD0Ev
	.weak	_ZTVN4ustl9exceptionE
	.section	.data.rel.ro._ZTVN4ustl9exceptionE,"awG",@progbits,_ZTVN4ustl9exceptionE,comdat
	.align 8
	.type	_ZTVN4ustl9exceptionE, @object
	.size	_ZTVN4ustl9exceptionE, 40
_ZTVN4ustl9exceptionE:
	.quad	0
	.quad	_ZTIN4ustl9exceptionE
	.quad	0
	.quad	0
	.quad	__cxa_pure_virtual
	.weak	_ZTIN4ustl9bad_allocE
	.section	.data.rel.ro._ZTIN4ustl9bad_allocE,"awG",@progbits,_ZTIN4ustl9bad_allocE,comdat
	.align 8
	.type	_ZTIN4ustl9bad_allocE, @object
	.size	_ZTIN4ustl9bad_allocE, 24
_ZTIN4ustl9bad_allocE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN4ustl9bad_allocE
	.quad	_ZTIN4ustl9exceptionE
	.weak	_ZTSN4ustl9bad_allocE
	.section	.rodata._ZTSN4ustl9bad_allocE,"aG",@progbits,_ZTSN4ustl9bad_allocE,comdat
	.align 16
	.type	_ZTSN4ustl9bad_allocE, @object
	.size	_ZTSN4ustl9bad_allocE, 18
_ZTSN4ustl9bad_allocE:
	.string	"N4ustl9bad_allocE"
	.weak	_ZTIN4ustl9exceptionE
	.section	.data.rel.ro._ZTIN4ustl9exceptionE,"awG",@progbits,_ZTIN4ustl9exceptionE,comdat
	.align 8
	.type	_ZTIN4ustl9exceptionE, @object
	.size	_ZTIN4ustl9exceptionE, 16
_ZTIN4ustl9exceptionE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN4ustl9exceptionE
	.weak	_ZTSN4ustl9exceptionE
	.section	.rodata._ZTSN4ustl9exceptionE,"aG",@progbits,_ZTSN4ustl9exceptionE,comdat
	.align 16
	.type	_ZTSN4ustl9exceptionE, @object
	.size	_ZTSN4ustl9exceptionE, 18
_ZTSN4ustl9exceptionE:
	.string	"N4ustl9exceptionE"
	.weak	__cxa_pure_virtual
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
