// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4360 rf_entity_apply_buffered_position_sample
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity. buffer632NULL returns entity pointer bits without state writes. Otherwise low16-bit buffer1324 time passed to stdcall4B3A00(entity,time,outPosition,outVelocity),then always copies output velocity324 and predicted position240,sets remaining432=0. If buffer1320 bit2 set,also copies same output position into physics current228;common object position60 is not explicitly written here. Child fallback reads object60,not physics228;with sample count<2 it supplies shared vector17F10B0 as velocity;other branches supply interpolated/last/current entity velocity. No child-success check,remaining time interpolation or force/torque reset. EAX0 on processed bit-clear exit,vector helper EAX on bit-set,entity
// bits when no buffer;not a uniform success boolean.
float *__cdecl rf_entity_apply_buffered_position_sample(int a1)
{
  float *result; // eax
  float v2[3]; // [esp+0h] [ebp-3Ch] BYREF
  float v3[3]; // [esp+Ch] [ebp-30h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-24h] BYREF
  float source[3]; // [esp+24h] [ebp-18h] BYREF
  float v6[3]; // [esp+30h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(source);
  rf_vector3_default_construct_noop(v6);
  result = (float *)a1;
  if ( *(_DWORD *)(a1 + 632) )
  {
    rf_entity_sample_buffered_position_and_velocity(a1, *(_WORD *)(*(_DWORD *)(a1 + 632) + 1324), v6, source);
    rf_vector_copy((float *)(a1 + 324), copy_result, source);
    rf_vector_copy((float *)(a1 + 240), v3, v6);
    *(float *)(a1 + 432) = 0.0;
    result = (float *)(*(_DWORD *)(*(_DWORD *)(a1 + 632) + 1320) & 2);
    if ( result )
      return rf_vector_copy((float *)(a1 + 228), v2, v6);
  }
  return result;
}

