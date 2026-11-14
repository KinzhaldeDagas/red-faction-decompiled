// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E4C40 rf_fighter_chaingun_model_release
// UNREALRED VERIFIED [resource-pools-20261028]: If signed global0x662F30>-1, releases descriptor through unknown_libname_26 then sets global-1. Other cached prop indices0x662F34/38 unchanged. This is shared fighter chaingun model created by0x4E46B0; no allocation free when global alreadynegative.
void __cdecl rf_fighter_chaingun_model_release()
{
  if ( dword_662F30 > -1 )
  {
    rf_model_handle_destroy_cdecl_adapter((_DWORD *)dword_662F30);
    dword_662F30 = -1;
  }
}

