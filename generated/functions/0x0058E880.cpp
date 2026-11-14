// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058E880 rf_dsound_buffer_has_3d_capability
// UNREALRED VERIFIED [dsound-creation-20261028]: Calls DS buffer GetCaps+12 with20-byte structure; returns true only when HRESULT>=0 and caps flags mask0x10set. Does not query3D interface itself,restore lost buffer or validate pointer.
bool __cdecl rf_dsound_buffer_has_3d_capability(int a1)
{
  int v2; // [esp+0h] [ebp-18h] BYREF
  int v3; // [esp+4h] [ebp-14h]
  int v4; // [esp+14h] [ebp-4h]

  v2 = 20;
  v4 = (*(int (__stdcall **)(int, int *))(*(_DWORD *)a1 + 12))(a1, &v2);
  return v4 >= 0 && (v3 & 0x10) != 0;
}

