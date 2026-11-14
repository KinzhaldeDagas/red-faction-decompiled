// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD460 sub_4CD460
// UNREALRED VERIFIED [combat-native-followup-20261104]: Copies stored source position/direction first. If parent handle>=0 resolves and emitter flag0x40 is clear, rotates source position by parent common+72 matrix then adds parent common+60 position; rotates direction by the same matrix and normalizes. Uses parent orientation, not velocity-based look axes. Missing parent or flag0x40 preserves raw stored vectors. No automatic transformation of already emitted particles is performed here.
int __thiscall sub_4CD460(int this, float *a2, float *destination)
{
  float v5[3]; // [esp+4h] [ebp-28h] BYREF
  float v6[3]; // [esp+10h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-10h] BYREF
  int v8; // [esp+28h] [ebp-4h]

  v8 = 0;
  rf_vector_copy(destination, copy_result, (const float *)(this + 20));
  rf_vector_copy(a2, v6, (const float *)(this + 8));
  if ( *(int *)(this + 4) > -1 )
  {
    v8 = rf_object_resolve_handle(*(_DWORD *)(this + 4));
    if ( v8 )
    {
      if ( (*(_WORD *)(this + 56) & 0x40) == 0 )
      {
        rf_vector_copy(a2, v5, (const float *)(this + 8));
        rf_vector_rotate_by_matrix3(a2, (float *)(v8 + 72));
        rf_vector_accumulate(a2, (float *)(v8 + 60));
        rf_vector_rotate_by_matrix3(destination, (float *)(v8 + 72));
        rf_vector_normalize_reciprocal_sqrt(destination);
      }
    }
  }
  return v8;
}

