// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475EE0 rf_cutscene_registries_destroy_all
// UNREALRED VERIFIED [cutscene-ui-20261028]: Operator-deletes each camera-record pointer in0x6FB258. For each cutscene record in0x6FB264, assigns constant0x638354 to RF string in all64 segment entries (record+32+32*i), then scalar-deletes record through0x476DC0(flags1). Releases both pointer-array backing stores. Does not end active playback or clear global active pointer0x6FB24C here.
void **rf_cutscene_registries_destroy_all()
{
  void **v0; // eax
  _DWORD *v1; // eax
  void *v3; // [esp+8h] [ebp-10h]
  int k; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]
  int j; // [esp+14h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6FB258); ++i )
  {
    v0 = (void **)sub_552200(unk_6FB258, i);
    operator delete(*v0);
  }
  for ( j = 0; j < rf_receiver_get_first_dword(unk_6FB264); ++j )
  {
    for ( k = 0; k < 64; ++k )
    {
      v1 = (_DWORD *)sub_552200(unk_6FB264, j);
      rf_string_assign_from_cstr((_DWORD *)(*v1 + 32 * k + 32), (char *)byte_638354);
    }
    v3 = *(void **)sub_552200(unk_6FB264, j);
    if ( v3 )
      rf_cutscene_record_scalar_delete(v3, 1);
  }
  rf_pointer_array_release_storage((void **)unk_6FB258);
  return rf_pointer_array_release_storage((void **)unk_6FB264);
}

