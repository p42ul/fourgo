#include "sound.h"

#include <gb/gb.h>
#include "fourgo.h"


void play_drop_sound(Player player)
{
  if (player == P1)
  {
    NR10_REG = 0x7E;
    NR11_REG = 0x84;
    NR12_REG = 0x73;
    NR13_REG = 0x72;
    NR14_REG = 0x86;
  }
  else
  {
    NR10_REG = 0x7E;
    NR11_REG = 0x84;
    NR12_REG = 0x73;
    NR13_REG = 0x45;
    NR14_REG = 0x86;
  }
}

void play_move_sound(Player player)
{
  if (player == P1)
  {
    NR10_REG = 0x24;
    NR11_REG = 0x81;
    NR12_REG = 0x43;
    NR13_REG = 0x72;
    NR14_REG = 0x86;
  }
  else
  {
    NR10_REG = 0x24;
    NR11_REG = 0x81;
    NR12_REG = 0x43;
    NR13_REG = 0x45;
    NR14_REG = 0x86;
  }
}

void init_sound(void)
{
  NR52_REG = 0x80;
  NR51_REG = 0xFF;
  NR50_REG = 0x77;
}
