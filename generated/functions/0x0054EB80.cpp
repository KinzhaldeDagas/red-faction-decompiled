// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054EB80 rf_lightmap_rgb_float_texel_to_bytes
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Arguments lineartexelindex,outputRGBbytepointer. Reads globalfloatplanes R0x1566B20,G0x14A6B20,B0x14E6B20,converts eachvalue*255 toint,clamps negatives0. If maximumchannel>255,scales ALLthree integerchannels by255/max using integerdivision,retaining colorratios ratherthan independentlyclamping. WritesRGBbytes,returns outputpointer. No index,finite or overflowvalidation.
_BYTE *__cdecl rf_lightmap_rgb_float_texel_to_bytes(int a1, _BYTE *a2)
{
  int v3; // [esp+0h] [ebp-10h]
  int v4; // [esp+4h] [ebp-Ch]
  int v5; // [esp+8h] [ebp-8h]
  int v6; // [esp+Ch] [ebp-4h]

  v4 = (int)(flt_1566B20[a1] * 255.0);
  v5 = (int)(flt_14A6B20[a1] * 255.0);
  v6 = (int)(flt_14E6B20[a1] * 255.0);
  if ( v4 < 0 )
    v4 = 0;
  if ( v5 < 0 )
    v5 = 0;
  if ( v6 < 0 )
    v6 = 0;
  v3 = v4;
  if ( v5 > v4 )
    v3 = v5;
  if ( v6 > v3 )
    v3 = v6;
  if ( v3 > 255 )
  {
    v4 = 255 * v4 / v3;
    v5 = 255 * v5 / v3;
    v6 = 255 * v6 / v3;
  }
  *a2 = v4;
  a2[1] = v5;
  a2[2] = v6;
  return a2;
}

