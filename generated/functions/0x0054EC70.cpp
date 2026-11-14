// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054EC70 rf_lightmap_rgb_filtered_texel_to_bytes
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Arguments x,y,width,height,outputRGBbytes. Interior x1..width-2,y1..height-2 sums3x3 neighborhood ineach globalfloatplane0x1566B20/0x14A6B20/0x14E6B20 and scales255/9. Othercoordinates average clippedneighborrectangle: lowerbounds max(1,x-1)/max(1,y-1),upperbounds min(width-1,x+1)/min(height-1,y+1); index0rows/columns deliberatelyexcluded there. Converts toints,clamps negatives0,if max>255 scalesallchannels255/max,storesRGB. No dimension/finite/buffer checks. Current pointerreturn misleading: finalcode overwrites AL with greenbyte,so EAX is not reliable outputpointer. Mainupdater calls filteredpath only when bothdimensions>8 and x/y2..dimension-3; edges use unfilteredhelper.
_BYTE *__cdecl rf_lightmap_rgb_filtered_texel_to_bytes(int a1, int a2, int a3, int a4, _BYTE *a5)
{
  int v5; // eax
  _BYTE *result; // eax
  int i; // [esp+14h] [ebp-3Ch]
  float v8; // [esp+18h] [ebp-38h]
  int v9; // [esp+1Ch] [ebp-34h]
  int v10; // [esp+20h] [ebp-30h]
  int v11; // [esp+24h] [ebp-2Ch]
  int j; // [esp+28h] [ebp-28h]
  int v13; // [esp+2Ch] [ebp-24h]
  int v14; // [esp+30h] [ebp-20h]
  int v15; // [esp+34h] [ebp-1Ch]
  float v16; // [esp+38h] [ebp-18h]
  float v17; // [esp+38h] [ebp-18h]
  float v18; // [esp+3Ch] [ebp-14h]
  float v19; // [esp+3Ch] [ebp-14h]
  float v20; // [esp+40h] [ebp-10h]
  float v21; // [esp+40h] [ebp-10h]
  int v22; // [esp+44h] [ebp-Ch]
  int v23; // [esp+48h] [ebp-8h]
  int v24; // [esp+4Ch] [ebp-4h]

  if ( a1 >= 1 && a1 <= a3 - 2 && a2 >= 1 && a2 <= a4 - 2 )
  {
    v5 = a1 + a3 * a2;
    v17 = (flt_1566B1C[v5 - a3]
         + flt_1566B20[v5 - a3]
         + unk_1566B24[v5 - a3]
         + flt_1566B1C[v5]
         + flt_1566B20[v5]
         + unk_1566B24[v5]
         + flt_1566B1C[a3 + v5]
         + flt_1566B20[a3 + v5]
         + unk_1566B24[a3 + v5])
        * (float)28.333334;
    v19 = (flt_14A6B1C[v5 - a3]
         + flt_14A6B20[v5 - a3]
         + unk_14A6B24[v5 - a3]
         + flt_14A6B1C[v5]
         + flt_14A6B20[v5]
         + unk_14A6B24[v5]
         + flt_14A6B1C[a3 + v5]
         + flt_14A6B20[a3 + v5]
         + unk_14A6B24[a3 + v5])
        * (float)28.333334;
    v21 = (flt_14E6B1C[v5 - a3]
         + flt_14E6B20[v5 - a3]
         + flt_14E6B24[v5 - a3]
         + flt_14E6B1C[v5]
         + flt_14E6B20[v5]
         + flt_14E6B24[v5]
         + flt_14E6B1C[a3 + v5]
         + flt_14E6B20[a3 + v5]
         + flt_14E6B24[a3 + v5])
        * (float)28.333334;
  }
  else
  {
    v20 = 0.0;
    v18 = 0.0;
    v16 = 0.0;
    v10 = a2 - 1;
    if ( a2 - 1 < 1 )
      v10 = 1;
    v14 = a2 + 1;
    if ( a2 + 1 > a4 - 1 )
      v14 = a4 - 1;
    v9 = a1 - 1;
    if ( a1 - 1 < 1 )
      v9 = 1;
    v13 = a1 + 1;
    if ( a1 + 1 > a3 - 1 )
      v13 = a3 - 1;
    v11 = a3 * v10;
    for ( i = v10; i <= v14; ++i )
    {
      for ( j = v9; j <= v13; ++j )
      {
        v16 = v16 + flt_1566B20[j + v11];
        v18 = v18 + flt_14A6B20[j + v11];
        v20 = v20 + flt_14E6B20[j + v11];
      }
      v11 += a3;
    }
    v8 = 255.0 / (double)((v13 - v9 + 1) * (v14 - v10 + 1));
    v17 = v16 * v8;
    v19 = v18 * v8;
    v21 = v20 * v8;
  }
  v22 = (int)v17;
  v24 = (int)v19;
  v23 = (int)v21;
  if ( v22 < 0 )
    v22 = 0;
  if ( v24 < 0 )
    v24 = 0;
  if ( v23 < 0 )
    v23 = 0;
  v15 = v22;
  if ( v24 > v22 )
    v15 = v24;
  if ( v23 > v15 )
    v15 = v23;
  if ( v15 > 255 )
  {
    v22 = 255 * v22 / v15;
    v24 = 255 * v24 / v15;
    v23 = 255 * v23 / v15;
  }
  result = a5;
  *a5 = v22;
  LOBYTE(result) = v24;
  a5[1] = v24;
  a5[2] = v23;
  return result;
}

