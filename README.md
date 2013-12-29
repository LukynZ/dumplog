dumplog
=======

####Quick log viewer with multiple filter parameters and settings.

**Usage: single log file**

> dumplog { log_file | shortcut } [ filter pamameter.. ]

*examples:*

> dumplog dmesg eth0

> dumplog x nouveau drm VDPAU *// <= dumplog -s x Xorg.0.log*

**Usage: multiple log files**

> dumplog -m { log_file | shortcut } [ log file2.. | shortcut2.. ] [ -f [ filter pamameters ] ] *// m - multiple, f - filters*

*examples:*

> dumplog -f dmesg Xorg.0.log -f nouveau dri

> dumplog -m x d -f nouveau drm VDPAU *// <= dumplog -ss x Xorg.0.log, dumplog -ss d dmesg*


**list:**

> dumplog { -ls | -lp } *// ls = list shortcuts; lp = list path (default /var/log/)*

*example:*

> dumplog -ls


**set shortcut for log file**

> dumplog -ss shortcut log_file *// ss - set shortcut*

*examples:*

> dumplog -ss d dmesg *// => dumplog d eth0*

> dumplog -ss c cups/access_log *// => dumplog c 12/Dec/2013*


**set path to logs in your system**

> dumplog -sp path_to_logs *// sp - set path*

*example:*

> dumplog -sp /var/mylogs/

config files are saved to /root/.dumplog/ for now

![alt tag](http://www.volny.cz/suchoi/dumplog.png)
