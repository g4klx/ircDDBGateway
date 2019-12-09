#ifndef __GLOBAL_DEFS__
#define __GLOBAL_DEFS__

#if defined(__APPLE__) || defined(LINUX)
#define DATA_DIR   "/opt/mmdvm/conf/dstar"
#define LOG_DIR    "/opt/mmdvm/logs"
#define CONF_DIR   "/opt/mmdvm/conf"
#define CONF_FILE  "ircDDBGateway.ini"
#define PID_FILE   "/tmp/ircDDBGateway.pid"
#define PID_FILE_T "/tmp/ircDDBGateway_%s.pid"

#elif defined(OPENWRT) && OPENWRT == 1
#define DATA_DIR   "/etc/mmdvm/dstar"
#define LOG_DIR    "/var/log/mmdvm"
#define CONF_DIR   "/etc"
#define CONF_FILE  "ircDDBGateway.ini"
#define PID_FILE   "/tmp/ircDDBGateway.pid"
#define PID_FILE_T "/tmp/ircDDBGateway_%s.pid"

#else
#define DATA_DIR   "/usr/share/ircddbgateway"
#define LOG_DIR    "/tmp"
#define CONF_DIR   "/etc"
#define CONF_FILE  "ircddbgateway"
#define PID_FILE   "/var/run/ircddbgateway.pid"
#define PID_FILE_T "/var/run/ircddbgateway_%s.pid"

#endif

#endif
