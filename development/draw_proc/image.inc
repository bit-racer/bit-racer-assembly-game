
  shipOffsetX1             equ           0                                                                                                                                                                                                   	;position of first from left pixel
	shipOffsetY1             equ           0                                                                                                                                                                                                   	;position of first from top pix
	shipSizeX                equ          32                                                                                                                                                                                                    	;img Width
	shipSizeY                equ          32                                                                                                                                                                                                    	;img Height
	screenMaxY1              equ          370
	screenMaxX1              equ          320
	screenMinY1              equ          100
	screenMinX1              equ          4
  REV db 0
  Ers db 1


  Mikasa_Plane             DB           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                         DB           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                         DB           0, 0, 0, 0, 0, 0, 0, 0, 19, 19, 138, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19
	                         DB           138, 138, 138, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 138, 138, 138, 66, 138, 19, 0, 0, 0
	                         DB           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 138, 138, 138, 138, 138, 138, 19, 0, 0, 0, 0, 0, 0, 19, 19, 19, 19, 19
	                         DB           19, 19, 19, 19, 19, 19, 19, 19, 19, 0, 0, 0, 19, 138, 138, 138, 138, 66, 138, 19, 0, 0, 0, 0, 0, 0, 19, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29
	                         DB           29, 19, 19, 19, 19, 19, 19, 138, 66, 66, 138, 19, 0, 0, 0, 0, 0, 19, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 19, 19, 19, 19, 19, 19, 66
	                         DB           138, 66, 138, 19, 0, 0, 0, 0, 19, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 19, 19, 19, 19, 138, 66, 138, 138, 66, 138, 19, 0, 0, 0, 0
	                         DB           0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 23, 19, 19, 19, 66, 138, 66, 66, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                         DB           0, 19, 19, 138, 138, 138, 138, 138, 138, 19, 23, 23, 27, 27, 19, 138, 66, 66, 66, 66, 19, 0, 0, 0, 0, 0, 0, 0, 19, 19, 19, 19, 19, 66, 66, 66, 66, 66, 66, 66
	                         DB           66, 138, 19, 19, 19, 19, 138, 66, 66, 138, 138, 19, 19, 23, 23, 27, 0, 0, 19, 19, 66, 66, 91, 91, 91, 91, 66, 91, 66, 91, 66, 138, 138, 138, 91, 138, 66, 66, 91, 138
	                         DB           66, 66, 66, 66, 4, 65, 65, 23, 0, 19, 66, 91, 91, 4, 4, 4, 91, 91, 91, 91, 91, 66, 91, 66, 66, 66, 91, 66, 66, 91, 91, 66, 66, 66, 66, 66, 6, 64, 64, 64
	                         DB           19, 66, 91, 4, 64, 64, 64, 64, 4, 91, 91, 91, 66, 91, 66, 91, 91, 91, 91, 138, 66, 66, 91, 138, 66, 66, 138, 19, 67, 67, 67, 67, 19, 66, 91, 4, 64, 64, 64, 64
	                         DB           4, 91, 91, 91, 66, 91, 66, 91, 91, 91, 91, 138, 66, 66, 91, 138, 66, 66, 138, 19, 67, 67, 67, 67, 0, 19, 66, 91, 91, 4, 4, 4, 91, 91, 91, 91, 91, 66, 91, 66
	                         DB           66, 66, 91, 66, 66, 91, 91, 66, 66, 66, 66, 66, 6, 64, 64, 64, 0, 0, 19, 19, 66, 66, 91, 91, 91, 91, 66, 91, 66, 91, 66, 138, 138, 138, 91, 138, 66, 66, 91, 138
	                         DB           66, 66, 66, 66, 4, 65, 65, 23, 0, 0, 0, 0, 19, 19, 19, 19, 19, 66, 66, 66, 66, 66, 66, 66, 66, 138, 19, 19, 19, 19, 138, 66, 66, 138, 138, 19, 19, 23, 23, 27
	                         DB           0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 19, 138, 138, 138, 138, 138, 138, 19, 23, 23, 27, 27, 19, 138, 66, 66, 66, 66, 19, 0, 0, 0, 0, 19, 19, 19, 19, 19, 19, 19
	                         DB           19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 23, 19, 19, 19, 66, 138, 66, 66, 138, 19, 0, 0, 0, 0, 19, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27
	                         DB           27, 19, 19, 19, 19, 138, 66, 138, 138, 66, 138, 19, 0, 0, 0, 0, 0, 19, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 19, 19, 19, 19, 19, 19, 66
	                         DB           138, 66, 138, 19, 0, 0, 0, 0, 0, 0, 19, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 19, 19, 19, 19, 19, 19, 138, 66, 66, 138, 19, 0, 0, 0, 0
	                         DB           0, 0, 0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 0, 0, 0, 19, 138, 138, 138, 138, 66, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                         DB           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 138, 138, 138, 138, 138, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                         DB           0, 0, 0, 0, 0, 0, 19, 138, 138, 138, 66, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19
	                         DB           138, 138, 138, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 19, 138, 138, 19, 0, 0, 0
	                         DB           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 138, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                         DB           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 19, 0, 0, 0
	