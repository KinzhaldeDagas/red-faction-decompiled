// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EDEF0 rf_feedback_xor_transform_bytes_in_place
// UNREALRED VERIFIED [wave-codec-20261028]: This is three32-bit state words; arguments mutable byte buffer,signed byte count. For each byte performs8 feedback steps: if state0 lowbit1,state0=(state0 XOR0x40000031)|0x80000000,then conditionally updates state1: odd XOR0x20000010 OR0x40000000 and emits1,even arithmetic-right-shifts1 andemits0. If state0 lowbit0,arithmetic-right-shifts state0 and conditionally updates state2: odd XOR0x08000001 OR0x10000000 andemits1,even arithmetic-right-shifts1 andemits0. Odd branches do NOT also shift. Builds8-bit key by leftshift/OR,then XORs current buffer byte. State mutates across bytes/calls; same initialstate andsame length reverses transformation by XOR symmetry. Count0 returns0 without access; negative count decrements toward wrap and is not safely rejected. No buffer bound or seed validation. This contract describes exact feedback operations,not a
// claimed standard cipher or security property.
int __thiscall rf_feedback_xor_transform_bytes_in_place(unsigned int *this, _BYTE *a2, int a3)
{
  int result; // eax
  char v4; // [esp+4h] [ebp-Ch]
  char i; // [esp+Bh] [ebp-5h]
  int j; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; *a2++ ^= i )
  {
    result = a3--;
    if ( !result )
      break;
    for ( j = 0; j < 8; ++j )
    {
      v4 = 0;
      if ( (*this & 1) != 0 )
      {
        *this = *this ^ 0x40000031 | 0x80000000;
        if ( (*(this + 1) & 1) != 0 )
        {
          *(this + 1) = *(this + 1) ^ 0x20000010 | 0x40000000;
          v4 = 1;
        }
        else
        {
          *(this + 1) = (int)*(this + 1) >> 1;
        }
      }
      else
      {
        *this = (int)*this >> 1;
        if ( (*(this + 2) & 1) != 0 )
        {
          *(this + 2) = *(this + 2) ^ 0x8000001 | 0x10000000;
          v4 = 1;
        }
        else
        {
          *(this + 2) = (int)*(this + 2) >> 1;
        }
      }
      i = v4 | (2 * i);
    }
  }
  return result;
}

