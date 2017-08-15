%include "macro_common"

%include "asm_text.asm"
%if ($-$$) % 2 != 0
	nop
%endif

times (vs_dududu-vs_text) -($-$$) db fill_code
%include "asm_dududu.asm"
%if ($-$$) % 2 != 0
	nop
%endif

times (vs_dlgse-vs_dududu) -($-$$) db fill_code
%include "asm_dlgse.asm"
%if ($-$$) % 2 != 0
	nop
%endif

times (vs_aup-vs_dlgse) -($-$$) db fill_code
%include "asm_aup.asm"
%if ($-$$) % 2 != 0
	nop
%endif

times (vs_scode-vs_aup) -($-$$) db fill_code
%include "asm_scode.asm"
%if ($-$$) % 2 != 0
	nop
%endif

times (vs_ldscn-vs_scode) -($-$$) db fill_code
%include "asm_ldscn.asm"
%if ($-$$) % 2 != 0
	nop
%endif

times (vs_ldscnB-vs_ldscn) -($-$$) db fill_code
%include "asm_ldscnB.asm"
%if ($-$$) % 2 != 0
	nop
%endif

times 0x100-($-$$) db fill_code
