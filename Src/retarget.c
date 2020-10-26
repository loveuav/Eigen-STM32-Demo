/******************************************************************************/
/* RETARGET.C: 'Retarget' layer for target-dependent low level functions      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005 Keil Software. All rights reserved.                     */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <stdio.h>

#include <rt_misc.h>
#include <rt_sys.h>

// https://stackoverflow.com/questions/17548453/push-back-causes-program-to-stop-before-entering-main#comment50773218_20777139

__asm(".global __use_no_semihosting"); // only for AC6

char *_sys_command_string(char *cmd, int len)
{
    return 0;
}

extern void $Super$$_sys_open(void);

FILEHANDLE $Sub$$_sys_open(const char *name, int openmode)
{
    return 1; /* everything goes to the same output */
}

extern void $Super$$_sys_close(void);
int $Sub$$_sys_close(FILEHANDLE fh)
{
    return 0;
}

extern void $Super$$_sys_write(void);
int $Sub$$_sys_write(FILEHANDLE fh, const unsigned char *buf,
                     unsigned len, int mode)
{
    //your_device_write(buf, len);
    return 0;
}

extern void $Super$$_sys_read(void);
int $Sub$$_sys_read(FILEHANDLE fh, unsigned char *buf,
                    unsigned len, int mode)
{
    return -1; /* not supported */
}

extern void $Super$$_ttywrch(void);
void $Sub$$_ttywrch(int ch)
{
    char c = ch;
    //your_device_write(&c, 1);
}

extern void $Super$$_sys_istty(void);
int $Sub$$_sys_istty(FILEHANDLE fh)
{
    return 0; /* buffered output */
}

extern void $Super$$_sys_seek(void);
int $Sub$$_sys_seek(FILEHANDLE fh, long pos)
{
    return -1; /* not supported */
}

extern void $Super$$_sys_flen(void);
long $Sub$$_sys_flen(FILEHANDLE fh)
{
    return -1; /* not supported */
}

extern void $Super$$_sys_exit(void);
long $Sub$$_sys_exit(FILEHANDLE fh)
{
    return -1; /* not supported */
}
