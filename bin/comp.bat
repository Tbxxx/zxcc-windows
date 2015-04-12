rm *.o
rm *.exe
rm os3bdos.hex os3bdos.prn os3bdos.sym
rem gcc zxcc.o zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L..\cpmredir\lib -lcpmredir -o zxcc
cd z80
gcc -O -c z80.c
cd ..
gcc -DHAVE_CONFIG_H -I. -I.. -Ik:/zxcc2/zxcc-0.5.7/cpmredir/include -DZXCC -O2 -c ccp_spt.c
gcc -DHAVE_CONFIG_H -I. -I.. -Ik:/zxcc2/zxcc-0.5.7/cpmredir/include -DZXCC -O2 -c ccp.c
gcc -DHAVE_CONFIG_H -I. -I.. -Ik:/zxcc2/zxcc-0.5.7/cpmredir/include -DZXCC -O2 -c zxbdos.c
gcc -DHAVE_CONFIG_H -I. -I.. -Ik:/zxcc2/zxcc-0.5.7/cpmredir/include -DZXCC -O2 -c zxcbdos.c
gcc -DHAVE_CONFIG_H -I. -I.. -Ik:/zxcc2/zxcc-0.5.7/cpmredir/include -DZXCC -O2 -c zxdbdos.c
gcc -DCPM -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o cpm
copy cpm.exe zxcc.exe
gcc -DMBASIC -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o mbasic
gcc -DM80NEW -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o m80new
gcc -DM80 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o m80
gcc -DBASCOM -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o bascom
gcc -DF80 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o f80
gcc -DOBASIC -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o obasic
gcc -DBDSCC -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o bdscc
gcc -DBDSCLINK -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o bdsclink
gcc -DAZCC -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o azcc
gcc -DAZAS -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o azas
gcc -DAZLN -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o azln
gcc -DHTC -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o htc
gcc -DHTP1 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o htp1
gcc -DHTCGEN -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o htcgen
gcc -DHTCPP -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L..\cpmredir\lib -lcpmredir -o htcpp
gcc -DHTZAS -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o htzas
gcc -DHTOPTIM -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o htoptim
 gcc -DHTLIBR -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o htlibr
rem attempt to fake out gcc
gcc -DXXXX -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o xxxx
copy xxxx.exe htlinq.exe
gcc -DL80 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o l80
gcc -DLD80 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o ld80
gcc -DZCPR -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o zcpr
gcc -DMSH -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o msh
gcc -DMAC -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o mac
gcc -DRMAC -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o rmac
gcc -DDRILINK -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o drilink
gcc -DDRILIB -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o drilib
gcc -DSLR180 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o slr180
gcc -DSLRZ80 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o slrz80
gcc -DSLRNK1 -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o slrnk1
gcc -DSLRIB -O2 -DHAVE_CONFIG_H -I. -I.. -Iprograms -I../cpmredir/include -DZXCC cpm.c zxbdos.o zxdbdos.o ccp.o ccp_spt.o z80/z80.o -L. -L..\cpmredir\lib -lcpmredir -o slrib
strip *.exe


