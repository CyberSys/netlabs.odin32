        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinCalcFrameRect:PROC
        PUBLIC  _WinCalcFrameRect
_WinCalcFrameRect PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    call   WinCalcFrameRect
    add    esp, 12
    pop    fs
    ret
_WinCalcFrameRect ENDP

CODE32          ENDS

                END
