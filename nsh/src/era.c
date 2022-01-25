/**
 * nsh - the N: Shell
 *
 * @author Thomas Cherryhomes
 * @email thom dot cherryhomes at gmail dot com
 * @license GPL v. 3 (see LICENSE.md)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "era.h"
#include "adamnet_read.h"
#include "adamnet_write.h"
#include "input.h"

extern unsigned char response[1024];

void era(char *s)
{
  char resp[257];
  char dir[256];
  
  if (s==NULL)
    {
      s=dir;
      printf("URL: ");
      input(s);
    }

  if (s==NULL)
    return;
  
  memset(resp,0,sizeof(resp));
  
  resp[0]='!'; // 0x21

  if (s!=NULL)
    strncpy(&resp[1],s,256);
  
  adamnet_write(resp,strlen(resp));
}
