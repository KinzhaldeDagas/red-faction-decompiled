// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA560 rf_rfa_track_weight_at_time
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Gets raw buffer; track offset=DWORD at raw+80+4*trackIndex, raw-relative; weight=float at track+0. Weight<~1e-5 returns0 (including negative values); nonzero bypass-ramp byte returns raw weight. Otherwise relative tick=tick-header.start(+16),duration=end(+20)-start,rampIn=header+36,rampOut=header+40. Negative relative tick=>0; before rampIn=>relative/rampIn*weight; after duration=>0; after duration-rampOut=>remaining/rampOut*weight; otherwise weight. Result is capped above by raw weight, with no independent lower clamp or malformed-duration/window/NaN guard. Tick comparisons signed; no track bounds or raw-buffer validation.
double __thiscall rf_rfa_track_weight_at_time(void *this, int a2, int a3, char a4)
{
  int v5; // [esp+8h] [ebp-1Ch]
  unsigned __int8 *raw_buffer; // [esp+Ch] [ebp-18h]
  float v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+18h] [ebp-Ch]
  float v10; // [esp+20h] [ebp-4h]
  int v11; // [esp+30h] [ebp+Ch]

  raw_buffer = rf_rfa_get_or_load_raw_buffer(this);
  v7 = *(float *)&raw_buffer[*(_DWORD *)&raw_buffer[4 * a2 + 80]];
  if ( v7 < 0.000009999999747378752 )
    return 0.0;
  if ( a4 )
    return v7;
  v11 = a3 - *((_DWORD *)raw_buffer + 4);
  v5 = *((_DWORD *)raw_buffer + 5) - *((_DWORD *)raw_buffer + 4);
  v9 = *((_DWORD *)raw_buffer + 9);
  v8 = *((_DWORD *)raw_buffer + 10);
  if ( v11 >= 0 )
  {
    if ( v11 >= v9 )
    {
      if ( v11 <= v5 )
      {
        if ( v11 <= v5 - v8 )
          v10 = v7;
        else
          v10 = (double)(v5 - v11) / (double)v8 * v7;
      }
      else
      {
        v10 = 0.0;
      }
    }
    else
    {
      v10 = (double)v11 / (double)v9 * v7;
    }
  }
  else
  {
    v10 = 0.0;
  }
  if ( v7 >= (double)v10 )
    return v10;
  else
    return v7;
}

