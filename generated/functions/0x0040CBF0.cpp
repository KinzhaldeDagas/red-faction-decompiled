// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CBF0 rf_ai_carried_corpse_drop_clearance
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): One required AI block. Resolves carried handle+1212 type7; miss AL0. Reads class scalar FLOAT683588+5396*corpse class index+672 without index
// validation; scalar=float32(2*value+DOUBLE0.6000000238418579). Forms endpoint=source common position+60 +source common forward row+96*scalar. Geometry
// segment(source+60,endpoint,public mask1,NULL)==EXACT AL1 blocks. Then scans all clutter next+652 with class(+660) DWORD+116 mask4, without common inactive/delete filtering.
// Broadphase radiusSq=float32(float32(abs(scalar)+clutter radius+384)^2); proceeds when radiusSq is NOT ordered<distanceSquared(source common position,clutter common position), thus
// equality AND unordered admit broadphase. Inverse-translates/rotates clutter position into source common pose; local Z is admitted when NOT ordered<0, again unordered admitted.
// Returns0 only if abs(localX) is ordered STRICTLY<abs(localZ); ignores local Y/height and no explicit upper forward-Z bound beyond broadphase. Otherwise returns1. No scan of
// entities/projectiles/corpses, no bounding sphere sweep, no radius clamp or finite check. Force-drop caller bypasses this entire predicate.
char __cdecl rf_ai_carried_corpse_drop_clearance(_DWORD *a1)
{
  float *v2; // eax
  double v3; // st7
  float v4; // [esp+4h] [ebp-40h]
  float v5; // [esp+8h] [ebp-3Ch]
  float v6; // [esp+Ch] [ebp-38h]
  float scaled_result[3]; // [esp+10h] [ebp-34h] BYREF
  float v8; // [esp+1Ch] [ebp-28h]
  float v9[2]; // [esp+20h] [ebp-24h] BYREF
  float v10; // [esp+28h] [ebp-1Ch]
  int i; // [esp+2Ch] [ebp-18h]
  float sum_result[3]; // [esp+30h] [ebp-14h] BYREF
  float scalar; // [esp+3Ch] [ebp-8h]
  int v14; // [esp+40h] [ebp-4h]

  v14 = rf_corpse_resolve_handle_type7(a1[303]);
  if ( !v14 )
    return 0;
  scalar = *((float *)&unk_683588 + 1349 * *(_DWORD *)(v14 + 672)) * 2.0 + 0.6000000238418579;
  v2 = rf_vector_multiply_scalar((const float *)(*a1 + 96), scaled_result, scalar);
  rf_vector_add((const float *)(*a1 + 60), sum_result, v2);
  if ( rf_geometry_segment_is_obstructed(*a1 + 60, (int)sum_result, 1, 0) == 1 )
    return 0;
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(*(_DWORD *)(i + 660) + 116) & 4) != 0 )
    {
      v6 = fabs(scalar);
      v8 = v6 + *(float *)(i + 384);
      v8 = v8 * v8;
      v3 = rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(i + 60));
      if ( v8 >= v3 )
      {
        rf_vector3_copy_return_destination(v9, (float *)(i + 60));
        rf_vector_inverse_translate_rotate_in_place(v9, *a1 + 60, *a1 + 72);
        if ( v10 >= 0.0 )
        {
          v5 = fabs(v10);
          v4 = fabs(v9[0]);
          if ( v4 < (double)v5 )
            return 0;
        }
      }
    }
  }
  return 1;
}

