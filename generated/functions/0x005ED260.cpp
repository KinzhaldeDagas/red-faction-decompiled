// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED260 rf_dsound3d_set_listener_transform_and_commit
// UNREALRED VERIFIED [wave-codec-20261028]: Arguments positionXYZ,velocityXYZ,orientation matrix3. Requires ready global0x1F670FC and listener0x1F670F8,else-1. Writes listener position vtable+56,velocity+64,orientation+52 from matrix row2(forward) androw1(up),all flags1. Also sets float2 via vtable+60 andfloat1 via+48,flags1. Calls commit+68; only final commit negative HRESULT returns-1,else0; previous HRESULTs ignored. Does not normalize orientation or validate pointers.
int __cdecl rf_dsound3d_set_listener_transform_and_commit(float *a1, float *a2, float *a3)
{
  if ( !unk_1F670FC )
    return -1;
  if ( !dword_1F670F8 )
    return -1;
  (*(void (__stdcall **)(_DWORD *, _DWORD, float, float, int))(*dword_1F670F8 + 56))(
    dword_1F670F8,
    *a1,
    a1[1],
    a1[2],
    1);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, _DWORD, float, float, int))(*dword_1F670F8 + 64))(
    dword_1F670F8,
    dword_1F670F8,
    *a2,
    a2[1],
    a2[2],
    1);
  (*(void (__stdcall **)(_DWORD *, float, float, float, float, float, float, int))(*dword_1F670F8 + 52))(
    dword_1F670F8,
    a3[6],
    a3[7],
    a3[8],
    a3[3],
    a3[4],
    a3[5],
    1);
  (*(void (__stdcall **)(_DWORD *, _DWORD, int))(*dword_1F670F8 + 60))(dword_1F670F8, 2.0, 1);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, _DWORD, int))(*dword_1F670F8 + 48))(dword_1F670F8, dword_1F670F8, 1.0, 1);
  if ( (*(int (__stdcall **)(_DWORD *))(*dword_1F670F8 + 68))(dword_1F670F8) >= 0 )
    return 0;
  else
    return -1;
}

