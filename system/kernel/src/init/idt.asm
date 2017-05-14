;
;  Copyright (c) 2011-2014 Graham Edgecombe <graham@grahamedgecombe.com>
;
;  Permission to use, copy, modify, and/or distribute this software for any
;  purpose with or without fee is hereby granted, provided that the above
;  copyright notice and this permission notice appear in all copies.

[global idtr_install]
idtr_install:
	push rbp
	mov rbp, rsp
	lidt [rdi]
	pop rbp
	ret