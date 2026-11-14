// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552220 rf_lightmap_atlas_try_claim_padded_rect
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall page,requestedW/H,outX,outY. NULL occupancy pointer0 returnsfalse. PaddingP=15A6B30,paddedW=W+2P,H=H+2P. Scans top-left Y increasing then X increasing;accepts right/bottom equality with page dimensions4/8. For candidate,checks every occupancy byte0;first wholly free candidate writes outputs(x+P,y+P),marks ALL padded bytes1,returnsAL1. Failure returns0 without output writes/occupancy changes. No rotation,best-fit optimization,padding/dimension/overflow validation. NOT a pure find/query:success reserves region.
char __thiscall rf_lightmap_atlas_try_claim_padded_rect(_DWORD *this, int a2, int a3, _DWORD *a4, _DWORD *a5)
{
  BOOL v6; // [esp+4h] [ebp-14h]
  int k; // [esp+8h] [ebp-10h]
  int n; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  int j; // [esp+10h] [ebp-8h]
  int m; // [esp+10h] [ebp-8h]
  int v12; // [esp+14h] [ebp-4h]
  int v13; // [esp+20h] [ebp+8h]
  int v14; // [esp+24h] [ebp+Ch]

  if ( !*this )
    return 0;
  v13 = a2 + 2 * unk_15A6B30;
  v14 = a3 + 2 * unk_15A6B30;
  v12 = 0;
LABEL_4:
  if ( v12 >= *(this + 2) )
    return 0;
  if ( v14 + v12 > *(this + 2) )
    return 0;
  for ( i = 0; ; ++i )
  {
    if ( i >= *(this + 1) )
    {
      ++v12;
      goto LABEL_4;
    }
    if ( v13 + i <= *(this + 1) )
    {
      v6 = 0;
      for ( j = 0; j < v14 && !v6; ++j )
      {
        for ( k = 0; k < v13 && !v6; ++k )
          v6 = *(_BYTE *)(*this + k + i + *(this + 1) * (j + v12)) != 0;
      }
      if ( !v6 )
        break;
    }
  }
  *a4 = unk_15A6B30 + i;
  *a5 = unk_15A6B30 + v12;
  for ( m = 0; m < v14; ++m )
  {
    for ( n = 0; n < v13; ++n )
      *(_BYTE *)(n + i + *(this + 1) * (m + v12) + *this) = 1;
  }
  return 1;
}

