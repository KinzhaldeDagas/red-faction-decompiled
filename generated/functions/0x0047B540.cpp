// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047B540 rf_rfl_light_update_changing
// VERIFIED: Changing-light update for modes other than 1/2 while enabled. Accumulates frame delta; at most one expired dwell transition is processed per update, so overshoot is discarded rather than carried across states. Optional profile interpolation updates RGB between the two multipliers.
// UNREALRED VERIFIED [rfl-light-decode]: Updates changing modes 3 and 4 with decoded dwell/interpolation behavior, discarding overshoot and toggling at most once per frame.
void __thiscall rf_rfl_light_update_changing(int this, float a2)
{
  double v2; // st7
  double v3; // [esp+10h] [ebp-28h]
  double v4; // [esp+18h] [ebp-20h]
  double v5; // [esp+20h] [ebp-18h]
  double v6; // [esp+28h] [ebp-10h]
  float v8; // [esp+34h] [ebp-4h]

  if ( *(_DWORD *)(this + 60) != 2 && *(_DWORD *)(this + 60) != 1 && *(_BYTE *)(this + 145) )
  {
    *(float *)(this + 140) = *(float *)(this + 140) + a2;
    if ( *(float *)(this + 136) <= (double)*(float *)(this + 140) )
    {
      *(float *)(this + 140) = 0.0;
      *(_BYTE *)(this + 144) = *(_BYTE *)(this + 144) == 0;
      if ( *(_BYTE *)(this + 144) )
      {
        v6 = *(float *)(this + 116) - *(float *)(this + 120);
        v5 = *(float *)(this + 120) * 2.0;
        *(float *)(this + 136) = sub_567730() * v5 + v6;
        rf_renderer_light_recompute_scaled_rgb(
          *(_DWORD *)(this + 148),
          *(float *)(this + 108),
          *(float *)(this + 68),
          *(float *)(this + 72),
          *(float *)(this + 76));
      }
      else
      {
        v4 = *(float *)(this + 124) - *(float *)(this + 128);
        v3 = *(float *)(this + 128) * 2.0;
        *(float *)(this + 136) = sub_567730() * v3 + v4;
        rf_renderer_light_recompute_scaled_rgb(
          *(_DWORD *)(this + 148),
          *(float *)(this + 112),
          *(float *)(this + 68),
          *(float *)(this + 72),
          *(float *)(this + 76));
      }
      if ( *(float *)(this + 136) < 0.1000000014901161 )
        *(float *)(this + 136) = 0.1;
    }
    else if ( *(_BYTE *)(this + 135) )
    {
      if ( *(_BYTE *)(this + 144) )
        v2 = *(float *)(this + 108)
           - (*(float *)(this + 108) - *(float *)(this + 112)) * *(float *)(this + 140) / *(float *)(this + 136);
      else
        v2 = (*(float *)(this + 108) - *(float *)(this + 112)) * *(float *)(this + 140) / *(float *)(this + 136)
           + *(float *)(this + 112);
      v8 = v2;
      rf_renderer_light_recompute_scaled_rgb(
        *(_DWORD *)(this + 148),
        v8,
        *(float *)(this + 68),
        *(float *)(this + 72),
        *(float *)(this + 76));
    }
  }
}

