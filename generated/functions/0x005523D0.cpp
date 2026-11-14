// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005523D0 rf_lightmap_atlas_mark_padded_rect
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): If occupancy pointer0 nonNULL,sets bytes1 in rectangle(width+2P,height+2P) starting(x-P,y-P),pitch pageWidth4. No search,free/clear,bounds or sign checks. Null map does nothing;EAX mixed receiver/height-loop result,not reliable pointer or status. Called even after new-page placement failure by552480.
_DWORD *__thiscall rf_lightmap_atlas_mark_padded_rect(_DWORD *this, int a2, int a3, int a4, int a5)
{
  _DWORD *result; // eax
  int j; // [esp+4h] [ebp-10h]
  int v7; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v9; // [esp+10h] [ebp-4h]
  int v10; // [esp+1Ch] [ebp+8h]
  _DWORD *v11; // [esp+20h] [ebp+Ch]

  result = this;
  if ( *this )
  {
    v10 = a2 + 2 * unk_15A6B30;
    result = (_DWORD *)(a3 + 2 * unk_15A6B30);
    v11 = result;
    v7 = a4 - unk_15A6B30;
    v9 = a5 - unk_15A6B30;
    for ( i = 0; i < (int)v11; ++i )
    {
      for ( j = 0; j < v10; ++j )
        *(_BYTE *)(j + v7 + *(this + 1) * (i + v9) + *this) = 1;
      result = (_DWORD *)(i + 1);
    }
  }
  return result;
}

