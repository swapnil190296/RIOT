.text

    .global aflCall
aflCall:
    // In qemu, svc $0x3f is intercepted, w/o really executing it
    // In real dev, it is executed, what's the expected result?
    // TODO simply return, conflict w/ some OS svc suage, or crash?
    // hypercall can be truned off by set noHyperCall to 0
    svc $0x3f
    // Why use bx rather than b?
    bx lr

    .global apiCallHelper
apiCallHelper:
    push	{r5, lr} 
    ldr		r5, [sp, $0x10]
    blx		r5 // TODO: Does blx r5 works on real device?
    pop		{r5, pc}
