        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinValidateRegion:PROC
        PUBLIC  _WinValidateRegion
_WinValidateRegion PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    call   WinValidateRegion
    add    esp, 12
    pop    fs
    ret
_WinValidateRegion ENDP

CODE32          ENDS

                END
