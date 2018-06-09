-------- PROJECT GENERATOR --------
PROJECT NAME :	porola
PROJECT DIRECTORY :	C:\WorkSpace\porola\porola
CPU SERIES :	RX600
CPU TYPE :	RX62N
TOOLCHAIN NAME :	Renesas RX Standard Toolchain
TOOLCHAIN VERSION :	1.1.0.0
GENERATION FILES :
    C:\WorkSpace\porola\porola\dbsct.c
        Setting of B,R Section
    C:\WorkSpace\porola\porola\typedefine.h
        Aliases of Integer Type
    C:\WorkSpace\porola\porola\sbrk.c
        Program of sbrk
    C:\WorkSpace\porola\porola\iodefine.h
        Definition of I/O Register
    C:\WorkSpace\porola\porola\intprg.c
        Interrupt Program
    C:\WorkSpace\porola\porola\vecttbl.c
        Initialize of Vector Table
    C:\WorkSpace\porola\porola\vect.h
        Definition of Vector
    C:\WorkSpace\porola\porola\resetprg.c
        Reset Program
    C:\WorkSpace\porola\porola\porola.c
        Main Program
    C:\WorkSpace\porola\porola\sbrk.h
        Header file of sbrk file
    C:\WorkSpace\porola\porola\stacksct.h
        Setting of Stack area
START ADDRESS OF SECTION :
 H'1000	B_1,R_1,B_2,R_2,B,R,SU,SI
 H'FFFF8000	PResetPRG
 H'FFFF8100	C_1,C_2,C,C$*,D_1,D_2,D,P,PIntPRG,W*,L
 H'FFFFFFD0	FIXEDVECT

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start 0xFFFF8000.
* RAM start 0x1000.

DATE & TIME : 2018/05/09 22:26:23
