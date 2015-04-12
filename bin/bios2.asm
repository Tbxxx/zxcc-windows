; BIOS / BDOS for the ZXCC environment.
;
; Modified by Tom Burnett for dual (testing/tflag) use
; assemble with George Phillip's zmac
;
	org	0FE00h
	DEFB	'ZXCC04'	;Serial number
;
; Some CP/M programs expect a jump at the start of BDOS, so here it is.
;
BDOS0:	JP	BDOS1

BDOS1:	LD	A,0C0h
	DEFB	0EDh,0FEh
	RET
;
;This is not a real BIOS, so let its code live below the BIOS jumpblock.
;
UBIOS:	LD	(XIX),IX
	POP	IX		;IX = address of UBIOS function
;
; ZXCC was written on the assumption that the BIOS jumpblock was a series 
; of CALL UBIOS instructions; in which case, IX would be the return address,
; or the address of the jumpblock entry plus 3.
;
; Now that the BIOS jumpblock is a true jumpblock and the CALL instructions 
; are elsewhere, the offset is relative to BIOS2 rather than CONST0. So 
; adjust the offset.
;
	PUSH	DE
	LD	DE,CONST0 - BIOS2
	ADD	IX,DE
	POP	DE
	LD	A,0C3h		;C3h = BIOS call
	DEFB	0EDh,0FEh	;ZXCC trap; IX = BIOS function
	LD	IX,(XIX)
	RET
;
XIX:	DEFW	0
;
; Location to start 0x100 transient program run.
; It's done here just in case the tpa program does a RET instead of a
; jp 0000h that would be a warm start BIOS call.  For example, BDS C
; does this
BEGIN:
		CALL	0100h	; run tpa program
		JP		CBOOT	; leave program via c code
		HALT			; stop the show if this doesn't work for some reason	
		

; CBOOT now leaves program via an exit(1) in the C code
; *.com file loading is handled from main()
CBOOT:	CALL	UBIOS	; Program termination via C code
WBOOT:  CALL	UBIOS   ; Program termination via C code
;
; Implementation of all other BIOS functions
;
BIOS2:	CALL	UBIOS	
BIOS3:	CALL	UBIOS	
BIOS4:	CALL	UBIOS	
BIOS5:	CALL	UBIOS	
BIOS6:	CALL	UBIOS	
BIOS7:	CALL	UBIOS	
BIOS8:	CALL	UBIOS	
BIOS9:	CALL	UBIOS	
BIOS10:	CALL	UBIOS	
BIOS11:	CALL	UBIOS	
BIOS12:	CALL	UBIOS	
BIOS13:	CALL	UBIOS	
BIOS14:	CALL	UBIOS	
BIOS15:	CALL	UBIOS	
BIOS16:	CALL	UBIOS	
BIOS17:	CALL	UBIOS	
BIOS18:	CALL	UBIOS	
BIOS19:	CALL	UBIOS	
BIOS20:	CALL	UBIOS	
BIOS21:	CALL	UBIOS	
BIOS22:	CALL	UBIOS	
BIOS23:	CALL	UBIOS	
BIOS24:	CALL	UBIOS	
BIOS25:	CALL	UBIOS	
BIOS26:	CALL	UBIOS	
BIOS27:	CALL	UBIOS	
BIOS28:	CALL	UBIOS	
BIOS29:	CALL	UBIOS	
BIOS30:	CALL	UBIOS	
BIOS31:	CALL	UBIOS	
BIOS32:	CALL	UBIOS	
;
;
	org	0FEECh
tmpdrv:	defb	0FFh		;Temp drive = current


;
;TODO: SCB at FE9Ch
;

;
; Mallard BASIC (and maybe other programs) assumes that the BIOS 
; jumpblock is a list of jumps, not calls. So rather than composing the
; BIOS jumpblock of a sequence of CALL UBIOS, it's now a sequence
; of jumps to CALL UBIOS.
;
	org	0FF00h
	JP	CBOOT	;FF00
WBOOT0:	JP	WBOOT	;03
CONST0:	JP	BIOS2
	JP	BIOS3
	JP	BIOS4
	JP	BIOS5
	JP	BIOS6
	JP	BIOS7
	JP	BIOS8
	JP	BIOS9
	JP	BIOS10
	JP	BIOS11
	JP	BIOS12
	JP	BIOS13
	JP	BIOS14
	JP	BIOS15
	JP	BIOS16
	JP	BIOS17
	JP	BIOS18
	JP	BIOS19
	JP	BIOS20
	JP	BIOS21
	JP	BIOS22
	JP	BIOS23
	JP	BIOS24
	JP	BIOS25
	JP	BIOS26
	JP	BIOS27
	JP	BIOS28
	JP	BIOS29
	JP	BIOS30
	JP	BIOS31
	JP	BIOS32
;
	org	0FFC0h	;Space for DPB
dpb:	defs	20h

	END
	
