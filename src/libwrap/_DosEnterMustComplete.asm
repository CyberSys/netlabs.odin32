        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DosEnterMustComplete:PROC
        PUBLIC  _DosEnterMustComplete
_DosEnterMustComplete PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   DosEnterMustComplete
    add    esp, 4
    pop    fs
    ret
_DosEnterMustComplete ENDP

CODE32          ENDS

                END
