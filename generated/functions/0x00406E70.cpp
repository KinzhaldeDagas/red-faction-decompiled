// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00406E70 rf_ai_find_nearest_type27_event_position
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block. Signed pointer-registry count90B0E0 is reread each iteration, element access unchecked;
// only enclosing record DWORD+656==27 is considered. Measures owner COMMON+60 to record vector+64, rounds distancefloat32. Best starts FLOAT_MAX exact0x7F7FFFFF; only ORDERED
// strictly smaller replaces best and copies position, so ties retain first and NaN/Inf/equal-FLOAT_MAX distances never win. After scan exact equality to DOUBLE bits0x47EFFFFFE0000000
// (same float-max value) returns EAX-1 and leaves block vector+1168 unchanged. Otherwise copies selected vector into+1168 and returns EAX0. No radius cap below FLOAT_MAX,
// event-enabled state, activation, owner/type/null guards, route construction or timer effects. Local matrix constructor and initial vector constructor write no data; result is only
// published after successful selection.
int __cdecl rf_ai_find_nearest_type27_event_position(float *a1)
{
  int first_dword; // eax
  int v2; // eax
  int v3; // eax
  float v5[3]; // [esp+0h] [ebp-54h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-48h] BYREF
  float v7; // [esp+18h] [ebp-3Ch]
  float v8; // [esp+1Ch] [ebp-38h]
  char v9[36]; // [esp+20h] [ebp-34h] BYREF
  float destination[3]; // [esp+44h] [ebp-10h] BYREF
  int i; // [esp+50h] [ebp-4h]

  v7 = 3.4028235e38;
  rf_vector3_default_construct_noop(destination);
  rf_matrix3_construct(v9);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= first_dword )
      break;
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) == 27 )
    {
      v2 = sub_552200(unk_90B0E0, i);
      v8 = rf_vector_distance((const float *)(*(_DWORD *)a1 + 60), (const float *)(*(_DWORD *)v2 + 64));
      if ( v7 > (double)v8 )
      {
        v7 = v8;
        v3 = sub_552200(unk_90B0E0, i);
        rf_vector_copy(destination, copy_result, (const float *)(*(_DWORD *)v3 + 64));
      }
    }
  }
  if ( v7 == 3.402823466385289e38 )
    return -1;
  rf_vector_copy(a1 + 292, v5, destination);
  return 0;
}

