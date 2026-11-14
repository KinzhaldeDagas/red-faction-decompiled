// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051D9B0 rf_solid_split_face_for_primary_uv_span
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl solid,face, no return. Skip if signed face textureID DWORD48<0. Resolve bitmap dimensions then U axis0 before V axis1. Per-axis allowed span:dimension>256:4,>128:8,>64:16,>32:32,>16:64,otherwise128 (inclusive boundaries belong smaller bucket). Seed min/max from first corner, then primary UV component4/8 over original ring. Only ORDERED max-min>limit attempts subdivision: n=int(ceil(F32(range/limit))); n==0 exits entire function; step=F32(range/n), if limit<step OR unordered exits. Try cut valuesF32(k*step+min) for signed k0..n-1, including minimum but excluding maximum. Call51DC10(solid,face,axis,cut); FIRST true exits whole function immediately since original face destroyed. If all cuts
// fail continue next axis. No recursive child processing here, no texture sampling/secondaryUV/bounds update, no zero-corner guard.
void __cdecl rf_solid_split_face_for_primary_uv_span(_DWORD *a1, int a2)
{
  float v2; // [esp+8h] [ebp-3Ch]
  int v3; // [esp+Ch] [ebp-38h]
  int v4; // [esp+10h] [ebp-34h]
  float v5; // [esp+14h] [ebp-30h]
  int v6; // [esp+18h] [ebp-2Ch]
  float v7; // [esp+1Ch] [ebp-28h]
  int k; // [esp+20h] [ebp-24h]
  int v9; // [esp+24h] [ebp-20h]
  int j; // [esp+24h] [ebp-20h]
  float v11; // [esp+28h] [ebp-1Ch]
  float v12; // [esp+2Ch] [ebp-18h]
  float v13; // [esp+30h] [ebp-14h]
  float v14; // [esp+30h] [ebp-14h]
  float v15; // [esp+34h] [ebp-10h]
  int v16; // [esp+38h] [ebp-Ch] BYREF
  int v17; // [esp+3Ch] [ebp-8h] BYREF
  int i; // [esp+40h] [ebp-4h]

  if ( *(int *)(a2 + 48) > -1 )
  {
    rf_bitmap_get_resolved_dimensions(*(_DWORD *)(a2 + 48), &v16, &v17);
    for ( i = 0; i < 2; ++i )
    {
      if ( *(&v16 + i) <= 256 )
      {
        if ( *(&v16 + i) <= 128 )
        {
          if ( *(&v16 + i) <= 64 )
          {
            if ( *(&v16 + i) <= 32 )
            {
              if ( *(&v16 + i) <= 16 )
                v11 = 128.0;
              else
                v11 = 64.0;
            }
            else
            {
              v11 = 32.0;
            }
          }
          else
          {
            v11 = 16.0;
          }
        }
        else
        {
          v11 = 8.0;
        }
      }
      else
      {
        v11 = 4.0;
      }
      v9 = *(_DWORD *)(a2 + 64);
      v13 = rf_geomod_corner_primary_uv_component(v9, i);
      v15 = v13;
      v12 = v13;
      if ( *(_DWORD *)(v9 + 20) == *(_DWORD *)(a2 + 64) )
        v4 = 0;
      else
        v4 = *(_DWORD *)(v9 + 20);
      for ( j = v4; j; j = v3 )
      {
        v14 = rf_geomod_corner_primary_uv_component(j, i);
        v12 = rf_float_minimum_two_values(v12, v14);
        v15 = rf_float_maximum_two_values(v15, v14);
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(a2 + 64) )
          v3 = 0;
        else
          v3 = *(_DWORD *)(j + 20);
      }
      if ( v11 < v15 - v12 )
      {
        v2 = (v15 - v12) / v11;
        v6 = (int)rf_math_ceil_float(v2);
        if ( !v6 )
          return;
        v7 = (v15 - v12) / (double)v6;
        if ( v11 < (double)v7 )
          return;
        for ( k = 0; k < v6; ++k )
        {
          v5 = (double)k * v7 + v12;
          if ( rf_solid_split_face_at_primary_uv_value(a1, a2, i, v5) )
            return;
        }
      }
    }
  }
}

