// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495CD0 rf_player_string_state3664_assign
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall3664-byte prefix,source stack,RET4,returns receiver. Copies FLOAT0,BYTE4,DWORD8. Assigns exactly128 embedded28-byte records at12+28*i via495DB0,then DWORD3596,then
// FOUR16-byte raw blocks at3600+16*j. Padding5..7 untouched; nested28-byte record padding omitted by delegate. RFStrings assigned,not raw struct-copy or re-construction. No logical
// active-count bound: all128 records copied.
char *__thiscall rf_player_string_state3664_assign(char *this, int a2)
{
  char *v2; // eax
  unsigned int j; // [esp+4h] [ebp-8h]
  unsigned int i; // [esp+8h] [ebp-4h]

  *(float *)this = *(float *)a2;
  *(this + 4) = *(_BYTE *)(a2 + 4);
  *((_DWORD *)this + 2) = *(_DWORD *)(a2 + 8);
  for ( i = 0; i < 0x80; ++i )
    rf_player_string_record28_assign((int)(this + 28 * i + 12), a2 + 28 * i + 12);
  *((_DWORD *)this + 899) = *(_DWORD *)(a2 + 3596);
  for ( j = 0; j < 4; ++j )
  {
    v2 = this + 16 * j + 3600;
    *(_DWORD *)v2 = *(_DWORD *)(a2 + 16 * j + 3600);
    *((_DWORD *)v2 + 1) = *(_DWORD *)(a2 + 16 * j + 3604);
    *((_DWORD *)v2 + 2) = *(_DWORD *)(a2 + 16 * j + 3608);
    *((_DWORD *)v2 + 3) = *(_DWORD *)(a2 + 16 * j + 3612);
  }
  return this;
}

