// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00524C60 rf_world_decal_draw_records_attached_to_face
// UNREALRED VERIFIED [decal-updates-20261028]: Only if caller face flags+40 mask0x100000 set, scans active decals and each polygon circular list+212, compares polygon owner+1312 with face, invokes0x524D50(face,decal) for each match and counts matches. If none found clears face flag0x100000. No opacity/texture validity checks here. Multiple matching polygons can invoke draw helper repeatedly; helper itself finds first match.
int __cdecl rf_world_decal_draw_records_attached_to_face(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-14h]
  int v3; // [esp+4h] [ebp-10h]
  int j; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v6; // [esp+10h] [ebp-4h]

  result = a1;
  if ( (*(_DWORD *)(a1 + 40) & 0x100000) != 0 )
  {
    v6 = 0;
    for ( i = unk_A7051C; i; i = v2 )
    {
      result = i;
      for ( j = *(_DWORD *)(i + 212); j; j = v3 )
      {
        if ( *(_DWORD *)(j + 1312) == a1 )
        {
          rf_world_decal_draw_first_polygon_on_face(a1, i);
          ++v6;
        }
        result = i;
        if ( *(_DWORD *)(j + 1320) == *(_DWORD *)(i + 212) )
        {
          v3 = 0;
        }
        else
        {
          result = *(_DWORD *)(j + 1320);
          v3 = result;
        }
      }
      if ( *(_DWORD *)(i + 224) == unk_A7051C )
      {
        v2 = 0;
      }
      else
      {
        result = i;
        v2 = *(_DWORD *)(i + 224);
      }
    }
    if ( !v6 )
    {
      *(_DWORD *)(a1 + 40) &= ~0x100000u;
      return a1;
    }
  }
  return result;
}

