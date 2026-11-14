// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004900A0 rf_multiplayer_allocate_unused_network_id_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments,returns BYTE AL. Starting candidate globalBYTE704BD8,scans ALL players in circular list and compares signed-extended candidate/idBYTE(net4608+20); equality is
// same byte identity. Collision increments candidate with8-bit wrap and restarts full scan. Free candidate returns OLD byte then increments global for next call. Includes local
// player,does not reserve/exclude0 or255,check connection state or netNULL. If all256 ids present,loops indefinitely; apparent final OR AL,0xFF failure path is unreachable because
// loop condition is constant1. Does not insert player/reserve returned id beyond advancing candidate.
char rf_multiplayer_allocate_unused_network_id_byte()
{
  _DWORD *v2; // [esp+4h] [ebp-Ch]
  int v3; // [esp+8h] [ebp-8h]
  _DWORD *i; // [esp+Ch] [ebp-4h]

  while ( 1 )
  {
    v3 = 1;
    for ( i = (_DWORD *)dword_87C324; i; i = v2 )
    {
      if ( *(char *)(i[1152] + 20) == unk_704BD8 )
      {
        v3 = 0;
        break;
      }
      if ( *i == dword_87C324 )
        v2 = nullptr;
      else
        v2 = (_DWORD *)*i;
    }
    if ( v3 )
      return unk_704BD8++;
    ++unk_704BD8;
  }
}

