htCPP -DCPM -DHI_TECH -Dz80 -I %1.c temp1.out
htP1 -S temp1.out temp2.out 
htcGEN temp1.out temp2.out %1.AS
htzas xxx %1.AS
htlinq -c100h -o%1.COM crtcpm.obj %1.obj libc.lib


