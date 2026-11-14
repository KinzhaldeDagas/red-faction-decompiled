// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005068A0 rf_vclip_find_first_free_runtime_slot
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): No arguments. Scans EXACT128 indices0..127; tests BYTE at90B8BC+72*i (runtime base90B880, active byte+60). Returns first zero-byte slot index, otherwise-1. Native IMUL48h and MOVZX BYTE prove stride72 and byte width; do not reinterpret pseudocode array indexing as 288-byte records or DWORD occupancy. Any nonzero active byte means busy. Does not reserve/mark slot, unlink a record, destroy VFX, allocate/evict, or inspect loaded definition count. Repeated calls can return same index until caller marks active.
int rf_vclip_find_first_free_runtime_slot()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 128; ++i )
  {
    if ( !unk_90B8BC[72 * i] )
      return i;
  }
  return -1;
}

