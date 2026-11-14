// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598C80 rf_audio_environment_get_property_fields
// UNREALRED VERIFIED [network-queues-20261028]: Destination pointer must have56bytes. Uses borrowed IKsPropertySet global0x1BCA300 without null/ready check. Performs14 Get calls(vtable+12) with GUID0x656390,no instance data,4-byte output each,shared actual-byte-count local. IDs2..14 write destination offsets0..48,then ID14 is fetched AGAIN into offset52. This is literal duplicate property14,not property15. Ignores all HRESULTs/byte counts except final HRESULT returned; failed calls can leave partial/uninitialized destination contents. Hex-Rays double-this pseudocode is misleading: disassembly pushes normal8 COM Get arguments.
int __cdecl rf_audio_environment_get_property_fields(int a1)
{
  _BYTE v2[4]; // [esp+4h] [ebp-4h] BYREF

  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    2,
    0,
    0,
    a1,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    3,
    0,
    0,
    a1 + 4,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    4,
    0,
    0,
    a1 + 8,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    5,
    0,
    0,
    a1 + 12,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    6,
    0,
    0,
    a1 + 16,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    7,
    0,
    0,
    a1 + 20,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    8,
    0,
    0,
    a1 + 24,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    9,
    0,
    0,
    a1 + 28,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    10,
    0,
    0,
    a1 + 32,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    11,
    0,
    0,
    a1 + 36,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    12,
    0,
    0,
    a1 + 40,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    13,
    0,
    0,
    a1 + 44,
    4,
    v2);
  (*(void (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
    dword_1BCA300,
    dword_1BCA300,
    &unk_656390,
    14,
    0,
    0,
    a1 + 48,
    4,
    v2);
  return (*(int (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, int, int, _BYTE *))(*dword_1BCA300 + 12))(
           dword_1BCA300,
           dword_1BCA300,
           &unk_656390,
           14,
           0,
           0,
           a1 + 52,
           4,
           v2);
}

