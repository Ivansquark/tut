#! /bin/sh
# SYSTEM INFO IN HTML
SYSNAME=$(uname)
CURR_DIR=$(pwd)
TITLE="System Information Report For $USER"
CURRENT_TIME=$(date +"%x %r %Z")
TIME_STAMP="Generated $CURRENT_TIME, by $SYSNAME"

report_uptime() {
    cat << _EOF_
            <H2>System Uptime</H2>
            <PRE>$(uptime)</PRE>
_EOF_
    return
}
report_disk_space() {
    cat << _EOF_    
            <H2>Disk Space Utilization</H2>
            <PRE>$(df ~)</PRE>
_EOF_
    return
}
report_home_space() {
    if [ $(id -u) -eq 0 ]; then
        cat << _EOF_
            <H2>Home Space Utilization</H2>
            <PRE>$(du $PWD/..)</PRE>
_EOF_
    else
        cat << _EOF_
            <H2>Home Space Utilization</H2>
            <PRE>$(du $PWD)</PRE>
_EOF_
    fi
    return
}

cat << _EOF_ >index.html
<HTML>
        <HEAD>
            <TITLE>$TITLE</TITLE>
        </HEAD>
        <BODY>
            <H1>$TITLE</H1>
            <P>$TIME_STAMP executed from $CURR_DIR</P>
            $(report_uptime)
            $(report_disk_space)
            $(report_home_space)
        </BODY>
</HTML>
_EOF_
