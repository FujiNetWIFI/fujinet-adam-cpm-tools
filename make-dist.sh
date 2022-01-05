#!/bin/bash

BLANK=dist/blank160.dsk
DSK=dist/fnc-tools-adam-cpm.dsk
CP="cpmcp -f adam $DSK"

rm -f $DSK
cp $BLANK $DSK
set -x
$CP finfo/finfo.com 0:finfo.com
$CP feject/feject.com 0:feject.com
$CP fld/fld.com 0:fld.com
$CP flh/flh.com 0:flh.com
$CP fmount/fmount.com 0:fmount.com
$CP fnew/fnew.com 0:fnew.com
$CP fwifi/fwifi.com 0:fwifi.com
$CP fhost/fhost.com 0:fhost.com
$CP ncd/ncd.com 0:ncd.com
$CP ndir/ndir.com 0:ndir.com
$CP nera/nera.com 0:nera.com
$CP nget/nget.com 0:nget.com
$CP nlogin/nlogin.com 0:nlogin.com
$CP nmkdir/nmkdir.com 0:nmkdir.com
$CP nput/nput.com 0:nput.com
$CP npwd/npwd.com 0:npwd.com
$CP nren/nren.com 0:nren.com
$CP README.md 0:README.TXT
set +x

