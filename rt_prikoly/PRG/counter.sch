VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan2"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL CLK
        SIGNAL BUT
        SIGNAL MODE
        SIGNAL XLXN_65
        SIGNAL XLXN_66
        SIGNAL XLXN_67
        SIGNAL CE
        SIGNAL CLR
        SIGNAL Q(7)
        SIGNAL Q(6)
        SIGNAL Q(5)
        SIGNAL Q(4)
        SIGNAL Q(3)
        SIGNAL Q(2)
        SIGNAL Q(1)
        SIGNAL Q(0)
        SIGNAL LED7
        SIGNAL LED6
        SIGNAL LED5
        SIGNAL LED4
        SIGNAL LED3
        SIGNAL LED2
        SIGNAL LED1
        SIGNAL LED0
        SIGNAL D0
        SIGNAL D1
        SIGNAL D2
        SIGNAL D3
        SIGNAL D4
        SIGNAL D5
        SIGNAL D6
        SIGNAL D7
        SIGNAL Q(7:0)
        SIGNAL XLXN_475
        SIGNAL XLXN_476
        SIGNAL XLXN_477
        SIGNAL XLXN_491
        SIGNAL XLXN_492
        SIGNAL XLXN_493
        SIGNAL XLXN_494
        SIGNAL XLXN_495
        SIGNAL XLXN_496
        SIGNAL XLXN_497
        SIGNAL XLXN_498
        PORT Input CLK
        PORT Input BUT
        PORT Input MODE
        PORT Input CE
        PORT Input CLR
        PORT Output LED7
        PORT Output LED6
        PORT Output LED5
        PORT Output LED4
        PORT Output LED3
        PORT Output LED2
        PORT Output LED1
        PORT Output LED0
        PORT Output D0
        PORT Output D1
        PORT Output D2
        PORT Output D3
        PORT Output D4
        PORT Output D5
        PORT Output D6
        PORT Output D7
        BEGIN BLOCKDEF obuf
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 64 0 64 -64 
            LINE N 128 -32 64 0 
            LINE N 64 -64 128 -32 
            LINE N 0 -32 64 -32 
            LINE N 224 -32 128 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF muxf5
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 96 -64 96 -256 
            LINE N 256 -96 96 -64 
            LINE N 256 -224 256 -96 
            LINE N 96 -256 256 -224 
            LINE N 320 -128 256 -128 
            LINE N 0 -224 96 -224 
            LINE N 0 -32 96 -32 
            LINE N 0 -96 96 -96 
            LINE N 176 -32 96 -32 
            LINE N 176 -80 176 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF ibuf
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 64 0 64 -64 
            LINE N 128 -32 64 0 
            LINE N 64 -64 128 -32 
            LINE N 224 -32 128 -32 
            LINE N 0 -32 64 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF ibufg
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 64 0 64 -64 
            LINE N 128 -32 64 0 
            LINE N 64 -64 128 -32 
            LINE N 224 -32 128 -32 
            LINE N 0 -32 64 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF sr8ce
            TIMESTAMP 2000 1 1 10 10 10
            RECTANGLE N 320 -268 384 -244 
            LINE N 0 -192 64 -192 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 384 -256 320 -256 
            LINE N 0 -128 64 -128 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 0 -32 64 -32 
            LINE N 0 -320 64 -320 
            RECTANGLE N 64 -384 320 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF or8
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 48 -64 
            LINE N 0 -128 48 -128 
            LINE N 0 -192 48 -192 
            LINE N 0 -384 48 -384 
            LINE N 0 -448 48 -448 
            LINE N 0 -512 48 -512 
            LINE N 256 -288 192 -288 
            LINE N 0 -320 64 -320 
            LINE N 0 -256 64 -256 
            ARC N 28 -336 204 -160 192 -288 112 -336 
            LINE N 112 -240 48 -240 
            ARC N 28 -416 204 -240 112 -240 192 -288 
            ARC N -40 -344 72 -232 48 -240 48 -336 
            LINE N 112 -336 48 -336 
            LINE N 48 -336 48 -512 
            LINE N 48 -64 48 -240 
        END BLOCKDEF
        BEGIN BLOCKDEF inv
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -32 64 -32 
            LINE N 224 -32 160 -32 
            LINE N 64 -64 128 -32 
            LINE N 128 -32 64 0 
            LINE N 64 0 64 -64 
            CIRCLE N 128 -48 160 -16 
        END BLOCKDEF
        BEGIN BLOCKDEF xor2
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 64 -64 
            LINE N 0 -128 60 -128 
            LINE N 256 -96 208 -96 
            ARC N -40 -152 72 -40 48 -48 44 -144 
            ARC N -24 -152 88 -40 64 -48 64 -144 
            LINE N 128 -144 64 -144 
            LINE N 128 -48 64 -48 
            ARC N 44 -144 220 32 208 -96 128 -144 
            ARC N 44 -224 220 -48 128 -48 208 -96 
        END BLOCKDEF
        BEGIN BLOCKDEF or2
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 192 -96 
            ARC N 28 -224 204 -48 112 -48 192 -96 
            ARC N -40 -152 72 -40 48 -48 48 -144 
            LINE N 112 -144 48 -144 
            ARC N 28 -144 204 32 192 -96 112 -144 
            LINE N 112 -48 48 -48 
        END BLOCKDEF
        BEGIN BLOCK XLXI_34 muxf5
            PIN I0 XLXN_67
            PIN I1 XLXN_65
            PIN S XLXN_66
            PIN O XLXN_476
        END BLOCK
        BEGIN BLOCK XLXI_35 ibuf
            PIN I BUT
            PIN O XLXN_65
        END BLOCK
        BEGIN BLOCK XLXI_36 ibuf
            PIN I MODE
            PIN O XLXN_66
        END BLOCK
        BEGIN BLOCK XLXI_37 ibufg
            PIN I CLK
            PIN O XLXN_67
        END BLOCK
        BEGIN BLOCK XLXI_58 ibuf
            PIN I CE
            PIN O XLXN_477
        END BLOCK
        BEGIN BLOCK XLXI_62 ibuf
            PIN I CLR
            PIN O XLXN_475
        END BLOCK
        BEGIN BLOCK XLXI_33 obuf
            PIN I Q(7)
            PIN O LED7
        END BLOCK
        BEGIN BLOCK XLXI_32 obuf
            PIN I Q(6)
            PIN O LED6
        END BLOCK
        BEGIN BLOCK XLXI_31 obuf
            PIN I Q(5)
            PIN O LED5
        END BLOCK
        BEGIN BLOCK XLXI_30 obuf
            PIN I Q(4)
            PIN O LED4
        END BLOCK
        BEGIN BLOCK XLXI_29 obuf
            PIN I Q(3)
            PIN O LED3
        END BLOCK
        BEGIN BLOCK XLXI_28 obuf
            PIN I Q(2)
            PIN O LED2
        END BLOCK
        BEGIN BLOCK XLXI_27 obuf
            PIN I Q(1)
            PIN O LED1
        END BLOCK
        BEGIN BLOCK XLXI_26 obuf
            PIN I Q(0)
            PIN O LED0
        END BLOCK
        BEGIN BLOCK XLXI_9 obuf
            PIN I Q(0)
            PIN O D0
        END BLOCK
        BEGIN BLOCK XLXI_8 obuf
            PIN I Q(1)
            PIN O D1
        END BLOCK
        BEGIN BLOCK XLXI_7 obuf
            PIN I Q(2)
            PIN O D2
        END BLOCK
        BEGIN BLOCK XLXI_6 obuf
            PIN I Q(3)
            PIN O D3
        END BLOCK
        BEGIN BLOCK XLXI_5 obuf
            PIN I Q(4)
            PIN O D4
        END BLOCK
        BEGIN BLOCK XLXI_4 obuf
            PIN I Q(5)
            PIN O D5
        END BLOCK
        BEGIN BLOCK XLXI_3 obuf
            PIN I Q(6)
            PIN O D6
        END BLOCK
        BEGIN BLOCK XLXI_2 obuf
            PIN I Q(7)
            PIN O D7
        END BLOCK
        BEGIN BLOCK XLXI_284 sr8ce
            PIN C XLXN_476
            PIN CE XLXN_477
            PIN CLR XLXN_475
            PIN SLI XLXN_498
            PIN Q(7:0) Q(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_293 or8
            PIN I0 Q(0)
            PIN I1 Q(1)
            PIN I2 Q(2)
            PIN I3 Q(3)
            PIN I4 Q(4)
            PIN I5 Q(5)
            PIN I6 Q(6)
            PIN I7 Q(7)
            PIN O XLXN_491
        END BLOCK
        BEGIN BLOCK XLXI_294 inv
            PIN I XLXN_491
            PIN O XLXN_497
        END BLOCK
        BEGIN BLOCK XLXI_295 xor2
            PIN I0 Q(3)
            PIN I1 Q(7)
            PIN O XLXN_493
        END BLOCK
        BEGIN BLOCK XLXI_296 xor2
            PIN I0 Q(2)
            PIN I1 XLXN_493
            PIN O XLXN_495
        END BLOCK
        BEGIN BLOCK XLXI_297 xor2
            PIN I0 Q(1)
            PIN I1 XLXN_495
            PIN O XLXN_496
        END BLOCK
        BEGIN BLOCK XLXI_298 or2
            PIN I0 XLXN_496
            PIN I1 XLXN_497
            PIN O XLXN_498
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        BEGIN BRANCH CLK
            WIRE 176 768 224 768
        END BRANCH
        BEGIN BRANCH BUT
            WIRE 176 896 224 896
        END BRANCH
        BEGIN BRANCH MODE
            WIRE 208 960 224 960
        END BRANCH
        INSTANCE XLXI_34 480 992 R0
        BEGIN BRANCH XLXN_65
            WIRE 448 896 480 896
        END BRANCH
        INSTANCE XLXI_35 224 928 R0
        BEGIN BRANCH XLXN_66
            WIRE 448 960 480 960
        END BRANCH
        INSTANCE XLXI_36 224 992 R0
        BEGIN BRANCH XLXN_67
            WIRE 448 768 480 768
        END BRANCH
        INSTANCE XLXI_37 224 800 R0
        IOMARKER 208 960 MODE R180 28
        IOMARKER 176 896 BUT R180 28
        IOMARKER 176 768 CLK R180 28
        INSTANCE XLXI_58 640 656 R0
        BEGIN BRANCH CE
            WIRE 608 624 640 624
        END BRANCH
        IOMARKER 608 624 CE R180 28
        INSTANCE XLXI_62 656 1072 R0
        BEGIN BRANCH CLR
            WIRE 624 1040 656 1040
        END BRANCH
        IOMARKER 624 1040 CLR R180 28
        BUSTAP 1584 736 1680 736
        BUSTAP 1584 816 1680 816
        BUSTAP 1584 896 1680 896
        BUSTAP 1584 976 1680 976
        BUSTAP 1584 1056 1680 1056
        BUSTAP 1584 1136 1680 1136
        BUSTAP 1584 1216 1680 1216
        BUSTAP 1584 1296 1680 1296
        BEGIN BRANCH Q(4)
            WIRE 1680 976 1728 976
            WIRE 1728 976 1840 976
            BEGIN DISPLAY 1728 976 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(3)
            WIRE 1680 1056 1728 1056
            WIRE 1728 1056 1840 1056
            BEGIN DISPLAY 1728 1056 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(2)
            WIRE 1680 1136 1728 1136
            WIRE 1728 1136 1840 1136
            BEGIN DISPLAY 1728 1136 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 1584 96 1680 96
        BUSTAP 1584 176 1680 176
        BUSTAP 1584 256 1680 256
        BUSTAP 1584 336 1680 336
        BUSTAP 1584 416 1680 416
        BUSTAP 1584 496 1680 496
        BUSTAP 1584 576 1680 576
        BUSTAP 1584 656 1680 656
        BEGIN BRANCH Q(6)
            WIRE 1680 176 1744 176
            WIRE 1744 176 1840 176
            BEGIN DISPLAY 1752 176 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(5)
            WIRE 1680 256 1744 256
            WIRE 1744 256 1840 256
            BEGIN DISPLAY 1752 256 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(4)
            WIRE 1680 336 1744 336
            WIRE 1744 336 1840 336
            BEGIN DISPLAY 1752 336 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(3)
            WIRE 1680 416 1760 416
            WIRE 1760 416 1840 416
            BEGIN DISPLAY 1760 416 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(2)
            WIRE 1680 496 1760 496
            WIRE 1760 496 1840 496
            BEGIN DISPLAY 1756 496 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 1680 576 1744 576
            WIRE 1744 576 1840 576
            BEGIN DISPLAY 1740 576 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(0)
            WIRE 1680 656 1744 656
            WIRE 1744 656 1840 656
            BEGIN DISPLAY 1744 656 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        IOMARKER 2096 96 LED7 R0 28
        IOMARKER 2096 176 LED6 R0 28
        IOMARKER 2096 256 LED5 R0 28
        IOMARKER 2096 336 LED4 R0 28
        IOMARKER 2096 416 LED3 R0 28
        IOMARKER 2096 496 LED2 R0 28
        IOMARKER 2096 576 LED1 R0 28
        IOMARKER 2096 656 LED0 R0 28
        IOMARKER 2096 1296 D0 R0 28
        IOMARKER 2096 1216 D1 R0 28
        IOMARKER 2096 1136 D2 R0 28
        IOMARKER 2096 1056 D3 R0 28
        IOMARKER 2096 976 D4 R0 28
        IOMARKER 2096 896 D5 R0 28
        IOMARKER 2096 816 D6 R0 28
        IOMARKER 2096 736 D7 R0 28
        INSTANCE XLXI_33 1840 128 R0
        INSTANCE XLXI_32 1840 208 R0
        INSTANCE XLXI_31 1840 288 R0
        INSTANCE XLXI_30 1840 368 R0
        INSTANCE XLXI_29 1840 448 R0
        INSTANCE XLXI_28 1840 528 R0
        INSTANCE XLXI_27 1840 608 R0
        INSTANCE XLXI_26 1840 688 R0
        INSTANCE XLXI_9 1840 1328 R0
        INSTANCE XLXI_8 1840 1248 R0
        INSTANCE XLXI_7 1840 1168 R0
        INSTANCE XLXI_6 1840 1088 R0
        INSTANCE XLXI_5 1840 1008 R0
        INSTANCE XLXI_4 1840 928 R0
        INSTANCE XLXI_3 1840 848 R0
        INSTANCE XLXI_2 1840 768 R0
        BEGIN BRANCH LED7
            WIRE 2064 96 2096 96
        END BRANCH
        BEGIN BRANCH LED6
            WIRE 2064 176 2096 176
        END BRANCH
        BEGIN BRANCH LED5
            WIRE 2064 256 2096 256
        END BRANCH
        BEGIN BRANCH LED4
            WIRE 2064 336 2096 336
        END BRANCH
        BEGIN BRANCH LED3
            WIRE 2064 416 2096 416
        END BRANCH
        BEGIN BRANCH LED2
            WIRE 2064 496 2096 496
        END BRANCH
        BEGIN BRANCH LED1
            WIRE 2064 576 2096 576
        END BRANCH
        BEGIN BRANCH LED0
            WIRE 2064 656 2096 656
        END BRANCH
        BEGIN BRANCH D0
            WIRE 2064 1296 2096 1296
        END BRANCH
        BEGIN BRANCH D1
            WIRE 2064 1216 2096 1216
        END BRANCH
        BEGIN BRANCH D2
            WIRE 2064 1136 2096 1136
        END BRANCH
        BEGIN BRANCH D3
            WIRE 2064 1056 2096 1056
        END BRANCH
        BEGIN BRANCH D4
            WIRE 2064 976 2096 976
        END BRANCH
        BEGIN BRANCH D5
            WIRE 2064 896 2096 896
        END BRANCH
        BEGIN BRANCH D6
            WIRE 2064 816 2096 816
        END BRANCH
        BEGIN BRANCH D7
            WIRE 2064 736 2096 736
        END BRANCH
        BEGIN BRANCH Q(7)
            WIRE 1680 96 1776 96
            WIRE 1776 96 1840 96
            BEGIN DISPLAY 1772 96 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(7:0)
            WIRE 1392 736 1456 736
            WIRE 1456 736 1584 736
            WIRE 1584 736 1584 816
            WIRE 1584 816 1584 896
            WIRE 1584 896 1584 976
            WIRE 1584 976 1584 1056
            WIRE 1584 1056 1584 1136
            WIRE 1584 1136 1584 1216
            WIRE 1584 1216 1584 1296
            WIRE 1584 1296 1584 1376
            WIRE 1584 1376 1584 1440
            WIRE 1584 1440 1584 1504
            WIRE 1584 1504 1584 1568
            WIRE 1584 1568 1584 1632
            WIRE 1584 1632 1584 1696
            WIRE 1584 1696 1584 1760
            WIRE 1584 1760 1584 1824
            WIRE 1584 1824 1584 1936
            WIRE 1584 1936 1584 2000
            WIRE 1584 2000 1584 2016
            WIRE 1584 2016 1584 2064
            WIRE 1584 2064 1584 2096
            WIRE 1584 2096 1584 2112
            WIRE 1584 2112 1584 2160
            WIRE 1584 96 1584 176
            WIRE 1584 176 1584 256
            WIRE 1584 256 1584 336
            WIRE 1584 336 1584 416
            WIRE 1584 416 1584 496
            WIRE 1584 496 1584 576
            WIRE 1584 576 1584 656
            WIRE 1584 656 1584 736
            BEGIN DISPLAY 1456 736 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 1680 1216 1728 1216
            WIRE 1728 1216 1840 1216
            BEGIN DISPLAY 1728 1216 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(0)
            WIRE 1680 1296 1728 1296
            WIRE 1728 1296 1840 1296
            BEGIN DISPLAY 1728 1296 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_284 1008 992 R0
        BEGIN BRANCH XLXN_475
            WIRE 880 1040 1008 1040
            WIRE 1008 960 1008 1040
        END BRANCH
        BEGIN BRANCH XLXN_476
            WIRE 800 864 1008 864
        END BRANCH
        BEGIN BRANCH XLXN_477
            WIRE 864 624 928 624
            WIRE 928 624 928 800
            WIRE 928 800 1008 800
        END BRANCH
        BEGIN BRANCH Q(6)
            WIRE 1680 816 1728 816
            WIRE 1728 816 1808 816
            WIRE 1808 816 1840 816
            BEGIN DISPLAY 1728 816 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(5)
            WIRE 1680 896 1728 896
            WIRE 1728 896 1776 896
            WIRE 1776 896 1840 896
            BEGIN DISPLAY 1728 896 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Q(7)
            WIRE 1680 736 1744 736
            WIRE 1744 736 1808 736
            WIRE 1808 736 1840 736
            BEGIN DISPLAY 1744 736 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 1584 1376 1680 1376
        BUSTAP 1584 1440 1680 1440
        BUSTAP 1584 1504 1680 1504
        BUSTAP 1584 1568 1680 1568
        BUSTAP 1584 1632 1680 1632
        BUSTAP 1584 1696 1680 1696
        BUSTAP 1584 1760 1680 1760
        BUSTAP 1584 1824 1680 1824
        BEGIN BRANCH Q(7)
            WIRE 1680 1376 1840 1376
        END BRANCH
        BEGIN BRANCH Q(6)
            WIRE 1680 1440 1840 1440
        END BRANCH
        BEGIN BRANCH Q(5)
            WIRE 1680 1504 1840 1504
        END BRANCH
        BEGIN BRANCH Q(4)
            WIRE 1680 1568 1840 1568
        END BRANCH
        BEGIN BRANCH Q(3)
            WIRE 1680 1632 1840 1632
        END BRANCH
        BEGIN BRANCH Q(2)
            WIRE 1680 1696 1840 1696
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 1680 1760 1840 1760
        END BRANCH
        BEGIN BRANCH Q(0)
            WIRE 1680 1824 1840 1824
        END BRANCH
        BUSTAP 1584 2160 1680 2160
        BUSTAP 1584 2096 1680 2096
        BUSTAP 1584 2016 1680 2016
        BUSTAP 1584 1936 1680 1936
        BEGIN BRANCH Q(7)
            WIRE 1680 1936 1840 1936
            WIRE 1840 1936 1840 1952
            WIRE 1840 1952 1888 1952
        END BRANCH
        BEGIN BRANCH Q(3)
            WIRE 1680 2016 1840 2016
            WIRE 1840 2016 1888 2016
        END BRANCH
        BEGIN BRANCH Q(2)
            WIRE 1680 2096 1840 2096
            WIRE 1840 2048 2176 2048
            WIRE 1840 2048 1840 2096
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 1680 2160 1840 2160
            WIRE 1840 2160 2144 2160
            WIRE 2144 2080 2144 2160
            WIRE 2144 2080 2464 2080
        END BRANCH
        INSTANCE XLXI_293 1840 1888 R0
        BEGIN BRANCH XLXN_491
            WIRE 2096 1600 2128 1600
        END BRANCH
        INSTANCE XLXI_294 2128 1632 R0
        INSTANCE XLXI_295 1888 2080 R0
        BEGIN BRANCH XLXN_493
            WIRE 2144 1984 2176 1984
        END BRANCH
        INSTANCE XLXI_296 2176 2112 R0
        BEGIN BRANCH XLXN_495
            WIRE 2432 2016 2464 2016
        END BRANCH
        INSTANCE XLXI_297 2464 2144 R0
        INSTANCE XLXI_298 2784 1872 R0
        BEGIN BRANCH XLXN_496
            WIRE 2720 2048 2752 2048
            WIRE 2752 1808 2752 2048
            WIRE 2752 1808 2784 1808
        END BRANCH
        BEGIN BRANCH XLXN_497
            WIRE 2352 1600 2560 1600
            WIRE 2560 1600 2560 1744
            WIRE 2560 1744 2784 1744
        END BRANCH
        BEGIN BRANCH XLXN_498
            WIRE 944 672 1008 672
            WIRE 944 672 944 1904
            WIRE 944 1904 3120 1904
            WIRE 3040 1776 3120 1776
            WIRE 3120 1776 3120 1904
        END BRANCH
    END SHEET
END SCHEMATIC
