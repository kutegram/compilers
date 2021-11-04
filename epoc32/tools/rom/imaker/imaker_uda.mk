
# ============================================================================
#
#  Name        : imaker_uda.mk
#  Part of     : iMaker
#  Description : iMaker User Data image configuration
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



###############################################################################
#  _   _ ___   _
# | | | |   \ /_\
# | |_| | |) / _ \
#  \___/|___/_/ \_\
#

USE_FILEDISK = 0
USE_SOSUDA   = 0

UDA_TITLE       = UDA
UDA_DIR         = $(WORKDIR)/uda
UDA_NAME        = $(NAME)
UDA_PREFIX      = $(UDA_DIR)/$(UDA_NAME)
UDA_IDIR        =
UDA_HBY         =
UDA_OBY         =
UDA_OPT         = $(BLDROM_OPT) -D_EABI=$(ARM_VERSION)
UDA_MSTOBY      = $(UDA_PREFIX)_uda_master.oby
UDA_HEADER      =
UDA_INLINE      =
UDA_FOOTER      =
UDA_TIME        = $(DAY)/$(MONTH)/$(YEAR)

UDA_CPDIR       =
UDA_ZIP         =
UDA_DATADIR     = $(UDA_DIR)/datadrive
UDA_SISCONFFILE = $(UDA_PREFIX)_uda_sisconf.txt
UDA_SISCONF     =\
  -d $(UDA_DRIVE): -c $(UDA_DATADIR) $(if $(SISINST_SISDIR),-s $(SISINST_SISDIR))\
  -z $(SISINST_ZDIR) $(if $(SISINST_HALINI),-i $(SISINST_HALINI)) -w info

UDA_VERSION     = $(CORE_VERSION)
UDA_SWVERFILE   = "$(UDA_DATADIR)/Resource/Versions/User Content Package_UDA.txt"
UDA_SWVERINFO   = $(UDA_VERSION)
UDA_EXCLFILE    = #$(UDA_DATADIR)/private/100059C9/excludelist.txt
UDA_TOUCH       = $(call iif,$(USE_SOSUDA),,$(YEAR)$(MONTH)$(DAY)000000)

UDA_IMG         = $(UDA_PREFIX).uda.img
UDA_LOG         = $(UDA_PREFIX).uda.log
UDA_OUTOBY      = $(UDA_PREFIX).uda.oby
UDA_EMPTYIMG    = $(UDA_PREFIX).udaempty.img

UDA_PLUGINLOG   = $(UDA_PREFIX)_uda_bldromplugin.log
UDA_UDEBFILE    = $(TRACE_UDEBFILE)

UDA_DRIVE       = C
UDA_FATTYPE     = fat16
UDA_FATSIZE     = 20480

#==============================================================================

