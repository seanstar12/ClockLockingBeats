obj-m += attestify.o
attestify-objs := clb_attestify.o

CROSS:= "~/Documents/android/aokp/prebuilts/gcc/linux-x86/arm/arm-eabi-4.7/bin/arm-eabi-" 
KERNEL:= "~/Documents/android/aokp/out/target/product/yuga/obj/KERNEL_OBJ"
ARCH:= arm

all:
	make -C $(KERNEL) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS)
clean:
	rm -f 	attestify.ko
	rm -f  	attestify.mod.c
	rm -f  	attestify.mod.o
	rm -f  	attestify.o
	rm -f  	built-in.o
	rm -f  	clb_attestify.o
	rm -f 	clb_attestify.mod.c
	rm -f  	modules.order
	rm -f  	Module.symvers
	rm -f 	.attestify.ko.cmd
	rm -f  	.attestify.mod.o.cmd
	rm -f  	.built-in.o.cmd
	rm -f  	.attestify.o.cmd
	rm -f  	.clb_attestify.o.cmd
	rm -f  	.tmp_versions/attestify.mod
	rmdir 	.tmp_versions/
