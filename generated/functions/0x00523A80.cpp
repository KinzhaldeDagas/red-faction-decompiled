// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00523A80 rf_decal_uv_shift_selected_axis_to_minimum_tile
// UNREALRED VERIFIED [decal-face-links-20261028]: Input interleaved vec2 array,count,mode. Mode0 does nothing; mode==0x40 examines U, any other nonzero mode examines V (including0xC0, which does NOT shift both axes). If any selected component strictly<0 or>1, finds minimum and subtracts floor(minimum) from that component across all vertices. Integral common translation only: does not clamp, individually wrap or compress span, so values may remain outside0..1. Exactly1 allowed. No count/storage guards; return register branch-dependent, not status.
int __cdecl rf_decal_uv_shift_selected_axis_to_minimum_tile(int a1, int a2, int a3)
{
  int result; // eax
  int v4; // [esp+4h] [ebp-1Ch]
  unsigned __int8 v5; // [esp+Bh] [ebp-15h]
  int v6; // [esp+Ch] [ebp-14h]
  float value; // [esp+10h] [ebp-10h]
  unsigned __int8 v8; // [esp+17h] [ebp-9h]
  int i; // [esp+18h] [ebp-8h]
  int j; // [esp+18h] [ebp-8h]
  float v11; // [esp+1Ch] [ebp-4h]

  value = 3.4028235e38;
  v11 = 3.4028235e38;
  v8 = 0;
  v5 = 0;
  if ( a3 )
  {
    for ( i = 0; i < a2; ++i )
    {
      if ( a3 == 64 )
      {
        if ( *(float *)(a1 + 8 * i) < 0.0 || *(float *)(a1 + 8 * i) > 1.0 )
          v8 = 1;
        if ( value > (double)*(float *)(a1 + 8 * i) )
          value = *(float *)(a1 + 8 * i);
      }
      else
      {
        if ( *(float *)(a1 + 8 * i + 4) < 0.0 || *(float *)(a1 + 8 * i + 4) > 1.0 )
          v5 = 1;
        if ( v11 > (double)*(float *)(a1 + 8 * i + 4) )
          v11 = *(float *)(a1 + 8 * i + 4);
      }
    }
    result = v8;
    if ( v8 || v5 )
    {
      v4 = 0;
      v6 = 0;
      if ( v8 )
        v4 = (int)rf_floor_float(value);
      result = v5;
      if ( v5 )
      {
        result = (int)rf_floor_float(v11);
        v6 = result;
      }
      for ( j = 0; j < a2; ++j )
      {
        result = v8;
        if ( v8 )
        {
          result = j;
          *(float *)(a1 + 8 * j) = *(float *)(a1 + 8 * j) - (double)v4;
        }
        if ( v5 )
        {
          result = a1;
          *(float *)(a1 + 8 * j + 4) = *(float *)(a1 + 8 * j + 4) - (double)v6;
        }
      }
    }
  }
  return result;
}

