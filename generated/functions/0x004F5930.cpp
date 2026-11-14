// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5930 rf_world_decal_snapshot_restore
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] For each100-byte input with nonempty filename+60, initialize decal setup through0x525110, copy saved position/orientation/vector, load bitmap(name,-1,1), recover signed low-byte field and ARITHMETIC-right-shift packed flags by8, retain scalar+96, query world association0x517060 and submit rf_impact_decal_world_submit. No local bitmap-load-success guard, clearing of existing decal registry, uniqueness check or stable-id matching.
void __cdecl rf_world_decal_snapshot_restore(int a1, int a2)
{
  float v2[3]; // [esp+0h] [ebp-7Ch] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-70h] BYREF
  float *source; // [esp+18h] [ebp-64h]
  float destination[3]; // [esp+1Ch] [ebp-60h] BYREF
  float v6[9]; // [esp+28h] [ebp-54h] BYREF
  float v7[5]; // [esp+4Ch] [ebp-30h] BYREF
  char v8; // [esp+60h] [ebp-1Ch]
  int v9; // [esp+64h] [ebp-18h]
  int v10; // [esp+68h] [ebp-14h]
  int v11; // [esp+6Ch] [ebp-10h]
  float v12; // [esp+70h] [ebp-Ch]
  int i; // [esp+78h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    rf_decal_parameter_record_construct((int)destination);
    source = (float *)(a1 + 100 * i);
    if ( *((_BYTE *)source + 60) )
    {
      rf_vector_copy(destination, copy_result, source);
      rf_matrix3_copy(v6, source + 3);
      rf_vector_copy(v7, v2, source + 12);
      LODWORD(v7[3]) = rf_bitmap_load_with_optional_mipmap_generation((char *)source + 60, (void *)0xFFFFFFFF, 1);
      v8 = *((_DWORD *)source + 23);
      v9 = *((int *)source + 23) >> 8;
      v12 = source[24];
      v10 = -1;
      LODWORD(v7[4]) = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, source, source, 0);
      v11 = rf_world_solid;
      rf_impact_decal_world_submit((int)destination);
    }
  }
}

