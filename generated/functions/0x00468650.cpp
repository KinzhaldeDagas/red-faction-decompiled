// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468650 rf_controls_assign_binding_and_remove_duplicates
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl FULL keyDWORD,mouseDWORD. Save selected action6F62BC;write LOWWORD key/player260+28*selected and LOWWORD mouse/player264+28*selected FIRST,without
// player/selection bounds. Scan EXACT128 slots independent of actionCount. If FULL key!=-1 and sign-extended existing keyWORD equals FULL key and i!=selected,clear ONLY that keyWORD
// toFFFF. Analogous independent mouse pass,clear ONLY mouseWORD. Passing-1 suppresses that dedup pass;assignment still writesFFFF. Equality uses full32 input after signed16 load,so
// out-of-range inputs truncate on store yet may evade duplicate removal. Opposite binding field remains unless explicitly overwritten at selected slot. No swap,conflict
// prompt,default/label change,save,scroll or capture reset. Stored int16 return incidental AX residue.
__int16 __cdecl rf_controls_assign_binding_and_remove_duplicates(int a1, int a2)
{
  __int16 result; // ax
  int v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  v3 = dword_6F62BC;
  *(_WORD *)(rf_local_fpgun_player + 28 * dword_6F62BC + 260) = a1;
  result = a2;
  *(_WORD *)(rf_local_fpgun_player + 28 * v3 + 264) = a2;
  for ( i = 0; i < 128; ++i )
  {
    if ( a1 != -1 )
    {
      result = rf_local_fpgun_player;
      if ( *(__int16 *)(rf_local_fpgun_player + 28 * i + 260) == a1 && i != v3 )
      {
        result = 28 * i;
        *(_WORD *)(rf_local_fpgun_player + 28 * i + 260) = -1;
      }
    }
    if ( a2 != -1 )
    {
      result = 28 * i;
      if ( *(__int16 *)(rf_local_fpgun_player + 28 * i + 264) == a2 )
      {
        result = i;
        if ( i != v3 )
        {
          result = rf_local_fpgun_player;
          *(_WORD *)(rf_local_fpgun_player + 28 * i + 264) = -1;
        }
      }
    }
  }
  return result;
}

