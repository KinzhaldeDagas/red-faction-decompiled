// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D4E30 rf_entity_angular_offsets_decay_clamp_and_wrap_once
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity pointer. When class predicate43C950 admits flags0x401200, scales entity2196 vector IN PLACE by float exp(float(frameDelta*-3)),adds entity2160 vector into2196,then forces2200(Y)=0. This uses global frame delta,not remaining time432. Always adds2184 vector into2172; clamps XYZ2172/2176/2180 with separate lower floats5172/5176/5180 and upper5184/5188/5192 using ordered-only clamp helper. Then each offset component subtracts ONE double constant6.2831854820251465 if ordered>constant,or adds ONE constant if ordered<-constant; no loop/fmod. Equality and unordered remain unchanged by wraps; bounds need not be ordered. No pointer/class/finite checks; no clearing of2160/2184 here.
void __cdecl rf_entity_angular_offsets_decay_clamp_and_wrap_once(float *a1)
{
  float v1; // [esp+8h] [ebp-8h]
  float v2; // [esp+Ch] [ebp-4h]

  if ( rf_entity_class_has_angular_decay_flags((int)a1) )
  {
    v1 = rf_frame_delta_seconds * -3.0;
    v2 = rf_exp_float(v1);
    rf_vector3_scale_in_place_return_self(a1 + 549, v2);
    rf_vector_accumulate(a1 + 549, a1 + 540);
    a1[550] = 0.0;
  }
  rf_vector_accumulate(a1 + 543, a1 + 546);
  rf_float_clamp_in_place(a1 + 543, a1[1293], a1[1296]);
  rf_float_clamp_in_place(a1 + 544, a1[1294], a1[1297]);
  rf_float_clamp_in_place(a1 + 545, a1[1295], a1[1298]);
  if ( a1[543] <= 6.283185482025146 )
  {
    if ( a1[543] < -6.283185482025146 )
      a1[543] = a1[543] + 6.283185482025146;
  }
  else
  {
    a1[543] = a1[543] - 6.283185482025146;
  }
  if ( a1[544] <= 6.283185482025146 )
  {
    if ( a1[544] < -6.283185482025146 )
      a1[544] = a1[544] + 6.283185482025146;
  }
  else
  {
    a1[544] = a1[544] - 6.283185482025146;
  }
  if ( a1[545] <= 6.283185482025146 )
  {
    if ( a1[545] < -6.283185482025146 )
      a1[545] = a1[545] + 6.283185482025146;
  }
  else
  {
    a1[545] = a1[545] - 6.283185482025146;
  }
}

