        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DrgSetDragImage:PROC
        PUBLIC  _DrgSetDragImage
_DrgSetDragImage PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    call   DrgSetDragImage
    add    esp, 16
    pop    fs
    ret
_DrgSetDragImage ENDP

CODE32          ENDS

                END
