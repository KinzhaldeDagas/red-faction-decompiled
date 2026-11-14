// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDCA0 rf_jpeg_emit_message_default
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jerror.c:emit_message matched): Cdecl(cinfo,msg_level). Negativelevelwarning:outputs ifnum_warnings108==0 ORtrace_level104>=3,thenincrementswarnings. Nonnegativeleveltrace:outputs onlytrace_level>=msg_level. Does not resetcounts,formatitself orchange fatalpolicy. Default suppressesrepeatwarnings afterfirstunlesshightrace;APIvoid.
int *__cdecl rf_jpeg_emit_message_default(int *a1, int a2)
{
  int *result; // eax
  int v3; // [esp+0h] [ebp-4h]

  result = a1;
  v3 = *a1;
  if ( a2 >= 0 )
  {
    if ( *(_DWORD *)(v3 + 104) >= a2 )
      return (int *)(*(int (__cdecl **)(int *))(v3 + 8))(a1);
  }
  else
  {
    if ( !*(_DWORD *)(v3 + 108) || *(int *)(v3 + 104) >= 3 )
      (*(void (__cdecl **)(int *))(v3 + 8))(a1);
    ++*(_DWORD *)(v3 + 108);
    return (int *)v3;
  }
  return result;
}

