        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinStartTimer:PROC
        PUBLIC  _WinStartTimer
_WinStartTimer PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    call   WinStartTimer
    add    esp, 16
    pop    fs
    ret
_WinStartTimer ENDP

CODE32          ENDS

                END
