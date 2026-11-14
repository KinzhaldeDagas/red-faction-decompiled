// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDB10 rf_jpeg_stdio_term_destination
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jdatadst.c:term_destination matched): Computesused=4096-free_in_buffer4;writesusedbytes ifnonzero andfatals37 onshortwrite. Thenfflush(FILE20). Originalbinary does NOT check fflush result or ferror afterward (difference from IJG v6b jdatadst.c,whose source checksboth). Returns fflushresult incidentally despitevoidAPI. No fclose or bufferdeletehere.
int __cdecl rf_jpeg_stdio_term_destination(_DWORD *a1)
{
  int ElementCount; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  v3 = a1[6];
  ElementCount = 4096 - *(_DWORD *)(v3 + 4);
  if ( ElementCount && fwrite(*(const void **)(v3 + 24), 1u, ElementCount, *(FILE **)(v3 + 20)) != ElementCount )
  {
    *(_DWORD *)(*a1 + 20) = 37;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  return fflush(*(FILE **)(v3 + 20));
}

