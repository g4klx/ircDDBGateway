# Building ircDDBGateway

## Windows

To use the ircDDB Gateway software you will first need to build the latest
version of wxWidgets (http://www.wxwidgets.org), the version I used was 3.0.4.
I also installed it in the default location which is C:\wxWidgets-3.0.4.

For compiling I use Visual C++ 2017 Community Edition downloaded from Microsoft
for free. I recommend that you use the same.

To build wxWidgets, you simply need to open Visual Studio 2017 using the File ->
Open -> Projects/Solutions and load the wx_vc12.sln file to be found in
wxWidgets-3.0.4\build\msw directory and then go into Batch Build and select the
DLL Debug and DLL Release entries for every one, this take a  little time! Then
build them.

The path names for wxWidgets are embedded within the Solution and Project
preferences, and will need changing if anything other than these default
locations are used. The first pass through the compiler will no doubt tell
you all that you need to know if there are problems.

Once you have built the executables, you will need to copy the correct wxWidgets
files to the same location as the executables. For 32-bit systems these are
wxbase30u_vc_custom.dll, wxmsw30u_adv_vc_custom.dll, and
wxmsw30u_core_vc_custom.dll. On 64-bit systems you'll need
wxbase30u_vc_x64_custom.dll, wxmsw30u_adv_vc_x64_custom.dll, and
wxmsw30u_core_vc_x64_custom.dll

If you are running in debug mode then the required wxWidgets files have the names
xxx30ud_xxxx instead. These can be found in the wxWidgets-3.0.4\lib\vc_dll
directory.

It is also probable that you'll need to install a copy of the latest Visual C++
run-time libraries from Microsoft, if you are not running the gateway software
on the same machine as the development/compilation was done on. You can find the
latest versions at https://support.microsoft.com/en-gb/help/2977003/the-latest-supported-visual-c-downloads


## Linux

You need to ensure that wxGTK is already installed on your machine.

Debian, Ubuntu:
```sh
sudo apt install libwxgtk3.0-dev
```

Fedora, CentOS, RedHat:
```sh
sudo dnf install wxGTK3-devel
```

To install them from scratch, you need to get wxGTK from 
<http://www.wxwidgets.org>. If you do a "make install" on it then they'll
be installed in the right places and nothing more needs to be done.

To actually build the software, type "make" in the same directory as this file
and all should build without errors, there may be a warning or two though. Once
compiled log in as root or use the sudo command, and do "make install".

You can optionally specify some make variables to alter the default behavior:

| Parameter | Default   | Description                       |
| --------- | --------- | --------------------------------- |
| BUILD     | `debug`   | `debug` or `release`              |
| TARGET    | _not set_ | when set to `opendv`, installs files in legacy locations |
| DATADIR   | `/usr/share/ircddbgateway` | where AMBE voice and host lists are kept |
| LOGDIR    | `/var/log` | location of log files            |
| CONFDIR   | `/etc`     | location of configuration files  |
| BINDIR    | `/usr/bin` | program binaries installed here  |

### Example

```sh
cd ircDDBGateway
make -j4 BUILD=release CONFDIR=/etc/dstar
sudo make install
```

This would build and install all the programs in this repo using 4 threads
(parallel build jobs), in release mode (no debug symbols) with a modified
configuration directory.

