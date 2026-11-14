// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502790 rf_goal_state_pack_shared_names
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Scan shared table0x90B0F0,count0x90B050,stride16. Only names with string length<16 bytes are exported, copying C string including terminator into20-byte entry name[16], then raw current count from record+0xC to entry+0x10. Longer names skipped; remaining name padding and initial value+8 are not packed/cleared. Export count stored as byte; no shared registry mutation.
_BYTE *__cdecl rf_goal_state_pack_shared_names(int a1, _BYTE *a2)
{
  char v2; // dl
  _BYTE *v4; // [esp+8h] [ebp-14h]
  const char *v5; // [esp+Ch] [ebp-10h]
  std::exception *v6; // [esp+10h] [ebp-Ch]
  int i; // [esp+14h] [ebp-8h]
  int v8; // [esp+18h] [ebp-4h]

  v8 = 0;
  for ( i = 0; i < dword_90B050; ++i )
  {
    v6 = (std::exception *)&byte_90B0F0[16 * i];
    if ( (int)rf_string_length_from_cstr((const char **)v6) < 16 )
    {
      v5 = rf_string_object_c_str_or_empty(v6);
      v4 = (_BYTE *)(a1 + 20 * v8);
      do
      {
        v2 = *v5;
        *v4++ = *v5++;
      }
      while ( v2 );
      *(_DWORD *)(a1 + 20 * v8++ + 16) = *((_DWORD *)v6 + 3);
    }
  }
  *a2 = v8;
  return a2;
}

