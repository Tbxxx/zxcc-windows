psect	text
global	_main
_main:
global	ncsv, cret, indir
call	ncsv
defw	f29
global	_strcpy
ld	hl,19f
push	hl
push	ix
pop	de
ld	hl,-50
add	hl,de
push	hl
call	_strcpy
ld	hl,2+2
add	hl,sp
ld	sp,hl
ld	(ix+-52),.low.0
ld	(ix+1+-52),.high.0
jp	l6
l3:
global	_bios
push	ix
pop	de
ld	l,(ix+-52)
ld	h,(ix+1+-52)
add	hl,de
ld	de,-50
add	hl,de
ld	a,(hl)
ld	l,a
rla
sbc	a,a
ld	h,a
push	hl
ld	hl,2
push	hl
call	_bios
ld	hl,2+2
add	hl,sp
ld	sp,hl
l5:
ld	l,(ix+-52)
ld	h,(ix+1+-52)
inc	hl
ld	(ix+-52),l
ld	(ix+1+-52),h
l6:
push	ix
pop	de
ld	l,(ix+-52)
ld	h,(ix+1+-52)
add	hl,de
ld	de,-50
add	hl,de
ld	a,(hl)
or	a
jp	anz,l3
l4:
l2:
jp	cret
f29	equ	-52
psect	data
19:
defb	72,101,108,108,111,44,32,119,111,114,108,100,32,102,114,111
defb	109,32,72,105,116,101,99,104,32,67,10,0
,(ix+1+-52)
add	hl,de
ld	de,-50
add	hl,de
ld	a,(hl)
ld	l,a
rla