        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinPostQueueMsg:PROC
        PUBLIC  _WinPostQueueMsg
_WinPostQueueMsg PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    push   dword ptr [esp+20]
    call   WinPostQueueMsg
    add    esp, 16
    pop    fs
    ret
_WinPostQueueMsg ENDP

CODE32          ENDS

                END
