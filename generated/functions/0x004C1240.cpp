// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1240 rf_bolt_emitters_submit_callbacks_for_room
// UNREALRED VERIFIED [impact-callbacks-20261028]: Scans bolt-emitter registry. Requires emitter room+108==caller,enable byte+88==exactly1,owner handle+12>=0, and resolved owner nonnull. Computes midpoint of emitter+16 and owner position+60, radius=distance(midpoint,emitter+16). Submits callback0x4C1200 with emitter payload,midpoint stored/cullcenter,sort1,optional pointers0,lighting bytes0/1. Does not render now or check submission return; returns registry loop count.
int __cdecl rf_bolt_emitters_submit_callbacks_for_room(int a1)
{
  int result; // eax
  float *v2; // eax
  float *v3; // eax
  float out_vector[3]; // [esp+20h] [ebp-34h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-28h] BYREF
  float lhs[3]; // [esp+38h] [ebp-1Ch] BYREF
  float v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+48h] [ebp-Ch]
  int v9; // [esp+4Ch] [ebp-8h]
  int i; // [esp+50h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(rf_bolt_emitter_registry);
    if ( i >= result )
      break;
    v9 = *(_DWORD *)sub_552200(rf_bolt_emitter_registry, i);
    if ( *(_DWORD *)(v9 + 108) == a1 && *(_BYTE *)(v9 + 88) == 1 && *(int *)(v9 + 12) > -1 )
    {
      v8 = rf_object_resolve_handle(*(_DWORD *)(v9 + 12));
      if ( v8 )
      {
        v2 = rf_vector_add((const float *)(v9 + 16), sum_result, (const float *)(v8 + 60));
        rf_vector_multiply_scalar(v2, lhs, 0.5);
        v3 = rf_vector_subtract(lhs, out_vector, (const float *)(v9 + 16));
        v7 = rf_vector3_length(v3);
        rf_world_submit_render_callback_entry(
          v9,
          (int)lhs,
          (int)lhs,
          v7,
          (int)rf_bolt_emitter_render_callback,
          1,
          0,
          0,
          0,
          0,
          1);
      }
    }
  }
  return result;
}

