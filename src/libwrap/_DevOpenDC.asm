        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DevOpenDC:PROC
        PUBLIC  _DevOpenDC
_DevOpenDC PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    call   DevOpenDC
    add    esp, 24
    pop    fs
    ret
_DevOpenDC ENDP

CODE32          ENDS

                END
