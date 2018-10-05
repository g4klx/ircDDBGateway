#ifndef __GLOBAL_DEFS__
#define __GLOBAL_DEFS__

#if defined(__APPLE__)
#define DATA_DIR "/etc/mmdvm/dstar"
#define LOG_DIR  "/var/log/mmdvm"
#define CONF_DIR "/etc"
#define CONF_FILE "ircDDBGateway.ini"
#define LOG_BASE "ircDDBGateway"

#elif defined(OPENWRT) && OPENWRT == 1
#define DATA_DIR "/etc/mmdvm/dstar"
#define LOG_DIR  "/var/log/mmdvm"
#define CONF_DIR "/etc"
#define CONF_FILE "ircDDBGateway.ini"
#define LOG_BASE "ircDDBGateway"

#else
#define DATA_DIR "/usr/share/ircddbgateway"
#define LOG_DIR  "/tmp"
#define CONF_DIR "/etc"
#define CONF_FILE "ircddbgateway"
#define LOG_BASE "ircddbgateway"

#endif

#endif
