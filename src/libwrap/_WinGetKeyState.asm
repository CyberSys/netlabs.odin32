        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinGetKeyState:PROC
        PUBLIC  _WinGetKeyState
_WinGetKeyState PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+12]
    push   dword ptr [esp+12]
    call   WinGetKeyState
    add    esp, 8
    pop    fs
    ret
_WinGetKeyState ENDP

CODE32          ENDS

                END
