// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005062A0 rf_trigger_find_by_level_id32
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Cdecl supplied level ID DWORD; -1 immediately returnsNULL. Otherwise scans trigger circular ring from90B79C to sentinel90B510 through next+652; returns FIRST trigger whose common-object DWORD+32 equals supplied value; no match returnsNULL. Does not compare runtime UID+44, name or array index, reject other negative IDs, test disabled/dead state, allocate or mutate. Requires valid initialized ring; no NULL/cycle guard.
int __cdecl rf_trigger_find_by_level_id32(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( a1 == -1 )
    return 0;
  for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 32) == a1 )
      return i;
  }
  return 0;
}