UDA_FDISKCONF = /mount 0
UDA_FDISKCMD  =\
  $(FILEDISK_TOOL) $(UDA_FDISKCONF) $(call peval,GetAbsFname($(call pquote,$(UDA_IMG)),1,1)) $(call peval,$$iVar[0] = GetFreeDrive()) |\
  copy  | $(UDA_DATADIR)/* | $(call peval,$$iVar[0])/ |\
  cmd   | $(FILEDISK_TOOL) /status $(call peval,$$iVar[0]) |\
  sleep | 1 |\
  cmd   | $(FILEDISK_TOOL) /umount $(call peval,$$iVar[0])

UDA_WINIMGCMD = $(WINIMAGE_TOOL) $(call pathconv,$(UDA_IMG)) /i $(call pathconv,$(UDA_DATADIR)) /h /q

UDA_CMD       = $(call iif,$(USE_FILEDISK),$(UDA_FDISKCMD),$(UDA_WINIMGCMD))
UDA_EMPTYCMD  =

#==============================================================================

define UDA_MSTOBYINFO
  $(BLDROM_HDRINFO)

  ROM_IMAGE  0 non-xip size=0x00000000

  DATA_IMAGE 0 $(basename $(UDA_IMG)) size=$(call peval,$(UDA_FATSIZE) * 1024) $(UDA_FATTYPE)

  // UDA header
  //
  $(UDA_HDRINFO)

  DATA_IMAGE[0] {
    $(BLR.UDA.OBY)
    $(UDA_INLINE)
    $(UDA_FOOTERINFO)
  }
endef

define UDA_HDRINFO
  $(DEFINE) _IMAGE_WORKDIR $(UDA_DIR)
  $(call mac2cppdef,$(BLR.UDA.OPT))
  $(BLR.UDA.HBY)
  $(UDA_HEADER)
  $(call select,$(USE_VARIANTBLD),u,$(VARIANT_HEADER))
endef

define UDA_FOOTERINFO
  $(if $(UDA_TIME),time=$(UDA_TIME))
  $(UDA_FOOTER)
endef

#==============================================================================

CLEAN_UDAFILE =\
  del | "$(UDA_MSTOBY)" "$(UDA_SISCONFFILE)" "$(UDA_SWVERFILE)" "$(UDA_EXCLFILE)"

BUILD_UDAFILE =\
  echo-q | Generating file(s) for UDA image creation |\
  $(call iif,$(USE_SOSUDA),\
    write  | $(UDA_MSTOBY) | $(call def2str,$(UDA_MSTOBYINFO)) |\
    write  | $(UDA_SISCONFFILE) | $(call quote,$(UDA_SISCONF)) |)\
  $(if $(UDA_SWVERINFO),\
    writeu | $(UDA_SWVERFILE) | $(UDA_SWVERINFO) |)\
  $(if $(UDA_EXCLFILE),\
    write  | $(UDA_EXCLFILE) | |\
    find-r | $(UDA_DATADIR)  | * |\
    writeu | $(UDA_EXCLFILE) |\
      $(call peval,join(q(), map(Quote(q($(UDA_DRIVE):\\\) . GetRelFname($$_, $(call pquote,$(UDA_DATADIR)), 1)) . q(\n), @gFindresult))))


###############################################################################
# UDA pre

STEPS_UDAPRE = $(call select,$(USE_VARIANTBLD),u,CUSTVARIANT) UDAPRE

CLEAN_UDAPRE = $(call select,$(USE_VARIANTBLD),u,,deldir | $(UDA_DATADIR) |) $(CLEAN_UDAFILE)

BUILD_UDAPRE =\
  echo-q | Preparing UDA image creation |\
  mkcd   | $(UDA_DIR) |\
  $(call select,$(USE_VARIANTBLD),u,,\
    mkdir | $(UDA_DATADIR) |\
    $(if $(UDA_ZIP),\
      $(eval __i_zip := $(foreach zip,$(UDA_ZIP),$(zip)$(if $(filter %.zip,$(call lcase,$(zip))),,/*.zip)))\
      echo-q | Extracting `$(__i_zip)$' to `$(UDA_DATADIR)$' |\
      unzip  | $(__i_zip) | $(UDA_DATADIR) |)\
    $(if $(UDA_CPDIR),\
      copy | $(UDA_CPDIR)/* | $(UDA_DATADIR) |))\
  $(BUILD_UDAFILE) |\
  $(call iif,$(USE_FILEDISK),\
    cmd | attrib -r -a -s -h $(call pathconv,$(UDA_DATADIR)) /s /d |)\
  $(if $(UDA_TOUCH),\
    finddir-r | $(UDA_DATADIR) | * | touch  | __find__ | $(UDA_TOUCH) |\
    find-r    | $(UDA_DATADIR) | * | touch  | __find__ | $(UDA_TOUCH))

#==============================================================================
# UDA build

BLR.UDA.IDIR   = $(call dir2inc,$(UDA_IDIR) $(call iif,$(USE_FEATVAR),,$(FEATVAR_IDIR)))
BLR.UDA.HBY    = $(call includeiby,$(IMAGE_HBY) $(UDA_HBY))
BLR.UDA.OBY    = $(call includeiby,$(UDA_OBY) $(call select,$(USE_VARIANTBLD),u,$(VARIANT_OBY)))
BLR.UDA.OPT    = $(UDA_OPT) -p -retainfolder -pfile=$(UDA_SISCONFFILE) -o$(UDA_NAME).dummy0.img $(BLDROPT)
BLR.UDA.POST   =\
  move | $(UDA_OUTOBY).log | $(UDA_LOG)

BLR.UDA.CLEAN  = del | "$(UDA_EMPTYIMG)" "$(UDA_IMG)"
BLR.UDA.BUILD  =\
  $(call iif,$(USE_SOSUDA),,\
    echo-q | Creating $(UDA_TITLE) SOS image |\
    $(if $(UDA_EMPTYCMD),\
      cmd  | $(UDA_EMPTYCMD) |\
      move | $(UDA_EMPTYIMG) | $(UDA_IMG) |)\
    cmd | $(UDA_CMD))

CLEAN_UDA = $(CLEAN_BLDROM)
BUILD_UDA = $(BUILD_BLDROM)

# UDA Empty
#
CLEAN_UDAEMPTY = del | $(UDA_EMPTYIMG)
BUILD_UDAEMPTY =\
  echo-q | Creating empty UDA FAT image |\
  mkdir  | $(UDA_DIR) |\
  cmd    | $(UDA_EMPTYCMD)

#==============================================================================
# UDA post

#==============================================================================

SOS.UDA.STEPS      = $(call iif,$(SKIPPRE),,UDAPRE) UDA $(SOS.UDAEMPTY.STEPS)
SOS.UDAEMPTY.STEPS = UDAEMPTY

ALL.UDA.STEPS      = $(SOS.UDA.STEPS)
ALL.UDAEMPTY.STEPS = $(SOS.UDAEMPTY.STEPS)

#==============================================================================

.PHONY: uda uda-image uda-empty uda-empty-image variantuda

uda uda-% variantuda variantuda_%: IMAGE_TYPE = UDA

uda:             ;@$(call IMAKER,$$(ALL.UDA.STEPS))
uda-image:       ;@$(call IMAKER,$$(SOS.UDA.STEPS))
uda-empty:       ;@$(call IMAKER,$$(ALL.UDAEMPTY.STEPS))
uda-empty-image: ;@$(call IMAKER,$$(SOS.UDAEMPTY.STEPS))

variantuda variantuda_%: USE_CUSTVARIANTBLD = 1
variantuda variantuda_%: USE_VARIANTBLD     = u
variantuda variantuda_%:\
  ;@$(call IMAKER,$$(ALL.UDA.STEPS))


# END OF IMAKER_UDA.MK
