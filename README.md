dumplog
=======

Quick log viewer with multiple filter parameters and settings.

Usage:

// log dump
dumplog { log_file | shortcut } [ filter pamameters ]

examples:
dumplog dmesg eth0
dumplog Xorg.0.log nouveau drm VDPAU


// list; -ls = list adjusted shortcuts; -lp = show adjusted path (default /var/log/)
dumplog { -ls | -lp }

example:
dumplog -ls


// set shortcut for log file
dumplog -s shortcut log_file

examples:
dumplog -s d dmesg // => dumplog d eth0
dumplog -s c cups/access_log // => dumplog c 12/Dec/2013


// set path to logs in your system
dumplog -p path_to_logs

example:
dumplog -p /var/mylogs/
