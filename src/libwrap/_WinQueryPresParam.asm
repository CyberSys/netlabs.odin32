        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinQueryPresParam:PROC
        PUBLIC  _WinQueryPresParam
_WinQueryPresParam PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+32]
    push   dword ptr [esp+32]
    push   dword ptr [esp+32]
    push   dword ptr [esp+32]
    push   dword ptr [esp+32]
    push   dword ptr [esp+32]
    push   dword ptr [esp+32]
    call   WinQueryPresParam
    add    esp, 28
    pop    fs
    ret
_WinQueryPresParam ENDP

CODE32          ENDS

                END
