        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DosAllocSharedMem:PROC
        PUBLIC  _DosAllocSharedMem
_DosAllocSharedMem PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    call   DosAllocSharedMem
    add    esp, 16
    pop    fs
    ret
_DosAllocSharedMem ENDP

CODE32          ENDS

                END
