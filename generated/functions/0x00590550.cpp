// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590550 rf_dsound_buffer_slot_is_playing
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument backend slot,not play handle. Null DS buffer pointer+0 returns0; else GetStatus vtable+36,negative HRESULT0,otherwise status&1. Returns normalized0/1. No index-range validation; cached pause flag is not consulted.
int __cdecl rf_dsound_buffer_slot_is_playing(int a1)
{
  int v2; // [esp+0h] [ebp-8h] BYREF
  int v3; // [esp+4h] [ebp-4h]

  if ( !unk_1BA1820[11 * a1] )
    return 0;
  v3 = (*(int (__stdcall **)(int, int *))(*(_DWORD *)unk_1BA1820[11 * a1] + 36))(unk_1BA1820[11 * a1], &v2);
  if ( v3 >= 0 )
    return v2 & 1;
  else
    return 0;
}

