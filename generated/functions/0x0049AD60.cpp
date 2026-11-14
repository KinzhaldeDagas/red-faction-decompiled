// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049AD60 rf_replication_encode_player_powerup_bits
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(entity,outBYTE). Clear output byte FIRST, then find current player by entity common handle44 using4DD720. If found query timed-node membership
// (player,kind1)->bit0,kind0->bit1,kind4->bit2, in that order; no direct Entity814 flag read or expiration check. Missing player leaves output0. No entity/output NULL validation.
// Return AL/EAX residue from last query/OR, not the encoded byte API contract; callers must use output pointer.
char __cdecl rf_replication_encode_player_powerup_bits(int a1, _BYTE *a2)
{
  _DWORD *v2; // eax
  int v4; // [esp+0h] [ebp-4h]

  *a2 = 0;
  v2 = sub_4DD720(*(_DWORD *)(a1 + 44));
  v4 = (int)v2;
  if ( v2 )
  {
    LOBYTE(v2) = rf_powerup_has_player_kind((int)v2, 1);
    if ( (_BYTE)v2 )
    {
      LOBYTE(v2) = *a2 | 1;
      *a2 = (_BYTE)v2;
    }
  }
  if ( v4 )
  {
    LOBYTE(v2) = rf_powerup_has_player_kind(v4, 0);
    if ( (_BYTE)v2 )
    {
      LOBYTE(v2) = (_BYTE)a2;
      *a2 |= 2u;
    }
  }
  if ( v4 )
  {
    LOBYTE(v2) = rf_powerup_has_player_kind(v4, 4);
    if ( (_BYTE)v2 )
    {
      *a2 |= 4u;
      LOBYTE(v2) = (_BYTE)a2;
    }
  }
  return (char)v2;
}

