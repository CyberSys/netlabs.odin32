        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinOpenClipbrd:PROC
        PUBLIC  _WinOpenClipbrd
_WinOpenClipbrd PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   WinOpenClipbrd
    add    esp, 4
    pop    fs
    ret
_WinOpenClipbrd ENDP

CODE32          ENDS

                END
