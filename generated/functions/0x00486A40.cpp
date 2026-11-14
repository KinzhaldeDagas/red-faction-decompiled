// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486A40 rf_material_debris_bitmap_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl(signed material_id,DWORD* auxiliary). IDs1..9 write record auxiliary+24 to output and return handle+20 from base0x6FFE98,stride28. For id<=0 or>=10, ALWAYS writes output0 and
// returns EAX=-1; unlike physics coefficient getters this does NOT expose Default0's authored debris bitmap. Output pointer is unconditionally dereferenced on either branch, no NULL
// guard. No bitmap load/frame selection/reference management here.
int __cdecl rf_material_debris_bitmap_get(int material_id, int *auxiliary)
{
  if ( material_id <= 0 || material_id >= 10 )
  {
    *auxiliary = 0;
    return -1;
  }
  else
  {
    *auxiliary = rf_material_physics_records[material_id].debris_bitmap_auxiliary;
    return rf_material_physics_records[material_id].debris_bitmap_handle;
  }
}

