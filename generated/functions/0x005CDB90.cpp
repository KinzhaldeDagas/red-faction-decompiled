// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CDB90 rf_scene_instance_update_15fps
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Scene runtime fields: flags0,overrideSeconds4,definition8,elapsedSeconds12,currentFrame16,model states20,point states24,emitter states28,transform states32. Flag0x4 immediately returnsfalse. Adds dt to elapsed,frame=overrideSeconds*15 if flag0x10 else elapsed*15. At frame>=definition frameCount+132: loop flag0x2 repeatedly subtracts duration/15 from elapsed,sets wrap byte,updates frame; zero/nonpositive duration can prevent termination. Nonloop calls stop/drain5CDF20. Draining flag0x1 clears shared range-owner1DB4B90 when self; if no emitter has liveCount>0 sets frame=end,flag0x4,returnsfalse,else updates ONLY emitters. Normal path updates points,models,emitters,transforms; particle culling bypass derives flag0x20. If shared range
// owner absent/self,clears it and samples148-byte transform-range definitions between global previous-frame1DB4B94 and current frame; first successful range sets owner=self and returns1. Other live paths return1. Optional origin/orientation forwarded. No count,definition,array or positive-time validation; draining does not update static tracks.
char __thiscall rf_scene_instance_update_15fps(void *this, float a2, const float *a3, const float *a4)
{
  double v5; // st7
  char v7; // [esp+1Ah] [ebp-6h]
  char v8; // [esp+1Bh] [ebp-5h]
  int i; // [esp+1Ch] [ebp-4h]
  int j; // [esp+1Ch] [ebp-4h]
  int k; // [esp+1Ch] [ebp-4h]
  int m; // [esp+1Ch] [ebp-4h]
  int n; // [esp+1Ch] [ebp-4h]
  int ii; // [esp+1Ch] [ebp-4h]
  int jj; // [esp+1Ch] [ebp-4h]

  v7 = 0;
  if ( ((*(_DWORD *)this >> 2) & 1) != 0 )
    return 0;
  *((float *)this + 3) = *((float *)this + 3) + a2;
  if ( ((*(_DWORD *)this >> 4) & 1) != 0 )
    v5 = *((float *)this + 1) * 15.0;
  else
    v5 = *((float *)this + 3) * 15.0;
  *((float *)this + 4) = v5;
  v8 = 0;
  if ( *((float *)this + 4) >= (double)*(int *)(*((_DWORD *)this + 2) + 132) )
  {
    if ( ((*(_DWORD *)this >> 1) & 1) != 0 )
    {
      while ( *((float *)this + 3) >= (double)*(int *)(*((_DWORD *)this + 2) + 132) / 15.0 )
        *((float *)this + 3) = *((float *)this + 3) - (double)*(int *)(*((_DWORD *)this + 2) + 132) / 15.0;
      v8 = 1;
      *((float *)this + 4) = *((float *)this + 3) * 15.0;
    }
    else
    {
      rf_scene_instance_stop_and_drain_particles(this);
    }
  }
  if ( (*(_DWORD *)this & 1) != 0 )
  {
    if ( (void *)unk_1DB4B90 == this )
      unk_1DB4B90 = 0;
    for ( i = 0; i < *(_DWORD *)(*((_DWORD *)this + 2) + 92); ++i )
    {
      if ( *(int *)(*((_DWORD *)this + 7) + 164 * i + 148) > 0 )
      {
        v7 = 1;
        break;
      }
    }
    if ( !v7 )
    {
      *((float *)this + 4) = (float)*(int *)(*((_DWORD *)this + 2) + 132);
      *(_DWORD *)this |= 4u;
      return 0;
    }
    for ( j = 0; j < *(_DWORD *)(*((_DWORD *)this + 2) + 92); ++j )
      rf_particle_instance_update(
        (float *)(*((_DWORD *)this + 7) + 164 * j),
        *((float *)this + 4),
        (float *)a3,
        (float *)a4,
        v8,
        (*(_DWORD *)this & 0x20) != 0);
  }
  else
  {
    for ( k = 0; k < *(_DWORD *)(*((_DWORD *)this + 2) + 84); ++k )
      rf_scene_point_track_update_pool_record(
        *((_DWORD *)this + 6) + 60 * k,
        (int)this,
        *((float *)this + 4),
        (float *)a3,
        (float *)a4);
    for ( m = 0; m < *(_DWORD *)(*((_DWORD *)this + 2) + 76); ++m )
      rf_scene_model_instance_update_geometry_adapter((char *)(*((_DWORD *)this + 5) + 152 * m), *((float *)this + 4));
    for ( n = 0; n < *(_DWORD *)(*((_DWORD *)this + 2) + 92); ++n )
      rf_particle_instance_update(
        (float *)(*((_DWORD *)this + 7) + 164 * n),
        *((float *)this + 4),
        (float *)a3,
        (float *)a4,
        v8,
        (*(_DWORD *)this & 0x20) != 0);
    for ( ii = 0; ii < *(_DWORD *)(*((_DWORD *)this + 2) + 100); ++ii )
      rf_scene_transform_track_state_update_compat(
        (_DWORD *)(*((_DWORD *)this + 8) + 40 * ii),
        *((float *)this + 4),
        (int)a3,
        (int)a4);
    if ( !unk_1DB4B90 || (void *)unk_1DB4B90 == this )
    {
      unk_1DB4B90 = 0;
      if ( *(int *)(*((_DWORD *)this + 2) + 116) > 0 )
      {
        for ( jj = 0; jj < *(_DWORD *)(*((_DWORD *)this + 2) + 116); ++jj )
        {
          if ( rf_scene_transform_range_sample_between_frames(
                 (_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 2) + 112) + 148 * jj),
                 unk_1DB4B94,
                 *((float *)this + 4)) )
          {
            unk_1DB4B90 = this;
            return 1;
          }
        }
      }
    }
  }
  return 1;
}

