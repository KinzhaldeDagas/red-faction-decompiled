// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053AA20 rf_procedural_bitmap_update_marked_records
// UNREALRED VERIFIED [decal-updates-20261028]: If enable byte0x663CBC nonzero, scans active procedural pool0x142665C via circular next+8. Only when record marker+4 equals global0x18092E0 AND last-update signed dword+0<marker invokes callback pointer+32(record), writes last-update=current global marker. Does not clamp mode/index or check callback pointer. Local updated-count not consistently returned: EAX branch-dependent traversal value, not reliable number updated. Marker wrap/sign comparison behavior is literal.
int rf_procedural_bitmap_update_marked_records()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int v3; // [esp+8h] [ebp-4h]

  v3 = 0;
  result = (unsigned __int8)byte_663CBC;
  if ( byte_663CBC )
  {
    for ( i = unk_142665C; i; i = v1 )
    {
      result = *(_DWORD *)(i + 4);
      if ( result == LODWORD(flt_18092A0[16]) )
      {
        result = *(_DWORD *)i;
        if ( *(_DWORD *)i < *(_DWORD *)(i + 4) )
        {
          (*(void (__cdecl **)(int))(i + 32))(i);
          *(float *)i = flt_18092A0[16];
          result = ++v3;
        }
      }
      if ( *(_DWORD *)(i + 8) == unk_142665C )
      {
        v1 = 0;
      }
      else
      {
        result = i;
        v1 = *(_DWORD *)(i + 8);
      }
    }
  }
  return result;
}

