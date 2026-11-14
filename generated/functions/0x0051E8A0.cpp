// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E8A0 rf_solid_find_geometry_record_by_saved_id
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Linear search vector at solid+0x90. Return first pointer whose record dword+0x24 equals supplied saved id, otherwise0. This ledger lookup is not array indexing by id or common-object runtime handle resolution. Geometry-record subtype beyond observed collection/layout is not inferred solely from helper.
int __thiscall rf_solid_find_geometry_record_by_saved_id(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(this + 36); ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(this + 36, i) + 36) == a2 )
      return *(_DWORD *)sub_552200(this + 36, i);
  }
  return 0;
}

