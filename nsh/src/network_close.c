/**
 * Close Connection
 *
 * @return status
 */

#include "adamnet_write.h"
#include "network.h"

unsigned char network_close(void)
{
  unsigned char resp='C';
  
  return adamnet_write(&resp,1);
}
