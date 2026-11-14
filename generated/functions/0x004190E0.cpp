// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004190E0 rf_geomod_debris_object_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl debris pointer. Flags+668 mask0x10 first unregisters the backing-solid additional light receiver. Ownership mask0x40000000 then destroys nonnull solid+660 with scalar-delete flag1. Unlinks intrusive next+652/prev+656, clears those two fields and decrements global physical-debris count unconditionally. Returns original object pointer bits. Does not stop voice+684, clear solid pointer/ownership flags, destroy common members or free containing object allocation. No null/already-unlinked guard; repeated calls can dereference zero links and double-destroy ownership.
_DWORD *__cdecl rf_geomod_debris_object_destroy(_DWORD *a1)
{
  char *v2; // [esp+8h] [ebp-4h]

  if ( (a1[167] & 0x10) != 0 )
    rf_light_additional_receiver_unregister_first((_DWORD *)a1[165]);
  if ( (a1[167] & 0x40000000) != 0 )
  {
    v2 = (char *)a1[165];
    if ( v2 )
      rf_solid_destroy(v2, 1);
  }
  *(_DWORD *)(a1[164] + 652) = a1[163];
  *(_DWORD *)(a1[163] + 656) = a1[164];
  a1[163] = 0;
  a1[164] = 0;
  --rf_physical_debris_count;
  return a1;
}

