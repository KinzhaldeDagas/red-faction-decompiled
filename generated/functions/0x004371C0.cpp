// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004371C0 rf_entity_update_motion_ambient_voice_gain
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity), heterogeneous EAX, not a success Boolean; prologue PUSH ECX only allocates gain local,
// no incoming ECX argument. FIRST flags entity2068 mask0x20: if voice2052!=-1 set source gain0 through568880, then exit WITHOUT clearing handle, updating position or querying death;
// absent voice exits too. With flag clear, dead433F60 EXACT AL1: for any voice!=-1 set source gain0 then write entity2052=-1; no voice stop/release call. Absent voice on live path
// exits. Other dead bytes use live branch. For live voice, ratio startsFLOAT0; only ORDERED current speedFLOAT2240>DOUBLE0.009999999776482582 computes round32(length(entity
// vector324)/speed2240); <=/NaN speed skips ratio.438AC0 ANY nonzero plus Player5168->viewWrapper196 getter4118B0 FULL DWORD8==0 forces ratio0 and SKIPS clamp/state/vehicle queries.
// Otherwise clamp via40D620(lower=class660 FLOAT432,upperFLOAT1), ordered-only with no inverted/NaN-bound normalization; NaN ratio survives. Then state1312==EXACT1 AND vehicle
// predicate437690 AL0 forces0, any nonzero vehicle preserves clamped ratio. Always source-gain update568880(RE-READ voice2052,ratio), then position5688D0(RE-READ voice2052,entity60),
// passing final fullEAX through. Invalid non--1 voice handles are delegated, no independent validity/admission result; early flags/absent/dead paths return pointer/byte/helper
// residue. No local-player identity proof, create/stop/release, finite/clamped-minimum guarantee, deadline or rollback.
int __cdecl rf_entity_update_motion_ambient_voice_gain(int a1)
{
  int v1; // ecx
  int result; // eax
  int v3; // [esp+8h] [ebp-4h] BYREF

  v3 = v1;
  result = a1;
  if ( (*(_DWORD *)(a1 + 2068) & 0x20) != 0 )
  {
    if ( *(_DWORD *)(a1 + 2052) != -1 )
      return (int)rf_ambient_voice_set_source_gain(*(_DWORD *)(a1 + 2052), 0.0);
  }
  else
  {
    result = rf_entity_is_dead(a1);
    if ( (unsigned __int8)result == 1 )
    {
      if ( *(_DWORD *)(a1 + 2052) != -1 )
      {
        result = (int)rf_ambient_voice_set_source_gain(*(_DWORD *)(a1 + 2052), 0.0);
        *(_DWORD *)(a1 + 2052) = -1;
      }
    }
    else if ( *(_DWORD *)(a1 + 2052) != -1 )
    {
      *(float *)&v3 = 0.0;
      if ( *(float *)(a1 + 2240) > 0.009999999776482582 )
        *(float *)&v3 = rf_vector3_length((float *)(a1 + 324)) / *(float *)(a1 + 2240);
      if ( !sub_438AC0(a1) || rf_view_wrapper_get_dword8(*(_DWORD *)(*(_DWORD *)(a1 + 5168) + 196)) )
      {
        rf_float_clamp_in_place((float *)&v3, *(float *)(*(_DWORD *)(a1 + 660) + 432), 1.0);
        if ( *(_DWORD *)(a1 + 1312) == 1 && !rf_object_is_use_vehicle((_DWORD *)a1) )
          *(float *)&v3 = 0.0;
      }
      else
      {
        *(float *)&v3 = 0.0;
      }
      rf_ambient_voice_set_source_gain(*(_DWORD *)(a1 + 2052), *(float *)&v3);
      return rf_ambient_voice_set_position(*(_DWORD *)(a1 + 2052), (float *)(a1 + 60));
    }
  }
  return result;
}

