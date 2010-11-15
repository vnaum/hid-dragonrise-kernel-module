ifneq ($(KERNELRELEASE),)
obj-m	:= hid-aureal.o

else
KDIR	:= /lib/modules/$(shell uname -r)/build
INST	:= $(DESTDIR)/lib/modules/$(shell uname -r)/updates
PWD	:= $(shell pwd)

default:
	$(MAKE) -C $(KDIR)  SUBDIRS=$(PWD) modules
install: default
	[ -d $(INST) ] || mkdir $(INST)
	cp hid-aureal.ko $(INST)/
	depmod -a
uninstall:
	rm -f $(INST)/hid-aureal.ko
	depmod -a

endif


tempclean:
	rm -Rf *.o .tmp_versions .io.* *.mod.c Module.symvers

clean:
	rm -Rf *.ko *.o .tmp_versions .hid-aureal.* *.mod.c Module.symvers modules.order Module.markers
