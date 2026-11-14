// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1010 rf_bolt_emitter_refresh_cached_room
// UNREALRED VERIFIED [world-uid-ownership]: Rebuilds a bolt emitter's derived endpoint and spatial-owner state from its resolved common-object attachment, falling back to the authored endpoint when unresolved.
void *__thiscall rf_bolt_emitter_refresh_cached_room(_DWORD *this)
{
  float *v1; // eax
  float *v2; // eax
  void *result; // eax
  float v5[3]; // [esp+8h] [ebp-58h] BYREF
  float v6[3]; // [esp+14h] [ebp-4Ch] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-40h] BYREF
  float out_vector[3]; // [esp+2Ch] [ebp-34h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-28h] BYREF
  float lhs[3]; // [esp+44h] [ebp-1Ch] BYREF
  float destination[3]; // [esp+50h] [ebp-10h] BYREF
  int v12; // [esp+5Ch] [ebp-4h]

  rf_vector3_default_construct_noop(lhs);
  rf_vector3_default_construct_noop(destination);
  v12 = rf_object_resolve_handle(*(this + 3));
  if ( v12 )
  {
    rf_vector_copy(lhs, copy_result, (const float *)this + 10);
    rf_vector_rotate_by_matrix3(lhs, (float *)(v12 + 72));
    rf_vector_accumulate(lhs, (float *)(v12 + 60));
    v1 = rf_vector_subtract(lhs, out_vector, (const float *)this + 4);
    v2 = rf_vector_multiply_scalar(v1, scaled_result, 0.5);
    rf_vector_copy(destination, v6, v2);
    rf_vector_accumulate(destination, (float *)this + 4);
  }
  else
  {
    rf_vector_copy(destination, v5, (const float *)this + 4);
  }
  result = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, destination, destination, 0);
  *(this + 27) = result;
  if ( !*(this + 27) )
  {
    result = rf_world_resolve_cached_room(
               (void *)rf_world_solid,
               nullptr,
               (const float *)this + 4,
               (const float *)this + 4,
               0);
    *(this + 27) = result;
  }
  return result;
}

