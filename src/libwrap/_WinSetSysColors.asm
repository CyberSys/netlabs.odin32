        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinSetSysColors:PROC
        PUBLIC  _WinSetSysColors
_WinSetSysColors PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    call   WinSetSysColors
    add    esp, 24
    pop    fs
    ret
_WinSetSysColors ENDP

CODE32          ENDS

                END
