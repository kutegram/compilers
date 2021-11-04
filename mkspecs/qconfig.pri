CONFIG+= debug shared stl exceptions rtti def_files
QT_ARCH = symbian
QT_EDITION = OpenSource
QT_CONFIG += release debug zlib png s60 openssl no-ipv6 script xmlpatterns phonon phonon-backend multimedia audio-backend declarative native-gestures svg minimal-config small-config medium-config large-config full-config
#versioning 
QT_VERSION = 4.7.3
QT_MAJOR_VERSION = 4
QT_MINOR_VERSION = 7
QT_PATCH_VERSION = 3
#Qt for Windows CE c-runtime deployment
QT_CE_C_RUNTIME = no
#Qt for Symbian FPU settings
MMP_RULES += "ARMFPU softvfp"