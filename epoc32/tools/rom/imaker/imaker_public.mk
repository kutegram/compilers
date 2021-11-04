
# ============================================================================
#  Name        : imaker_public.mk
#  Part of     : iMaker
#  Description : iMaker public interface
#  Version     : %version: 6 %
#
#  Copyright © 2008 Nokia.  All rights reserved.
#  This material, including documentation and any related computer
#  programs, is protected by copyright controlled by Nokia.  All
#  rights are reserved.  Copying, including reproducing, storing,
#  adapting or translating, any or all of this material requires the
#  prior written consent of Nokia.  This material also contains
#  confidential information which may not be disclosed to others
#  without the prior written consent of Nokia.
# ============================================================================


#==============================================================================
# Product variant variables

FEATVARIANT_CONFML = $(wildcard $(PRODUCT_DIR)/$(FEATURE_VARIANT).confml)

PRODVARIANT_DIR    = $(PRODUCT_DIR)
PRODVARIANT_CONFML = $(or $(FEATVARIANT_CONFML),$(PRODUCT_DIR)/$(PRODUCT_NAME).confml)
PRODVARIANT_CONFCP =\
  $(PLATFORM_NAME) $(PRODUCT_MSTNAME) $(PRODUCT_NAME)\
  $(if $(FEATVARIANT_CONFML),$(call select,$(PRODUCT_NAME),$(FEATURE_VARIANT),,$(FEATURE_VARIANT)))

#==============================================================================
# Customer variant variables
# Root for customer variant (custvariant) pack settings

CUSTVARIANT_ROOT   = $(PRODUCT_DIR)/customer
CUSTVARIANT_PREFIX = custvariant_
CUSTVARIANT_MKNAME = variant.mk
CUSTVARIANT_NAME   =
CUSTVARIANT_ID     =
CUSTVARIANT_DIR    = $(CUSTVARIANT_ROOT)/$(CUSTVARIANT_NAME)
CUSTVARIANT_CONFML = $(wildcard $(CUSTVARIANT_DIR)/$(CONFT_CFGNAME).confml)
CUSTVARIANT_CONFCP = $(if $(CUSTVARIANT_CONFML),$(CONFT_CFGNAME))
CUSTVARIANT_COMPLP =

#==============================================================================
# The Target specific override settings

$(CUSTVARIANT_PREFIX)%: CUSTVARIANT_NAME = $(TARGETNAME)
$(CUSTVARIANT_PREFIX)%: CUSTVARIANT_ID   = $(TARGETID)
$(CUSTVARIANT_PREFIX)%: VARIANT_DIR      = $(CUSTVARIANT_DIR)
$(CUSTVARIANT_PREFIX)%: VARIANT_MKNAME   = $(CUSTVARIANT_MKNAME)
$(CUSTVARIANT_PREFIX)%: VARIANT_CONFML   = $(CUSTVARIANT_CONFML)
$(CUSTVARIANT_PREFIX)%: VARIANT_CONFCP   = $(CUSTVARIANT_CONFCP)
$(CUSTVARIANT_PREFIX)%: variantrofs3_$$* ;

#==============================================================================
# Helps

$(call add_help,PRODVARIANT_DIR,v,(string),Overrides the VARIANT_DIR for product variant, see the instructions of VARIANT_CONFCP for details.)
$(call add_help,PRODVARIANT_CONFML,v,(string),Overrides the VARIANT_CONFML for product variant, see the instructions of VARIANT_CONFML for details.)
$(call add_help,PRODVARIANT_CONFCP,v,(string),Overrides the VARIANT_CONFCP for product variant, see the instructions of VARIANT_CONFCP for details.)
$(call add_help,CUSTVARIANT_DIR,v,(string),Overrides the VARIANT_DIR for customer variant, see the instructions of VARIANT_CONFCP for details.)
$(call add_help,CUSTVARIANT_CONFML,v,(string),Overrides the VARIANT_CONFML for customer variant, see the instructions of VARIANT_CONFML for details.)
$(call add_help,CUSTVARIANT_CONFCP,v,(string),Overrides the VARIANT_CONFCP for customer variant, see the instructions of VARIANT_CONFCP for details.)
$(call add_help,CUSTVARIANT_COMPLP,v,(string),Compatible language variant.)
