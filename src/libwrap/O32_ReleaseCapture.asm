        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_ReleaseCapture:PROC
        PUBLIC  O32_ReleaseCapture
O32_ReleaseCapture PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    call   _O32_ReleaseCapture
    pop    fs
    ret
O32_ReleaseCapture ENDP

CODE32          ENDS

                END
