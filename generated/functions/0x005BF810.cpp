// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BF810 rf_particle_instance_update
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Subtracts definition frame offset+200 from caller frame; negative result does nothing. Maintains previous/current origin+44/+32 and optional world orientation+56,then samples emitter key and updates force channels. deltaSeconds=(new-lastFrame)/15,or(frameCount-lastFrame+new)/15 when wrap byte nonzero. Updates elapsedSeconds,ages active particles by delta,kills when age>=lifetime (age=-1,liveCount--). Computes emitter velocity=(current-previous)/delta WITHOUT zero guard; accumulates backlog. Unless bypass byte or definition flag0x20,frustum-culls conservative sphere using lifetime,maxSpeed/maxSpread,shape extents; outside sets runtime flags+20 high bit and postpones force integration,while still allowing emission
// and lastFrame update. Unknown shape in cull branch sets high bit and RETURNS before emission/lastFrame update. Visible prior-unflagged instances use5BD420; prior-culled instances clear high bit and use backlog integrator5BCC60; processed backlog reset0. Finally emits via5BC330 and stores new lastFrame. No channelCount<=3,frame count,positive delta,particle capacity or pointer validation.
void __thiscall rf_particle_instance_update(float *this, float a2, float *source, float *a4, char a5, char a6)
{
  double v6; // st7
  double v7; // st7
  float *v8; // eax
  float *v9; // eax
  float scalar; // [esp+8h] [ebp-A8h]
  float v11; // [esp+10h] [ebp-A0h]
  float v12; // [esp+14h] [ebp-9Ch]
  int v13; // [esp+18h] [ebp-98h]
  float v14; // [esp+1Ch] [ebp-94h]
  float sum_result[3]; // [esp+24h] [ebp-8Ch] BYREF
  float out_vector[3]; // [esp+30h] [ebp-80h] BYREF
  float v18[3]; // [esp+3Ch] [ebp-74h] BYREF
  float v19[3]; // [esp+48h] [ebp-68h] BYREF
  float copy_result[3]; // [esp+54h] [ebp-5Ch] BYREF
  float lhs[3]; // [esp+60h] [ebp-50h] BYREF
  float v22; // [esp+6Ch] [ebp-44h]
  float rhs[3]; // [esp+70h] [ebp-40h] BYREF
  float v24; // [esp+7Ch] [ebp-34h]
  float vector[3]; // [esp+80h] [ebp-30h] BYREF
  int v26[3]; // [esp+8Ch] [ebp-24h] BYREF
  char v27; // [esp+9Bh] [ebp-15h]
  float v28; // [esp+9Ch] [ebp-14h]
  float v29[3]; // [esp+A0h] [ebp-10h] BYREF
  int i; // [esp+ACh] [ebp-4h]
  float v31; // [esp+B8h] [ebp+8h]

  v31 = a2 - (double)*(int *)(*(_DWORD *)this + 200);
  if ( v31 >= 0.0 )
  {
    if ( *(this + 7) > 0.0 )
      rf_vector_copy(this + 11, copy_result, this + 8);
    if ( source )
      rf_vector_copy(this + 8, v19, source);
    if ( a4 )
      rf_matrix3_copy(this + 14, a4);
    if ( *(this + 7) == 0.0 )
      rf_vector_copy(this + 11, v18, this + 8);
    rf_particle_instance_sample_emitter_key(this, v31);
    for ( i = 0; i < (*(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF); ++i )
      rf_scene_frame_channel_state_update(*((float **)this + i + 1), v31);
    if ( a5 )
      v6 = ((double)*(int *)(*(_DWORD *)this + 204) - *(this + 38) + v31) * 0.06666667014360428;
    else
      v6 = (v31 - *(this + 38)) * 0.06666667014360428;
    v28 = v6;
    if ( *(this + 38) >= 0.0 )
      v7 = *(this + 7) + v28;
    else
      v7 = v31 * 0.06666667014360428 + *(this + 7);
    *(this + 7) = v7;
    for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
    {
      if ( *(float *)(*((_DWORD *)this + 36) + 36 * i) >= 0.0 )
      {
        *(float *)(36 * i + *((_DWORD *)this + 36)) = *(float *)(*((_DWORD *)this + 36) + 36 * i) + v28;
        if ( *(float *)(*((_DWORD *)this + 36) + 36 * i + 4) <= (double)*(float *)(*((_DWORD *)this + 36) + 36 * i) )
        {
          *(float *)(36 * i + *((_DWORD *)this + 36)) = -1.0;
          --*((_DWORD *)this + 37);
        }
      }
    }
    scalar = v28;
    v8 = rf_vector_subtract(this + 8, out_vector, this + 11);
    rf_vector_divide(v8, v29, scalar);
    v27 = 0;
    *(this + 40) = *(this + 40) + v28;
    if ( !a6 && (*(_DWORD *)(*(_DWORD *)this + 172) & 0x20) == 0 )
    {
      rf_vector3_copy_return_destination((float *)v26, this + 23);
      rf_vector_rotate_by_matrix3((float *)v26, this + 14);
      rf_vector_accumulate((float *)v26, this + 8);
      v22 = (double)*(int *)(*(_DWORD *)this + 160) * (*(float *)(*(_DWORD *)this + 164) + 1.0) / 4800.0;
      v14 = *(float *)(*(_DWORD *)this + 212) + *(float *)(*(_DWORD *)this + 216);
      rf_vector3_set_components_return_destination(
        vector,
        *(float *)(*(_DWORD *)this + 216),
        v14,
        *(float *)(*(_DWORD *)this + 216));
      rf_vector_multiply_scalar(vector, rhs, v22);
      v13 = *(_DWORD *)(*(_DWORD *)this + 168);
      if ( v13 )
      {
        if ( v13 != 1 )
        {
          v27 = 1;
          *((_DWORD *)this + 5) |= 0x80000000;
          return;
        }
        v24 = rf_vector3_length(rhs) + *(this + 30);
      }
      else
      {
        v12 = *(this + 31) / 2.0;
        v11 = *(this + 30) / 2.0;
        rf_vector3_set_components_return_destination(lhs, v11, 0.0, v12);
        v9 = rf_vector_add(lhs, sum_result, rhs);
        v24 = rf_vector3_length(v9);
      }
      if ( rf_frustum_reject_sphere((float *)v26, v24) )
      {
        v27 = 1;
        *((_DWORD *)this + 5) |= 0x80000000;
      }
    }
    if ( !v27 )
    {
      if ( *((int *)this + 5) >= 0 )
      {
        rf_particle_instance_integrate_current_interval(this, v31, v28);
      }
      else
      {
        *((_DWORD *)this + 5) &= ~0x80000000;
        rf_particle_instance_integrate_backlog(this, v31, v29);
      }
      *(this + 40) = 0.0;
    }
    rf_particle_instance_emit_between_frames(this, v31, v28, v29);
    *(this + 38) = v31;
  }
}

