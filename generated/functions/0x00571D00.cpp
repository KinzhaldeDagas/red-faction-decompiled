// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571D00 rf_graphics_gamma_set
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): cdecl(float gamma). Clamps ordinary finite input through rf_float_clamp_in_place to float0.7..float2.2,stores gamma663F08 and signed trunc(gamma*100)663F0C. At exact minimum float0.699999988079071,the cache is69 (not70):FMUL100 flows directly to truncation without intermediate float rounding. Fori0..255:stores float x=i/255 and float y=1/gamma,uses verified x87 pow573D50,converts pow(x,y)*255 to signed int by truncation,clamps integer0..255,and writes primary DWORD LUT182A380[i]. Separately stores float(i) into linear FLOAT LUT182A790[i];redundant range tests do not change ordinary loop values. Recomputes every call even samegamma. Backend102 calls5C57D0 to build/apply ramp;otherwise returns backend selector. EAX backend result is
// incidental,not a gamma percent or normalized success. No own finite/device/readiness validation. Initial PE gamma-1 is a pre-init sentinel;570A00 explicitly applies1.0 after backend initialization.
int __cdecl rf_graphics_gamma_set(float a1)
{
  int result; // eax
  float X; // [esp+Ch] [ebp-14h]
  float Y; // [esp+10h] [ebp-10h]
  float v4; // [esp+14h] [ebp-Ch]
  int v5; // [esp+18h] [ebp-8h]
  int i; // [esp+1Ch] [ebp-4h]
  int j; // [esp+1Ch] [ebp-4h]

  rf_float_clamp_in_place(&a1, 0.69999999, 2.2);
  rf_graphics_gamma = a1;
  rf_graphics_gamma_percent = (int)(a1 * 100.0);
  for ( i = 0; i < 256; ++i )
  {
    Y = 1.0 / rf_graphics_gamma;
    X = (double)i / 255.0;
    v5 = (int)(rf_pow_float_forward(X, Y) * 255.0);
    if ( v5 <= 255 )
    {
      if ( v5 < 0 )
        v5 = 0;
    }
    else
    {
      v5 = 255;
    }
    rf_graphics_gamma_lut_u32[i] = v5;
  }
  for ( j = 0; j < 256; ++j )
  {
    v4 = (float)j;
    if ( v4 <= 255.0 )
    {
      if ( v4 < 0.0 )
        v4 = 0.0;
    }
    else
    {
      v4 = 255.0;
    }
    unk_182A790[j] = v4;
  }
  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_gamma_ramp_apply();
  return result;
}

