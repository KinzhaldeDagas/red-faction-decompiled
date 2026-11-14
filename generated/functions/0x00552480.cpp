// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552480 rf_lightmap_atlas_allocate_region
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Cdecl requestedW/H,outPageIndex,outX,outY. Initializes localXY0. With packed-atlas modeBYTE663D48,scans pages newest-to-oldest within last15A6B20 records,try-claim552220 both finds AND marks padded rectangle. If none,creates fixed square page15A6B24. Without packed mode,always creates own page:per dimension smallest doubling power-of-two>=request+2*padding15A6B30,minimum4. Page constructor24bytes always requested occupancy map. New-page try-claim return IGNORED;then unconditionally calls5523D0 to mark rectangle again and writes page index20,localXY outputs. Returns X coordinate,not boolean success. Thus failed new placement still marks using initializedXY0 (padding subtraction can go negative). No
// NULL/new-page/oversize/overflow handling;power-of-two loop can overflow. Zero-sized requests still perform placement/page side effects. Existing-page marking repeated idempotently by final helper.
int __cdecl rf_lightmap_atlas_allocate_region(int a1, int a2, _DWORD *a3, _DWORD *a4, int *a5)
{
  int first_dword; // eax
  int result; // eax
  _DWORD *v7; // [esp+4h] [ebp-40h]
  _DWORD *v8; // [esp+8h] [ebp-3Ch]
  void *v9; // [esp+Ch] [ebp-38h]
  void *v10; // [esp+14h] [ebp-30h]
  int v11; // [esp+1Ch] [ebp-28h]
  int v12; // [esp+1Ch] [ebp-28h]
  int v13; // [esp+20h] [ebp-24h]
  int v14; // [esp+20h] [ebp-24h]
  int i; // [esp+24h] [ebp-20h]
  _DWORD *v16; // [esp+28h] [ebp-1Ch]
  int v17; // [esp+2Ch] [ebp-18h] BYREF
  int v18; // [esp+30h] [ebp-14h] BYREF
  char v19; // [esp+37h] [ebp-Dh]
  int v20; // [esp+40h] [ebp-4h]

  v17 = 0;
  v18 = 0;
  v16 = nullptr;
  v19 = 0;
  if ( byte_663D48 )
  {
    for ( i = rf_receiver_get_first_dword(unk_15A7148) - 1; ; --i )
    {
      first_dword = rf_receiver_get_first_dword(unk_15A7148);
      if ( i < rf_int_max(first_dword - unk_15A6B20, 0) )
        break;
      v16 = *(_DWORD **)sub_552200(unk_15A7148, i);
      if ( rf_lightmap_atlas_try_claim_padded_rect(v16, a1, a2, &v17, &v18) )
      {
        v19 = 1;
        break;
      }
    }
  }
  if ( !v19 )
  {
    if ( byte_663D48 )
    {
      v10 = operator new(0x18u);
      v20 = 0;
      if ( v10 )
        v8 = (_DWORD *)rf_lightmap_atlas_page24_construct_register((int)v10, unk_15A6B24, unk_15A6B24, 1, 0);
      else
        v8 = nullptr;
      v20 = -1;
      v16 = v8;
      rf_lightmap_atlas_try_claim_padded_rect(v8, a1, a2, &v17, &v18);
    }
    else
    {
      v13 = 1;
      v11 = 1;
      while ( v13 < a1 + 2 * unk_15A6B30 )
        v13 *= 2;
      while ( v11 < a2 + 2 * unk_15A6B30 )
        v11 *= 2;
      v14 = rf_int_max(4, v13);
      v12 = rf_int_max(4, v11);
      v9 = operator new(0x18u);
      v20 = 1;
      if ( v9 )
        v7 = (_DWORD *)rf_lightmap_atlas_page24_construct_register((int)v9, v14, v12, 1, 0);
      else
        v7 = nullptr;
      v20 = -1;
      v16 = v7;
      rf_lightmap_atlas_try_claim_padded_rect(v7, a1, a2, &v17, &v18);
    }
  }
  rf_lightmap_atlas_mark_padded_rect(v16, a1, a2, v17, v18);
  *a3 = v16[5];
  result = v17;
  *a4 = v17;
  *a5 = v18;
  return result;
}

