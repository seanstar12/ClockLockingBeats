default: all

.DEFAULT:
	cd collatz-kit && $(MAKE) $@
	cd cpulimit-simplified && $(MAKE) $@
	cd oc-me && $(MAKE) $@

stage-kit:
	#clobber the kit first
	#then 'make' it
	#then copy it here
	cp ./collatz-kit/collatz-kit ./clb_out/collatz-kit
	cp ./cpulimit-simplified/cpulimit-simplified ./clb_out/cpulimit-simplified
	cp ./oc-me/oc-me ./clb_out/oc-me

clean-kit:
	#also clobber the overall build
	rm ./clb_out/collatz-kit
	rm ./clb_out/cpulimit-simplified
	rm ./clb_out/oc-me

