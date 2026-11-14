// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0E00 rf_bolt_emitter_regenerate_points_and_render
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall emitter,rendererArg RET4. Queries pause BYTE via named helper; when nonzero skips ALL point regeneration/random draws but still forwards render. When unpaused scans four
// slots, ordered life>0 only (TEST AH41/JNZ excludes <=0 and NaN). Uses generic first-DWORD getter486DE0 on slot-array+8 as COUNT (same machine getter used elsewhere for room
// pointers), not object lookup. For j=0..count-1: denominator=F32(count+2), t=F32((j+1)/denominator); evaluates cubic curve at t into existing vector pointer, then adds random unit
// vector scaled by emitter float84. No lifetime taper; even zero jitter amplitude consumes random direction call. Highest t=count/(count+2), not count/(count+1), preserving endpoint
// gap.
// Paused path retains old sampled vectors. Render always invokes4C0310(receiver,rendererArg,pausedBYTE), returning backend result. No active88 check, per-frame sampling cache,
// dt/life update, slot allocation/null-vector guard, finite/count/denominator validation or room refresh. Repeated unpaused render calls resample noise each time.
int *__thiscall rf_bolt_emitter_regenerate_points_and_render(float *this, int a2)
{
  float **v2; // eax
  float **v3; // eax
  float v5; // [esp+4h] [ebp-28h]
  int j; // [esp+10h] [ebp-1Ch]
  float v8; // [esp+14h] [ebp-18h]
  int i; // [esp+18h] [ebp-14h]
  float v10[3]; // [esp+1Ch] [ebp-10h] BYREF
  char v11; // [esp+2Bh] [ebp-1h]

  rf_vector3_default_construct_noop(v10);
  v11 = 0;
  v11 = rf_game_pause_gate_query();
  if ( !v11 )
  {
    for ( i = 0; i < 4; ++i )
    {
      if ( *(this + 17 * i + 28) > 0.0 )
      {
        v8 = (double)rf_receiver_get_first_dword(this + 17 * i + 30) + 2.0;
        for ( j = 0; j < rf_receiver_get_first_dword(this + 17 * i + 30); ++j )
        {
          v5 = ((double)j + 1.0) / v8;
          v2 = (float **)sub_552200((_DWORD *)this + 17 * i + 30, j);
          rf_cubic_bezier_evaluate_position(*((float ***)this + 17 * i + 29), *v2, v5);
          rf_random_unit_vector_from_z_and_azimuth(v10);
          rf_vector3_scale_in_place_return_self(v10, *(this + 21));
          v3 = (float **)sub_552200((_DWORD *)this + 17 * i + 30, j);
          rf_vector_accumulate(*v3, v10);
        }
      }
    }
  }
  return rf_bolt_emitter_forward_ribbon_backend(this, a2, v11);
}

