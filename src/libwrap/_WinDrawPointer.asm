        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinDrawPointer:PROC
        PUBLIC  _WinDrawPointer
_WinDrawPointer PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+24]
    push   dword ptr [esp+24]
    push   dword ptr [esp+24]
    push   dword ptr [esp+24]
    push   dword ptr [esp+24]
    call   WinDrawPointer
    add    esp, 20
    pop    fs
    ret
_WinDrawPointer ENDP

CODE32          ENDS

                END
