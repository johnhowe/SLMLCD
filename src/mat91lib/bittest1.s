	.file	"bittest1.c"
	.text
	.align	2
	.global	foo1
	.type	foo1, %function
foo1:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r0, r0, lsr #9
	and	r0, r0, #1
	@ lr needed for prologue
	bx	lr
	.size	foo1, .-foo1
	.align	2
	.global	foo2
	.type	foo2, %function
foo2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r0, r0, lsr #9
	and	r0, r0, #1
	@ lr needed for prologue
	bx	lr
	.size	foo2, .-foo2
	.ident	"GCC: (GNU) 4.3.0 20070531 (experimental)"
