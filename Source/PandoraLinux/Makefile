###############################################################################
#                                                     ZED for Pandora [Linux] #
###############################################################################
ifeq ($(strip $(ZEDPATH)),)
$(error "Please set ZEDPATH in your environment.  export ZEDPATH=/path/to/ZED")
endif

define \n

endef

ifeq ($(strip $(PNDSDK)),)
$(error $(\n)Please set PNDSDK in your environment:$(\n)$$ export PNDSDK=/path/to/PNDSDK)
endif

ifndef TOPDIR
export TOPDIR			:= $(shell cd ../../ && pwd)
export TOPSRC			:= $(TOPDIR)/Source
export BUILDDIR			:= $(shell pwd)
export PLATFORM			:= $(notdir $(CURDIR))
export ARCH				:= arm
export BUILD_PLATFORM	:= PANDORA_LINUX
export BUILD_ARCH		:= ARM
export BITSIZE			:= 32
export BUILD_TYPE		:= debug

export TOOL_PREFIX	:= $(PNDSDK)/bin/pandora-
export CPP			:= $(TOOL_PREFIX)g++
export AR			:= $(TOOL_PREFIX)ar
export GCCVER		:= $(shell $(CPP) -dumpversion)
endif

ifndef TARGETDIR
export TARGETDIR = $(TOPDIR)/Lib/$(PLATFORM)/$(ARCH)/$(BITSIZE)
export SOURCEDIR = .
export HEADERDIR = Headers
endif

COPYFILES ?= True

SUBDIRS			:= `find Source -type d | egrep -v '/\..*$$|^.$$'`
COMMONSUBDIRS	:= `find $(TOPSRC)/Common/Source -type d | egrep -v '/\..*$$|^.$$'`

debug: BUILD = debug
debug: ZED
ifeq ($(COPYFILES),True)
debug: copyfiles
endif

release: BUILD = release
release: ZED
ifeq ($(COPYFILES),True)
release: copyfiles
endif

profile: BUILD = profile
profile: ZED
ifeq ($(COPYFILES),True)
profile: copyfiles
endif

psdocs: BUILD = psdocs
psdocs: ZED

ZED:
	@for i in $(COMMONSUBDIRS); do if test -e \
	$$i/Makefile ; then $(MAKE) --no-print-directory -C $$i $(BUILD) COPYFILES=False \
	|| { exit 1; } fi; done;
	@for i in $(SUBDIRS); do if test -e \
	$$i/Makefile ; then $(MAKE) --no-print-directory -C $$i $(BUILD) \
	|| { exit 1; } fi; done;

.PHONY: clean
clean:
	@printf "Removing files from: /Obj ... "
	@rm -rf $(TOPDIR)/Obj
	@printf "[OK]\n"
	@printf "Removing files from: /Lib ... "
	@rm -rf $(TOPDIR)/Lib
	@printf "[OK]\n"

#####################
ifeq ($(COPYFILES), True)
.PHONY: copyfiles
$(ZEDPATH)/include/$(PLATFORM):
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"
	@printf "Creating directory: $(ZEDPATH)/include/$(PLATFORM) ... "
	@mkdir -p $(ZEDPATH)/include/$(PLATFORM)
	@printf "[OK]\n"
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"

$(ZEDPATH)/lib/$(PLATFORM)/$(ARCH)/$(BITSIZE):
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"
	@printf "Creating directory: $(ZEDPATH)/lib/$(PLATFORM)/$(ARCH)/$(BITSIZE) ... "
	@mkdir -p $(ZEDPATH)/lib/$(PLATFORM)/$(ARCH)/$(BITSIZE)
	@printf "[OK]\n"
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"

copyfiles: $(ZEDPATH)/include/$(PLATFORM) $(ZEDPATH)/lib/$(PLATFORM)/$(ARCH)/$(BITSIZE)
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"
	@printf "Copying local header files to: $(ZEDPATH)/include/$(PLATFORM) ..."
	@printf " "
	@cp -rf $(BUILDDIR)/Headers/* $(ZEDPATH)/include/$(PLATFORM)/
	@printf "[OK]\n"
	@printf "Copying common header files to: $(ZEDPATH)/include/$(PLATFORM) .."
	@printf ". "
	@cp -rf $(TOPSRC)/Common/Headers/* $(ZEDPATH)/include/$(PLATFORM)/
	@printf "[OK]\n"
	@printf "Copying library files to $(ZEDPATH)/lib/$(PLATFORM)/$(ARCH)/$(BITSIZE) ... "
	@files=$$(ls $(TARGETDIR)/*.a 2> /dev/null | wc -l);\
	if [ "$$files" != "0" ] ; then cp -f $(TARGETDIR)/*.a \
	$(ZEDPATH)/lib/$(PLATFORM)/$(ARCH)/$(BITSIZE)/; fi
	@files=$$(ls $(TARGETDIR)/*.so 2> /dev/null | wc -l);\
	if [ "$$files" != "0" ] ; then cp -f $(TARGETDIR)/*.so \
	$(ZEDPATH)/lib/$(PLATFORM)/$(ARCH)/$(BITSIZE)/; fi
	@printf "[OK]\n"
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"
endif
#####################

