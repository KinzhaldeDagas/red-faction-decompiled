// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED4E0 rf_dsound3d_query_primary_listener_interface
// UNREALRED VERIFIED [wave-codec-20261028]: If listener0x1F670F8 already nonnull,returns0. Gets primary buffer through0x5913B0,QueryInterface vtable0 for GUID0x6562F0 into listener. Nonnegative HRESULT returns0. Failure formats diagnostic Fatal error calling pPrimaryBuffer->QueryInterface using0x5913E0 error string,sets listenernull,returns-1; buffer is local only,no output/log call in this body. Does not check primary buffer pointer before dereference or set ready flag.
int rf_dsound3d_query_primary_listener_interface()
{
  const char *v1; // eax
  int v2; // [esp+0h] [ebp-10Ch]
  char Buffer[256]; // [esp+4h] [ebp-108h] BYREF
  _DWORD *primary_buffer_pointer; // [esp+108h] [ebp-4h]

  if ( dword_1F670F8 )
    return 0;
  primary_buffer_pointer = rf_dsound_get_primary_buffer_pointer();
  v2 = (*(int (__stdcall **)(_DWORD *, void *, _DWORD **))*primary_buffer_pointer)(
         primary_buffer_pointer,
         &unk_6562F0,
         &dword_1F670F8);
  if ( v2 >= 0 )
    return 0;
  v1 = rf_dsound_hresult_name_string(v2);
  sprintf(Buffer, "Fatal error calling pPrimaryBuffer->QueryInterface(): %s\n", v1);
  dword_1F670F8 = nullptr;
  return -1;
}

