// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7B30 rf_model_geometry_read_lod_table
// UNREALRED VERIFIED [original-shadow-radius-20261027] Geometry read after version and LOD count/distances: center vector to +28, radius float to +40, then min/max bounds +44/+56. At 0x5F7C46 the float reader is called and 0x5F7C4E stores ST0 at +0x28; decompiler zero assignments are not reliable float-return evidence. Geometry is installed at mesh+0x8C by 0x5B82C0; 0x566A70 and 0x566AA0 expose center/radius to the model sphere chain.
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl vfile. Reads signed version and rejects<7 (no upper-version bound). Allocates68-byte table,constructor0x5F85A0 calls no-op vector defaults. Reads signedLOD count into0;accepts count<=3 with NO lower bound. Reads count float distances into16+,center vector28,radiusfloat40,minbounds44,maxbounds56;calls LOD reader0x5F7D20 per pointer slot4+. Returns table even countnegative (loops skipped). On count>3 deletes table/NULL;on nested failure releases only earlier successful LODs via0x5F7A00,then deletes table/NULL. Does not inspect vfile status or validate distances/bounds. Float reads are actual ST0 values (existing radius comment retained).
// UNREALRED VERIFIED [combat-panic-bounds-20261104]: Combat navigation source retention: after LOD distances reads native binary32 center atLODtable+28,radius+40,min+44,max+56 directly. Preserve these raw values before Unreal axis/unit conversion; converting radius tofloat centimeters and back can change <=2.5 arrival boundary results.
float *__cdecl rf_model_geometry_read_lod_table(int *a1)
{
  float *v2; // [esp+8h] [ebp-2Ch]
  void *v3; // [esp+14h] [ebp-20h]
  int k; // [esp+1Ch] [ebp-18h]
  int i; // [esp+24h] [ebp-10h]
  int j; // [esp+24h] [ebp-10h]

  if ( rf_binary_stream_read_int32_versioned(a1, 0, 0) < 7 )
    return nullptr;
  v3 = operator new(0x44u);
  if ( v3 )
    v2 = (float *)rf_model_geometry_lod_table_construct_noop_vectors((int)v3);
  else
    v2 = nullptr;
  if ( !v2 )
    return nullptr;
  *(_DWORD *)v2 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  if ( *(int *)v2 <= 3 )
  {
    for ( i = 0; i < *(_DWORD *)v2; ++i )
      v2[i + 4] = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_binary_stream_read_vector3_versioned(a1, v2 + 7, 0, unk_1C8FBDC);
    v2[10] = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_binary_stream_read_vector3_versioned(a1, v2 + 11, 0, unk_1C8FBDC);
    rf_binary_stream_read_vector3_versioned(a1, v2 + 14, 0, unk_1C8FBDC);
    for ( j = 0; ; ++j )
    {
      if ( j >= *(_DWORD *)v2 )
        return v2;
      LODWORD(v2[j + 1]) = rf_model_geometry_read_lod_allocation((int)a1);
      if ( !LODWORD(v2[j + 1]) )
        break;
    }
    for ( k = 0; k < j; ++k )
      rf_model_geometry_release_lod_if_owned(LODWORD(v2[k + 1]));
  }
  operator delete(v2);
  return nullptr;
}

