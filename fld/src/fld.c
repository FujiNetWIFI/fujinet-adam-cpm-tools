/**
 * List Host Slots
 */

#include <fujicpm.h>
#include <conio.h>

const char *mode(char m)
{
  return m == 0x02 ? "R/W" : "R/O";
}

void main(void)
{
  DeviceSlot ds[8];

  cprintf("\nDEVICE SLOTS\n\n");
  fuji_get_device_slots(ds);

  for (char i=0;i<4;i++)
  {
    cprintf("[%d]",i+1);
    if (ds[i].hostSlot == 0xFF)
      cprintf("--Empty--");
    else
      cprintf("HS:%d M: %s F: %s",ds[i].hostSlot,mode(ds[i].mode),ds[i].file);

    cprintf("\n");
  }
}
