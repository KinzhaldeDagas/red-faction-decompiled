// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0AD0 rf_bolt_emitter_tick_slots
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall emitter. active BYTE88 only gates elapsed timestamp384 -> try-spawn4C0340; it does NOT gate existing slot simulation. For each of four slots, native TEST AH41/JNZ skips
// life<=0 OR unordered. Ordered positive life: offset20 += drift44*frameSeconds and offset32 += drift56*frameSeconds (binary32 vector operations), copy offsets to local vectors. For
// signed attachment handle4>-1 and successful handle resolver, reset curve control0 from authored emitter16, rotate by object common matrix72 and translate common position60; rotate
// first local offset only if emitter flags92&8. Second handle12>-1 independently resets control36 from emitter40 and transforms; rotate second local offset only if flag92&16.
// Negative handles other than-1 are skipped too.
// Missing/unresolved attachment leaves previous curve endpoint unchanged, not a fresh authored fallback. Curve control12=control0+first local offset, control24=control36+second local
// offset. Then stores binary32 life-=frameSeconds without clamp; even a slot expiring this tick gets final control update. No pause query, room refresh, point sampling,
// allocation/finite checks or deletion. NaN life is neither simulated nor recycled by spawn. Final loop value returns incidental lowBYTE4, not success.
char __thiscall rf_bolt_emitter_tick_slots(int this)
{
  char result; // al
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v7[3]; // [esp+8h] [ebp-80h] BYREF
  float v8[3]; // [esp+14h] [ebp-74h] BYREF
  float v9[3]; // [esp+20h] [ebp-68h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-5Ch] BYREF
  float v11[3]; // [esp+38h] [ebp-50h] BYREF
  float copy_result[3]; // [esp+44h] [ebp-44h] BYREF
  float v13[3]; // [esp+50h] [ebp-38h] BYREF
  float scaled_result[3]; // [esp+5Ch] [ebp-2Ch] BYREF
  float rhs[3]; // [esp+68h] [ebp-20h] BYREF
  int v16; // [esp+74h] [ebp-14h]
  float v17[3]; // [esp+78h] [ebp-10h] BYREF
  int i; // [esp+84h] [ebp-4h]

  result = this;
  if ( *(_BYTE *)(this + 88) )
  {
    result = rf_replicator_has_elapsed((int *)(this + 384));
    if ( result )
      result = rf_bolt_emitter_try_spawn_and_rearm(this);
  }
  for ( i = 0; i < 4; ++i )
  {
    if ( *(float *)(this + 68 * i + 112) > 0.0 )
    {
      v2 = rf_vector_multiply_scalar((const float *)(this + 68 * i + 156), scaled_result, rf_frame_delta_seconds);
      rf_vector_accumulate((float *)(this + 68 * i + 132), v2);
      v3 = rf_vector_multiply_scalar((const float *)(this + 68 * i + 168), v13, rf_frame_delta_seconds);
      rf_vector_accumulate((float *)(this + 68 * i + 144), v3);
      rf_vector3_copy_return_destination(rhs, (float *)(this + 68 * i + 132));
      rf_vector3_copy_return_destination(v17, (float *)(this + 68 * i + 144));
      if ( *(int *)(this + 4) > -1 )
      {
        v16 = rf_object_resolve_handle(*(_DWORD *)(this + 4));
        if ( v16 )
        {
          rf_vector_copy(*(float **)(this + 68 * i + 116), copy_result, (const float *)(this + 16));
          rf_vector_rotate_by_matrix3(*(float **)(this + 68 * i + 116), (float *)(v16 + 72));
          rf_vector_accumulate(*(float **)(this + 68 * i + 116), (float *)(v16 + 60));
          if ( (*(_DWORD *)(this + 92) & 8) != 0 )
            rf_vector_rotate_by_matrix3(rhs, (float *)(v16 + 72));
        }
      }
      if ( *(int *)(this + 12) > -1 )
      {
        v16 = rf_object_resolve_handle(*(_DWORD *)(this + 12));
        if ( v16 )
        {
          rf_vector_copy((float *)(*(_DWORD *)(this + 68 * i + 116) + 36), v11, (const float *)(this + 40));
          rf_vector_rotate_by_matrix3((float *)(*(_DWORD *)(this + 68 * i + 116) + 36), (float *)(v16 + 72));
          rf_vector_accumulate((float *)(*(_DWORD *)(this + 68 * i + 116) + 36), (float *)(v16 + 60));
          if ( (*(_DWORD *)(this + 92) & 0x10) != 0 )
            rf_vector_rotate_by_matrix3(v17, (float *)(v16 + 72));
        }
      }
      v4 = rf_vector_add(*(const float **)(this + 68 * i + 116), sum_result, rhs);
      rf_vector_copy((float *)(*(_DWORD *)(this + 68 * i + 116) + 12), v9, v4);
      v5 = rf_vector_add((const float *)(*(_DWORD *)(this + 68 * i + 116) + 36), v8, v17);
      rf_vector_copy((float *)(*(_DWORD *)(this + 68 * i + 116) + 24), v7, v5);
      *(float *)(this + 68 * i + 112) = *(float *)(this + 68 * i + 112) - rf_frame_delta_seconds;
    }
    result = i + 1;
  }
  return result;
}

