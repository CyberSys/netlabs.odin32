        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   GpiSetClipPath:PROC
        PUBLIC  _GpiSetClipPath
_GpiSetClipPath PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    call   GpiSetClipPath
    add    esp, 12
    pop    fs
    ret
_GpiSetClipPath ENDP

CODE32          ENDS

                END
