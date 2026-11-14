// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495DB0 rf_player_string_record28_assign
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall28-byte record,source,RET4,returns receiver. WORDs0/2/4,DWORD8,RFString assignment12,WORDs20/22/24. Padding6..7 and26..27 unchanged. No ownership copy of rawDWORD8 pointer
// target,scalar defaults or source/destinationNULL guard. Used128 times per player prefix assignment.
int __thiscall rf_player_string_record28_assign(int this, int a2)
{
  unsigned int j; // [esp+8h] [ebp-8h]
  unsigned int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < 2; ++i )
    *(_WORD *)(this + 2 * i) = *(_WORD *)(a2 + 2 * i);
  *(_WORD *)(this + 4) = *(_WORD *)(a2 + 4);
  *(_DWORD *)(this + 8) = *(_DWORD *)(a2 + 8);
  rf_string_assign_from_object((_DWORD *)(this + 12), a2 + 12);
  for ( j = 0; j < 2; ++j )
    *(_WORD *)(this + 2 * j + 20) = *(_WORD *)(a2 + 2 * j + 20);
  *(_WORD *)(this + 24) = *(_WORD *)(a2 + 24);
  return this;
}

