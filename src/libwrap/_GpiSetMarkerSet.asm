        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   GpiSetMarkerSet:PROC
        PUBLIC  _GpiSetMarkerSet
_GpiSetMarkerSet PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+12]
    push   dword ptr [esp+12]
    call   GpiSetMarkerSet
    add    esp, 8
    pop    fs
    ret
_GpiSetMarkerSet ENDP

CODE32          ENDS

                END
