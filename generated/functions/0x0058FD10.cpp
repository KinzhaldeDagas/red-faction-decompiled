// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058FD10 rf_dsound_query_buffer_3d_interface_if_capable
// UNREALRED VERIFIED [dsound-creation-20261028]: Arguments DS buffer,output interface pointer. GetCaps+12 with20-byte structure; requires success and caps flags mask0x10. Then QueryInterface IID0x6562E0; nonnegative HRESULT returns0. Any failure formats local diagnostic,sets outputnull,returns-1. No null buffer guard; caps lacks mask can report success HRESULT as diagnostic error text. Does not AddRef separately beyond QueryInterface.
int __cdecl rf_dsound_query_buffer_3d_interface_if_capable(int a1, _DWORD *a2)
{
  const char *v3; // eax
  int v4; // [esp+0h] [ebp-120h] BYREF
  int v5; // [esp+4h] [ebp-11Ch]
  int v6; // [esp+14h] [ebp-10Ch]
  char Buffer[260]; // [esp+18h] [ebp-108h] BYREF

  v4 = 20;
  v6 = (*(int (__stdcall **)(int, int *))(*(_DWORD *)a1 + 12))(a1, &v4);
  if ( v6 >= 0 && (v5 & 0x10) != 0 )
  {
    v6 = (**(int (__stdcall ***)(int, void *, _DWORD *))a1)(a1, &unk_6562E0, a2);
    if ( v6 >= 0 )
      return 0;
  }
  v3 = rf_dsound_hresult_name_string(v6);
  sprintf(Buffer, "Could not obtain 3D interface for hardware buffer: %s\n", v3);
  *a2 = 0;
  return -1;
}

