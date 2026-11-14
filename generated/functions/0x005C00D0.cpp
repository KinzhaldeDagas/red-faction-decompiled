// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C00D0 rf_sound_backend_set_listener_transform
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready, copies listener position to 1DAE7F8, velocity to 1DAE804, and the 3x3 orientation matrix to 1DAE7D4. Mode 1 also calls rf_dsound3d_set_listener_transform_and_commit with the same three inputs. Cached matrix first row is later used as the pan axis.
int __cdecl rf_sound_backend_set_listener_transform(float *source, float *a2, float *a3)
{
  int result; // eax
  float v4[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  result = rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    rf_vector_copy(flt_1DAE7F8, copy_result, source);
    rf_vector_copy(unk_1DAE804, v4, a2);
    rf_matrix3_copy(unk_1DAE7D4, a3);
    result = rf_sound_backend_mode;
    if ( rf_sound_backend_mode == 1 )
      return rf_dsound3d_set_listener_transform_and_commit(source, a2, a3);
  }
  return result;
}

