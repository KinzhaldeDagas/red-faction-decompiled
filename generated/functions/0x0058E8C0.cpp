// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058E8C0 rf_dsound_duplicate_buffer_into_slot
// UNREALRED VERIFIED [dsound-creation-20261028]: Arguments existing DS buffer,backend slot. Device0x1951804 DuplicateSoundBuffer+20 writes slot buffer+0. Nonnegative HRESULT0; failure formats local diagnostic,nulls buffer+0 and3D interface+4,returns-1. Does not release previous slot pointers,clear metadata or check device/slot bounds.
int __cdecl rf_dsound_duplicate_buffer_into_slot(int a1, int a2)
{
  const char *v2; // eax
  int v4; // [esp+0h] [ebp-10Ch]
  char Buffer[260]; // [esp+4h] [ebp-108h] BYREF

  v4 = (*(int (__thiscall **)(LPVOID, LPVOID, int, int *))(*(_DWORD *)MEMORY[0x1951804] + 20))(
         MEMORY[0x1951804],
         MEMORY[0x1951804],
         a1,
         &unk_1BA1820[11 * a2]);
  if ( v4 >= 0 )
    return 0;
  v2 = rf_dsound_hresult_name_string(v4);
  sprintf(Buffer, "DuplicateSoundBuffer failed because: %s\n", v2);
  unk_1BA1820[11 * a2] = 0;
  unk_1BA1824[11 * a2] = 0;
  return -1;
}

