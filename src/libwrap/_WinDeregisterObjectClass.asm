        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinDeregisterObjectClass:PROC
        PUBLIC  _WinDeregisterObjectClass
_WinDeregisterObjectClass PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   WinDeregisterObjectClass
    add    esp, 4
    pop    fs
    ret
_WinDeregisterObjectClass ENDP

CODE32          ENDS

                END
