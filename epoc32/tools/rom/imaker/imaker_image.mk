
# ============================================================================
#
#  Name        : imaker_image.mk
#  Part of     : iMaker
#  Description : Default iMaker image configuration
#  Version     : %version: 4 %
#
#  Copyright (c) 2008 Nokia.  All rights reserved.
#  This material, including documentation and any related computer
#  programs, is protected by copyright controlled by Nokia.  All
#  rights are reserved.  Copying, including reproducing, storing,
#  adapting or translating, any or all of this material requires the
#  prior written consent of Nokia.  This material also contains
#  confidential information which may not be disclosed to others
#  without the prior written consent of Nokia.
#
# ============================================================================



USE_FEATVAR    = $(call select,$(word 1,$(getsbvrominc)),invalid,0,1)
USE_FOTA       = 0
USE_IMGCHK     = 0
USE_IINTPRSIS  = 0
USE_IREADIMG   = 0
USE_IROMBLD    = 0
USE_OVERRIDE   = 1
USE_ROFS       = 1,2,3
USE_ROFSFILE   = $(call iif,$(USE_PAGING),1,0)
USE_ROMFILE    = 1
USE_SYMGEN     = 0
USE_UDEB       = 0
USE_VERGEN     = 0

$(foreach rofs,1 2 3 4 5 6,\
  $(eval USE_ROFS$(rofs) = $$(if $$(findstring $(rofs),$$(filter-out :%,$$(subst :, :,$$(subst $$(,), ,$$(USE_ROFS))))),1,0)))

#==============================================================================

TYPE = rnd

BUILD_INFOMK = image_conf_buildinfo.mk
BUILD_NAMEMK = image_conf_naming.mk
BUILD_YEAR   = $(YEAR)
BUILD_WEEK   = $(WEEK)
BUILD_NUMBER = xx

COREPLAT_NAME    =
COREPLAT_DIR     = $(CONFIGROOT)/$(COREPLAT_NAME)
COREPLAT_VERSION =
PLATFORM_NAME    = $(subst .,,$(COREPLAT_VERSION)$(S60_VERSION))
PLATFORM_DIR     = $(CONFIGROOT)/$(PLATFORM_NAME)
PRODUCT_MSTNAME  =
PRODUCT_NAME     =
PRODUCT_MANUFACT = Nokia
PRODUCT_MODEL    = N00
PRODUCT_TYPE     =
PRODUCT_REVISION = 01
PRODUCT_DIR      = $(PLATFORM_DIR)/$(if $(PRODUCT_MSTNAME),$(PRODUCT_MSTNAME)/)$(PRODUCT_NAME)

FEATURE_VARIANT = $(PRODUCT_NAME)
FEATVAR_IDIR    = $(call getrominc)

LABEL      =
NAME       = $(PRODUCT_NAME)$(LABEL)
WORKDIR    = $(if $(PRODUCT_NAME),$(E32ROMBLD)/$(PRODUCT_NAME),$(CURDIR))
WORKPREFIX = $(WORKDIR)/$(NAME)
WORKNAME   = $(WORKPREFIX)

IMAGE_HBY  = <data_caging_paths_for_iby.hrh> <Variant\Header.iby>
IMAGE_TYPE =

TRACE_IDIR     = $(addsuffix /traces,$(FEATVAR_IDIR))
TRACE_PREFIX   =
TRACE_SUFFIX   = _trace.txt
TRACE_UDEBFILE = $(E32ROMBLD)/mytraces.txt

OVERRIDE_CONF = OVERRIDE_REPLACE/WARN #OVERRIDE_REPLACE/ADD, OVERRIDE_REPLACE/SKIP, OVERRIDE_SKIP/ADD

GENIBY_FILEPAT = *.dll *.exe *.agt *.csy *.fsy *.tsy *.drv *.nif *.pgn *.prt

ARM_VERSION = ARMV5
SOS_VERSION = #9.3, 9.4, 9.5
S60_VERSION = #3.2, 5.0

ROFS_MAXSIZE = 0x10000000

CPPFILE_LIST =
MKFILE_LIST  = $(call findfile,$(BUILD_INFOMK) $(BUILD_NAMEMK) $(LANGPACK_SYSLANGMK),$(FEATVAR_IDIR)) $(VARIANT_MK)


###############################################################################
# Mini environment

