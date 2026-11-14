// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587720 rf_model_clip_tick_duration_seconds
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] Animation clip duration seconds: table pointer model+0x1D50, clip pointer table+0xF5C+4*index. Null clip returns0. Otherwise signed end_tick-start_tick, signed max(0,difference), convert to double, divide sequentially by160.0 then30.0, round through float local, return in ST(0). No index-range or table-null guard in this body. Preserve sequential arithmetic/float rounding rather than substituting an assumed integer frame count.
double __thiscall rf_model_clip_tick_duration_seconds(_DWORD *this, int a2)
{
  int end_tick; // esi
  int start_tick; // eax

  if ( !*(_DWORD *)(*(this + 1876) + 4 * a2 + 3932) )
    return 0.0;
  end_tick = rf_rfa_get_end_tick(*(void **)(*(this + 1876) + 4 * a2 + 3932));
  start_tick = rf_rfa_get_start_tick(*(void **)(*(this + 1876) + 4 * a2 + 3932));
  return (float)((double)rf_int_max(0, end_tick - start_tick) / 160.0 / 30.0);
}

