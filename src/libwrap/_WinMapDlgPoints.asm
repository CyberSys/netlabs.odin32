        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinMapDlgPoints:PROC
        PUBLIC  _WinMapDlgPoints
_WinMapDlgPoints PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    call   WinMapDlgPoints
    add    esp, 16
    pop    fs
    ret
_WinMapDlgPoints ENDP

CODE32          ENDS

                END
