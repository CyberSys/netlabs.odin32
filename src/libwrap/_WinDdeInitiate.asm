        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinDdeInitiate:PROC
        PUBLIC  _WinDdeInitiate
_WinDdeInitiate PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    call   WinDdeInitiate
    add    esp, 16
    pop    fs
    ret
_WinDdeInitiate ENDP

CODE32          ENDS

                END