MINIENV_MAINZIP = $(WORKPREFIX)_minienv.zip
MINIENV_TOOLZIP = $(WORKPREFIX)_minitool.zip
MINIENV_CONFZIP = $(WORKPREFIX)_miniconf.zip
MINIENV_SOSZIP  = $(WORKPREFIX)_minisos.zip
MINIENV_LOGZIP  = $(WORKPREFIX)_minilog.zip

MINIENV_TOOL    = $(E32TOOLS)/imaker.cmd $(ITOOL_DIR)/* $(IMAKER_DIR)/* $(call iif,$(USE_UNIX),,$(CPP))
MINIENV_CONF    = $(filter-out $(ITOOL_DIR)/% $(IMAKER_DIR)/%,$(MAKEFILE_LIST)) $(CPPFILE_LIST)
MINIENV_SOS     =\
  $(ROM_IMG) $(call iif,$(USE_PAGEDROM),$(ROM_INC))\
  $(call iif,$(USE_ROFS1),$(ROFS1_IMG)) $(call iif,$(USE_ROFS2),$(ROFS2_IMG)) $(call iif,$(USE_ROFS3),$(ROFS3_IMG))
MINIENV_LOG     = $(dir $(LOGFILE))*.log

MINIENV_SUBZIPS = TOOL CONF SOS LOG

CLEAN_MINIENV = $(foreach zip,MAIN $(MINIENV_SUBZIPS),del | $(MINIENV_$(zip)ZIP) |)
BUILD_MINIENV =\
  echo-q | Creating minimal flash image creation environment $(MINIENV_MAINZIP) |\
  $(foreach zip,$(MINIENV_SUBZIPS),\
    $(call iif,$(MINIENV_$(zip)ZIP),zip | $(MINIENV_$(zip)ZIP) | $(MINIENV_$(zip)) | |))\
  zip-j | $(MINIENV_MAINZIP) | $(foreach zip,$(MINIENV_SUBZIPS),$(MINIENV_$(zip)ZIP)) | |\
  $(foreach zip,$(MINIENV_SUBZIPS),del | $(MINIENV_$(zip)ZIP) |)


###############################################################################
#

SOS.IMAGE.STEPS =\
  $(filter-out %POST,$(SOS.CORE.STEPS) $(SOS.VARIANT.STEPS))\
  $(filter %POST,$(SOS.CORE.STEPS) $(SOS.VARIANT.STEPS))

ALL.IMAGE.STEPS = $(SOS.IMAGE.STEPS)

CLEAN_WORKAREA  = del | $(WORKDIR)/* | deldir | $(WORKDIR)/*
ALL.CLEAN.STEPS = $(ALL.IMAGE.STEPS) WORKAREA


###############################################################################
# Internal macros and definitions

getrominc = $(if $(call true,$(USE_FEATVAR)),$(getsbvrominc),$(CONFIGROOT) $(E32ROM))

getsbvrominc =\
  $(if $(call equal,$(__i_featvar),$(FEATURE_VARIANT)),,$(eval __i_featvar := $(FEATURE_VARIANT))\
    $(eval __i_getrominc := $(shell $(PERL) -x $(IMAKER_TOOL) --incdir $(__i_featvar))))$(__i_getrominc)

includeiby = $(call peval,\
  my @files = ();\
  while ($(call pquote,$1) =~ /(?:([1-6]):)?(?:<(.+?)>|"+(.+?)"+|(\S+))/g) {\
    my $$rom = (defined($$1) ? $$1 : q());\
    push(@files, ($$rom ? q(ROM_IMAGE[).$$rom.q(] {\\\n) : q()) . q(\#include ).\
      (defined($$2) ? qq(<$$2>) : q(").GetRelFname(defined($$3) ? $$3 : $$4, $(call pquote,$2)).q(")) . ($$rom ? q(\\\n}) : q()))\
  }\
  return(join(q(\\\n), @files)))

define BLDROM_HDRINFO
  // Generated master oby for $($(IMAGE_TYPE)_TITLE) image creation
  //
  // Filename: $($(IMAGE_TYPE)_MSTOBY)
  // Work dir: $(call peval,GetAbsDirname(q(.)))
  // Command : $(BLDROM_CMD)
endef

define BLDROM_PLUGINFO
  $(call iif,$(USE_OVERRIDE)$(USE_UDEB)$(call select,$(IMAGE_TYPE),CORE,$(USE_ROFS1)),
    // Buildrom plugins
    //
    $(call iif,$(USE_OVERRIDE),
      externaltool=override:$($(IMAGE_TYPE)_PLUGINLOG);$(if $(filter debug 127,$(VERBOSE)),debug,0)
      $(OVERRIDE_CONF))
    $(call iif,$(USE_UDEB)$(call select,$(IMAGE_TYPE),CORE,$(USE_ROFS1)),
      externaltool=obyparse:$($(IMAGE_TYPE)_PLUGINLOG);$(if $(filter debug 127,$(VERBOSE)),debug,0)
      $(call iif,$(call select,$(IMAGE_TYPE),CORE,$(USE_ROFS1)),
        $(call iif,$(USE_ROMFILE),
          OBYPARSE_ROM $(CORE_ROMFILE))
        $(call iif,$(USE_ROFSFILE),
          OBYPARSE_ROFS1 $(CORE_ROFSFILE))
      )
      $(call iif,$(USE_UDEB),
        OBYPARSE_UDEB $(call select,$(USE_UDEB),full,*,$($(IMAGE_TYPE)_UDEBFILE)))
    )
  )
endef

getgenfiles = $(if $1,\
  $(eval __i_cmd := $(filter geniby% write%,$(call lcase,$(call getelem,1,$1))))\
  $(if $(__i_cmd),"$(call getelem,2,$1)")\
  $(call getgenfiles,$(call restelems,$(if $(filter geniby%,$(__i_cmd)),7,$(if $(filter write%,$(__i_cmd)),4,2)),$1)))

# TEMPORARY
_buildoby = $(if $1,\
  $(eval __i_elem1 := $(call getelem,1,$1))\
  $(if $(filter geniby%,$(call lcase,$(__i_elem1))),$1,\
    geniby | $(__i_elem1) | $(call getelem,2,$1) | $(call getelem,3,$1) | \#include "%3" | end |\
    $(call _buildoby,$(call restelems,4,$1))))
# TEMPORARY

#==============================================================================

BLDROM_CMD = $(BLDROM_TOOL) $(filter-out --D% -U%,$(BLR.$(IMAGE_TYPE).OPT)) $(BLR.$(IMAGE_TYPE).IDIR) $($(IMAGE_TYPE)_MSTOBY)

CLEAN_BLDROM =\
  del | "$($(IMAGE_TYPE)_PREFIX).*" "$($(IMAGE_TYPE)_DIR)/tmp?.oby" "$($(IMAGE_TYPE)_DIR)/ecom*.s??" "$($(IMAGE_TYPE)_PLUGINLOG)" |\
  $(BLR.$(IMAGE_TYPE).CLEAN)

BUILD_BLDROM =\
  $(if $(BLR.$(IMAGE_TYPE).BUILD),$(BLR.$(IMAGE_TYPE).BUILD),\
    echo-q | Creating $($(IMAGE_TYPE)_TITLE) SOS image |\
    cd     | $($(IMAGE_TYPE)_DIR) |\
    cmd    | $(strip $(BLDROM_CMD)) | $(BLDROM_PARSE) |\
    copy   | tmp1.oby | $($(IMAGE_TYPE)_PREFIX).tmp1.oby |\
    $(call iif,$(KEEPTEMP),,del | "tmp?.oby" "$($(IMAGE_TYPE)_PREFIX).dummy*" |)\
    $(BLR.$(IMAGE_TYPE).POST))

CLEAN_MAKSYMROFS = del | $($(IMAGE_TYPE)_SYM)
BUILD_MAKSYMROFS =\
  echo-q | Creating $($(IMAGE_TYPE)_TITLE) symbol file |\
  cmd    | $(MAKSYMROFS_TOOL) $(call pathconv,$($(IMAGE_TYPE)_LOG) $($(IMAGE_TYPE)_SYM))


###############################################################################
# Targets

.PHONY:\
  all flash flash-all image image-all\
  i2file minienv

all flash-all image-all: USE_SYMGEN = 1
all flash flash-all    : ;@$(call IMAKER,$$(ALL.IMAGE.STEPS))

image image-all: ;@$(call IMAKER,$$(SOS.IMAGE.STEPS))

i2file minienv: ;@$(call IMAKER,$(call ucase,$@))

#==============================================================================

include $(addprefix $(IMAKER_DIR)/imaker_,$(addsuffix .mk,core odp rofs2 rofs3 uda variant))


# END OF IMAKER_IMAGE.MK
