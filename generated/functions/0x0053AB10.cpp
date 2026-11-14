// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053AB10 rf_procedural_bitmap_mark_used_by_handle
// UNREALRED VERIFIED [decal-updates-20261028]: Scans active procedural records; on first generated-bitmap handle+24 equal input, writes record marker+4=current0x18092E0 and returns record. No match returns0 after circular traversal. Does not run pixel callback directly; update0x53AA20 consumes markers.
int __cdecl rf_procedural_bitmap_mark_used_by_handle(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  result = unk_142665C;
  for ( i = unk_142665C; i; i = v2 )
  {
    if ( *(_DWORD *)(i + 24) == a1 )
    {
      *(float *)(i + 4) = flt_18092A0[16];
      return i;
    }
    if ( *(_DWORD *)(i + 8) == unk_142665C )
      v2 = 0;
    else
      v2 = *(_DWORD *)(i + 8);
    result = v2;
  }
  return result;
}

