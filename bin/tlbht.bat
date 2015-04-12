tlbcpm CPP -DCPM -DHI_TECH -Dz80 -I %1.c temp1.out
tlbcpm htP1 -S temp1.out temp2.out 
tlbcpm htcGEN temp1.out temp2.out %1.AS
tlbcpm htzas xxx %1.AS
tlbcpm htlink -c100h -o%1.COM crtcpm.obj %1.obj libc.lib


