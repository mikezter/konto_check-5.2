package main

/*
#cgo LDFLAGS: -lz
#cgo CFLAGS:
#include <stdlib.h>
#include "konto_check.c"
*/
import "C"

func Random() int {
	return int(C.random())
}

func Seed(i int) {
	C.srandom(C.uint(i))
}

func Check(blz string, kto string) int {
	return 0
}

func Msg(code C.int) string {
	return C.GoString(C.kto_check_retval2txt(code))
}

func init() {
	lut := C.CString("blz.lut2")
	retval := C.lut_init(lut, 5, 0)

	println(retval)
	println(Msg(retval))
	println(C.GoString(lut))

	if retval != C.OK {
		println("lut error")
	}

}

func main() {

}
