// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556110 rf_solid_select_all_vertices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Clears selected-vertex array204 COUNT while retaining storage, scans all solid vertices120 and appends every pointer without uniqueness checks. No incident-face updates or face selection changes. Return is final all-vertex count.
void __thiscall rf_solid_select_all_vertices(void *this)
{
  int *v1; // eax
  int i; // [esp+4h] [ebp-4h]

  rf_pointer_array_clear_count_keep_storage((_DWORD *)this + 51);
  for ( i = 0; i < rf_receiver_get_first_dword((char *)this + 120); ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)this + 30, i);
    rf_pointer_array_append_dword((_DWORD *)this + 51, *v1);
  }
}

