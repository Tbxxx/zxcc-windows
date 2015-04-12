time
erase tlb.com helloaz.com helloaz.o helloaz.asm helloz.com helloz.rel pi.com pi.rel test.rel test.com helloht.as helloht.obj helloht.com temp* os3*.sym os3*.hex os3*.prn
mbasic test
m80 helloz,helloz=helloz
l80 helloz,helloz/n/e
cpm helloz
bascom test,test=test
ld80 test,obslib/s,test/n/e
cpm test
f80 pi,pi=pi
ld80 pi,forlib/s,pi/n/e
cpm pi
azcc helloaz
azas helloaz
azln helloaz.o libc.lib
cpm helloaz
bdscc hellobds
bdsclink hellobds
cpm hellobds
htc helloht.c
cpm helloht
mac os3bdos
dir os3bdos.*
rmac os3rmac
dir os3rmac*
slr180 helloslr
slrnk1 helloslr,helloslr/n/e
cpm helloslr

time

