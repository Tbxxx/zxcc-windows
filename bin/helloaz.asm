	extrn	.begin,.chl,.swt
	extrn	csave,cret,.move
	PUBLIC main_
main_:	lxi d,.2
	call csave
	LXI H,.1+0
	PUSH H
	CALL printf_
	POP D
	RET
.2 EQU 0
.1:
	DB 72,101,108,108,111,44,32,119,111,114,108,100,32,102,114
	DB 111,109,32,65,122,116,101,99,32,67,46,10,0
	extrn	printf_
	END
