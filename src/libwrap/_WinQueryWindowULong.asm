        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinQueryWindowULong:PROC
        PUBLIC  _WinQueryWindowULong
_WinQueryWindowULong PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+12]
    push   dword ptr [esp+12]
    call   WinQueryWindowULong
    add    esp, 8
    pop    fs
    ret
_WinQueryWindowULong ENDP

CODE32          ENDS

                END
