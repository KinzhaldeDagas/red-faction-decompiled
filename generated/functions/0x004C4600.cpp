// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C4600 rf_geomod_impact_chunk_render_or_expire
// UNREALRED VERIFIED [room-render-20261028]: If elapsed float+112<=duration+116+1, advances elapsed by frame delta only when not paused. Alpha255 until elapsed>duration,then trunc((1-(elapsed-duration))*255),clamped0..255. Calls renderer0x5803D0(chunk,alpha). Entry with elapsed>duration+1 invokes0x4C39E0 deletion instead. Boundary checked BEFORE increment,so one frame can draw clampedalpha0 after overshoot. No elapsed clamp or return status.
void __cdecl rf_geomod_impact_chunk_render_or_expire(int a1)
{
  int v1; // ecx
  int v2; // [esp+0h] [ebp-4h] BYREF

  v2 = v1;
  if ( *(float *)(a1 + 112) <= *(float *)(a1 + 116) + 1.0 )
  {
    if ( !rf_game_pause_gate_query() )
      *(float *)(a1 + 112) = *(float *)(a1 + 112) + rf_frame_delta_seconds;
    v2 = 255;
    if ( *(float *)(a1 + 116) < (double)*(float *)(a1 + 112) )
    {
      v2 = (int)((1.0 - (*(float *)(a1 + 112) - *(float *)(a1 + 116))) * 255.0);
      rf_integer_clamp_in_place(&v2, 0, 255);
    }
    rf_renderer_draw_impact_chunk_backend_dispatch(a1, v2);
  }
  else
  {
    rf_geomod_impact_chunk_recycle((_DWORD **)a1);
  }
}

