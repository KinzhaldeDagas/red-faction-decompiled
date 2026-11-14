// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525920 rf_world_decal_collect_face_polygons_by_flags
// UNREALRED VERIFIED [decal-projection-20261028]: If face flags+40 has0x300000, scans face polygon chain+76 via next+1328. Includes polygon when parent-decal flags+80 contain ALL required bits(arg5) and NO excluded bits(arg6); copies polygon pointer to caller array up to initial *count capacity, early returns count at exactcapacity. Otherwise writes actual count back. Face withoutflags writes *count=0 but returns original face value. Context arg2 unused. No capacity<=0/output-pointer guards; zero capacity does not prevent first write.
int __cdecl rf_world_decal_collect_face_polygons_by_flags(int a1, int a2, int a3, int *a4, int a5, int a6)
{
  int result; // eax
  int v7; // [esp+0h] [ebp-10h]
  int v8; // [esp+4h] [ebp-Ch]
  int v9; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  result = a1;
  if ( (*(_DWORD *)(a1 + 40) & 0x300000) != 0 )
  {
    v9 = 0;
    for ( i = *(_DWORD *)(a1 + 76); i; i = v7 )
    {
      v7 = *(_DWORD *)(i + 1328);
      v8 = *(_DWORD *)(i + 1316);
      if ( (a5 & *(_DWORD *)(v8 + 80)) == a5 && (a6 & *(_DWORD *)(v8 + 80)) == 0 )
      {
        *(_DWORD *)(a3 + 4 * v9++) = i;
        result = v9;
        if ( v9 == *a4 )
          return result;
      }
    }
    *a4 = v9;
    return v9;
  }
  else
  {
    *a4 = 0;
  }
  return result;
}

