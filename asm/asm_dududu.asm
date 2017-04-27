%include "macro_common"

%define tmp _tmp(1)
%define vs vs_dududu

[BITS 32]
section dududu vstart=vs
	push    eax
	push    ebx
	call    dududu_start
dududu_start:
	pop     ebx
	pop     eax
	sub     ebx, 7 + vs
	mov     dword [ebx + tmp], eax
	pop     eax

checkcode:
	mov     al, byte [ebx + status_scode]
	cmp     al, byte [ebx + scode_TEXT]
	je      count
	cmp     al, byte [ebx + scode_SAY]
	je      count
	cmp     al, byte [ebx + scode_TALK]
	je      count
	jmp     dududu
count:
	cmp     dword [ebx + ptr_cnt], 0
	jne     notfirst
	mov     eax, dword [ebx + ptr_now]
	mov     dword [ebx + ptr_ttb], eax

notfirst:
	mov     eax, dword [ebx + ptr_cnt]
	inc     eax
	mov     dword [ebx + ptr_cnt], eax

dududu:
	cmp     byte [ebx + order_dududu], 0
	je      short close_dududu_over

%ifdef za
	mov     dword [esp + 0x0C], 0
%else
	mov     eax, dword [ebx + addr_mute]
	cmp     byte [eax], 0
	jne     short close_dududu_over

	mov     byte [eax], 1
	call    dword [ebx + to(jcs_dududu)]
	mov     eax, dword [ebx + addr_mute]
	mov     byte [eax], 0
	jmp     dududu_return
%endif

close_dududu_over:
	call    dword [ebx + to(jcs_dududu)]

dududu_return:
	push    dword [ebx + next(jcs_dududu)]
	mov     ebx, dword [ebx + tmp]
	ret

%undef tmp
%undef vs
