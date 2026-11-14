// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D8D00 rf_entity_commit_motion_and_dispatch_contact
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity. Bit424 mask0x4000: calls body-finalize,sets common72=current252,updates angular offsets,visual2016=current252 then rotates visual up about right by2172+2196 and forward by2180+2204. If remaining432 is ORDERED0 AND current-contact bit0x10000000 absent,sets material4992=-1 and exits. Nonzero OR unordered remaining,or contact bit,set: runtime-enabled predicate438090(entity,-1) bypasses settling. Otherwise only deactivates P136 if bit0x400000 clear,ORDERED squared velocity324<1 AND ORDERED scalar152^2>squared angular348. Active path q=-dot(angular348,current row264),clamps q to[-scalar152,+scalar152] using ORDERED comparisons (NaN q remains NaN),adds row264*q*GLOBAL frame delta to348. Ordinary
// non-bit0x4000 path computes consumed=float(oldRemaining*oldFraction460),newRemaining=oldRemaining-consumed BEFORE any positional backoff. Fraction>=1 OR unordered takes unobstructed commit5060. Smaller ordered fraction: displacement=predicted240-current228,length unguarded;unless bit0x400000 set,replaces fraction by(length*oldFraction-double0.05000000074505806)/length when >=0 OR unordered,otherwise0. Thus zero-length0/0 can publish NaN. Moves current228 bydisplacement*adjustedFraction,advances Euler2148 using angular336*oldRemaining*adjustedFraction filtered by445AF0 and one-step pitch-clamped Euler helper;rebuilds current252 and tensor P136. If bit0x20000000 set,clears it and SKIPS contact dispatch/response/current-contact-bit set;otherwise calls ECX434670:code2 invokes velocity/impact response59C0,code0 would zero newRemaining,othercode skips velocity response;then ORs0x10000000.
// Current434670 returns only1/2,but caller has code0 branch. Stores PRE-BACKOFF newRemaining to432 even after full-step or timing-only branch. No pointer,length,finite guard;return EAX is branch-dependent incidental result,not uniform success.
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: Contact and unobstructed commits can both update retained7E0. Caller4B8C20 physics work batch selects4D8D00; its unobstructed tail invokes4D5060, while contact branches additionally use2196/2204 view offsets. A birth-only7E0 cache or post hoc UEActor orientation resync does not preserve this owner or frame phase.
// UNREALRED VERIFIED [combat-original-facing-20261112]: Ordinary non4000 smaller-ordered-fraction branch locally updates current228,2148,current252 and rotated tensor after positional backoff; it does NOT locally copy/construct view2016. The ordinary full/unordered-fraction branch delegates5060, which does construct view2016 and copies current252 to COMMON72/predicted288. This is a distinction between the shown local math paths only: contact dispatch434670/response59C0 and their transitive effects are independent calls, not proven absent view writers. PRE-BACKOFF consumed/newRemaining locals remain authoritative across those calls.
float *__cdecl rf_entity_commit_motion_and_dispatch_contact(int a1)
{
  float *result; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  const float *v5; // eax
  float scalar; // [esp+Ch] [ebp-ACh]
  float v7; // [esp+10h] [ebp-A8h]
  float v8; // [esp+14h] [ebp-A4h]
  float v9; // [esp+18h] [ebp-A0h]
  _BYTE v10[36]; // [esp+1Ch] [ebp-9Ch] BYREF
  float v11[3]; // [esp+40h] [ebp-78h] BYREF
  float v12[3]; // [esp+4Ch] [ebp-6Ch] BYREF
  float v13[3]; // [esp+58h] [ebp-60h] BYREF
  float v14[3]; // [esp+64h] [ebp-54h] BYREF
  float copy_result[3]; // [esp+70h] [ebp-48h] BYREF
  float scaled_result[3]; // [esp+7Ch] [ebp-3Ch] BYREF
  int v17; // [esp+88h] [ebp-30h]
  float v18; // [esp+8Ch] [ebp-2Ch]
  float out_vector[3]; // [esp+90h] [ebp-28h] BYREF
  float v20; // [esp+9Ch] [ebp-1Ch]
  float v21; // [esp+A0h] [ebp-18h]
  int v22[3]; // [esp+A4h] [ebp-14h] BYREF
  float v23; // [esp+B0h] [ebp-8h]
  float v24; // [esp+B4h] [ebp-4h]

  if ( (*(_DWORD *)(a1 + 424) & 0x4000) != 0 )
  {
    rf_physics_body_finalize_step(a1);
    rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 252));
    rf_entity_angular_offsets_decay_clamp_and_wrap_once((float *)a1);
    rf_matrix3_copy((float *)(a1 + 2016), (const float *)(a1 + 252));
    v9 = *(float *)(a1 + 2172) + *(float *)(a1 + 2196);
    rf_matrix3_rotate_up_about_right_axis((float *)(a1 + 2016), v9);
    v8 = *(float *)(a1 + 2180) + *(float *)(a1 + 2204);
    rf_matrix3_rotate_up_about_forward_axis((float *)(a1 + 2016), v8);
    if ( *(float *)(a1 + 432) != 0.0 || (result = (float *)(*(_DWORD *)(a1 + 424) & 0x10000000)) != nullptr )
    {
      result = (float *)rf_entity_runtime_enabled_or_resolved_attachment(a1, -1);
      if ( !(_BYTE)result )
      {
        if ( (*(_DWORD *)(a1 + 424) & 0x400000) != 0
          || rf_vector_length_squared((float *)(a1 + 324)) >= 1.0
          || *(float *)(a1 + 152) * *(float *)(a1 + 152) <= rf_vector_length_squared((float *)(a1 + 348)) )
        {
          v21 = -rf_vector_dot((float *)(a1 + 348), (float *)(a1 + 264));
          if ( *(float *)(a1 + 152) >= (double)v21 )
          {
            if ( v21 < -*(float *)(a1 + 152) )
              v21 = -*(float *)(a1 + 152);
          }
          else
          {
            v21 = *(float *)(a1 + 152);
          }
          v7 = v21 * rf_frame_delta_seconds;
          rf_vector_scale((float *)v22, v7, (float *)(a1 + 264));
          return rf_vector_accumulate((float *)(a1 + 348), (float *)v22);
        }
        else
        {
          return rf_physics_state_deactivate(a1 + 136);
        }
      }
    }
    else
    {
      *(_DWORD *)(a1 + 4992) = -1;
    }
  }
  else
  {
    v24 = *(float *)(a1 + 432) * *(float *)(a1 + 460);
    v23 = *(float *)(a1 + 432) - v24;
    if ( *(float *)(a1 + 460) >= 1.0 )
    {
      result = rf_entity_commit_unobstructed_motion_and_bounds(a1);
    }
    else
    {
      rf_vector_subtract((const float *)(a1 + 240), out_vector, (const float *)(a1 + 228));
      v20 = rf_vector3_length(out_vector);
      if ( (*(_DWORD *)(a1 + 424) & 0x400000) == 0 )
      {
        v18 = (v20 * *(float *)(a1 + 460) - 0.05000000074505806) / v20;
        if ( v18 >= 0.0 )
          *(float *)(a1 + 460) = v18;
        else
          *(float *)(a1 + 460) = 0.0;
      }
      rf_vector3_scale_in_place_return_self(out_vector, *(float *)(a1 + 460));
      rf_vector_accumulate((float *)(a1 + 228), out_vector);
      scalar = *(float *)(a1 + 460) * *(float *)(a1 + 432);
      v2 = rf_vector_multiply_scalar((const float *)(a1 + 336), scaled_result, scalar);
      rf_vector_copy(out_vector, copy_result, v2);
      v3 = rf_entity_filter_rotation_axes_for_body(v14, a1, out_vector);
      rf_vector_copy(out_vector, v13, v3);
      v4 = rf_euler_angles_add_clamp_pitch_wrap_once(v12, (float *)(a1 + 2148), out_vector, 0);
      rf_vector_copy((float *)(a1 + 2148), v11, v4);
      v5 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v10, (float *)(a1 + 2148));
      rf_matrix3_copy((float *)(a1 + 252), v5);
      rf_physics_state_rebuild_rotated_tensor(a1 + 136);
      if ( (*(_DWORD *)(a1 + 424) & 0x20000000) != 0 )
      {
        result = (float *)(*(_DWORD *)(a1 + 424) & 0xDFFFFFFF);
        *(_DWORD *)(a1 + 424) = result;
      }
      else
      {
        v17 = rf_entity_contact_effects_and_response_code(a1);
        if ( v17 )
        {
          if ( v17 == 2 )
            rf_entity_resolve_contact_velocity_and_impact_damage(a1);
        }
        else
        {
          v23 = 0.0;
        }
        result = (float *)a1;
        *(_DWORD *)(a1 + 424) |= 0x10000000u;
      }
    }
    *(float *)(a1 + 432) = v23;
  }
  return result;
}

