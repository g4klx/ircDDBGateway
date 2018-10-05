
# Add -DDCS_LINK to the end of the CFLAGS line below to add DCS linking to StarNet
# Add -DDEXTRA_LINK to the end of the CFLAGS line below to add DExtra linking to StarNet

ifeq ($(OPENWRT),1)
DATADIR := "/etc/mmdvm/ircddbgateway"
LOGDIR  := "/var/log/mmdvm"
CONFDIR := "/etc"
BINDIR  := "/usr/bin"

CFLAGS  += -DLOG_DIR='$(LOGDIR)' -DCONF_DIR='$(CONFDIR)' -DDATA_DIR='$(DATADIR)'
LIBS    += -lwxbase_u
LDFLAGS := 

else
DATADIR := "/usr/share/ircddbgateway"
LOGDIR  := "/var/log"
CONFDIR := "/etc"
BINDIR  := "/usr/bin"

CXX     := $(shell wx-config --cxx)
CFLAGS  := -O2 -Wall $(shell wx-config --cxxflags) -DLOG_DIR='$(LOGDIR)' -DCONF_DIR='$(CONFDIR)' -DDATA_DIR='$(DATADIR)'
GUILIBS := $(shell wx-config --libs adv,core,base)
LIBS    := $(shell wx-config --libs base)
LDFLAGS := 

endif
