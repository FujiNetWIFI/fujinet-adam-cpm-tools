/**
 * Create New Disk
 */

#include <stdlib.h>
#include <stdbool.h>
#include <fujicpm.h>
#include <conio.h>

#define READWRITE 2

void home(void)
{
  cprintf("\x1b" "E");
}

DeviceSlot deviceSlots[8];

unsigned char select_host_slot(void)
{
  char hs[8][32];
  char c=0;
  
  fuji_get_host_slots(hs);

  home();
  cprintf("\nNEW DISK--HOST SLOTS\n\n");
  for (char i=0;i<8;i++)
    cprintf("[%u]%s\n",i+1,hs[i]);

  cprintf("\n");
  
  while (c < 0x30 || c > 0x39)
    {
      cprintf("SELECT HOST SLOT: ");
      c=cgetc();
      if (c==0x03)
	{
	  cprintf("\n\nABORTING\n");
	  exit(0);
	}
      cprintf("%c\n",c);
    }
  
  return c - '1';
}

unsigned long select_size(void)
{
  char c[10];
  unsigned long l;

  while (l<1)
    {
      home();
      cprintf("SELECT DISK SIZE\n\n");
      cprintf("[1]160K\n");
      cprintf("[2]256K (DDP)\n");
      cprintf("[3]320K\n");
      cprintf("[4]718K\n");
      cprintf("[5]1418K\n");
      cprintf("[6]8192K\n");
      cprintf("\n\nSELECT SIZE\nOR # OF BLOCKS: \n");
      cgets(c);
      l=atol(c);
      
      switch(l)
	{
	case 1:
	  l=160;
	  break;
	case 2:
	  l=256;
	  break;
	case 3:
	  l=320;
	  break;
	case 4:
	  l=718;
	  break;
	case 5:
	  l=1418;
	  break;
	case 6:
	  l=8192;
	  break;
	default:
	  break;
	}
    }
  
  return l;
}

void enter_filename(char *p)
{
  cprintf("FILENAME: ");
  cgets(p);
}

void show_device_slots(void)
{
  cprintf("\nPUT INTO DEVICE SLOT\n\n");
  
  for (char i=0;i<4;i++)
    {
      cprintf("[%d]",i+1);
      if (deviceSlots[i].file == 0x00)
	cprintf("--Empty--\n");
      else
	cprintf("%s\n",deviceSlots[i].file);
    }
}

unsigned char select_device_slot(void)
{
  unsigned char s=0;

  fuji_get_device_slots(deviceSlots);

  while (s < 1)
    {
      home();
      show_device_slots();
      
      cprintf("\nSELECT DEVICE SLOT: ");
      s=cgetc()-0x31;
      cprintf("%u\n\n",s+1);
    }

  return s;  
}

bool are_you_sure(unsigned char hs, unsigned char ds, unsigned long nb, char *p)
{
  bool yn=false;
  char c=0;
  
  cprintf("HOST SLOT: %u\n",hs+1);
  cprintf("DISK SLOT: %u\n",ds+1);
  cprintf(" # BLOCKS: %lu\n",nb);
  cprintf(" FILENAME: %s\n",p);
  cprintf("\nARE YOU SURE[Y/N]? ");
  
  c=cgetc();
  cprintf("%c\n\n",c);

  if (c == 'y' || c == 'Y')
    yn=true;
  
  return yn;
}

void main(void)
{
  unsigned char hs, ds;
  unsigned long numBlocks;
  char p[256];
  
  hs=select_host_slot();
  numBlocks=select_size();
  enter_filename(p);
  ds=select_device_slot();

  if (are_you_sure(hs,ds,numBlocks,p))
    {
      cprintf("CREATING...");
      fuji_mount_host_slot(hs);
      fuji_new_disk(hs,ds,numBlocks,p);

      deviceSlots[ds].mode = READWRITE;
      deviceSlots[ds].hostSlot = hs;
      strncpy(deviceSlots[ds].file,p,36);
      
      fuji_set_device_filename(ds,p);
      fuji_put_device_slots(deviceSlots);
      fuji_mount_device_slot(ds,READWRITE);
      cprintf("DONE.\n");
    }
}
