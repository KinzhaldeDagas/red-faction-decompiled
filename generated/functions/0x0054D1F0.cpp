// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054D1F0 rf_lightmap_shadow_mask_subtract_polygon_scanlines
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Sevenarguments lightmaprecord(unused),polygoncount,8-byteXYvertices,bytemask,width,height,coveragebyte. FindsminimumYvertex,startrow=ceil(minY-0.5). Walks clockwise/counterclockwise edgechains with sharedremainingedgecount; horizontaldenominator0 substituted1. EvaluatesedgeX atrowcenter y+0.5,edgeend=floor(nextY+0.5). Perrow sortsleft/rightX,firstcol=ceil(leftX-0.5),lastcol=floor(rightX-0.5),clipsfirstcol>=0,lastcol<=width,then subtractscoveragebyte from eachinclusivepixelspan. Bytearithmetic wrapsmod256; no saturationorbooleanassignment. Rows clippedto0..height inclusive through min(height+1,edgeend),so helperpermits x==width or y==height ifpolygon reachesboundary. Callerprojector clampscoordinates1..dimension-1,usuallykeepingwritesinterior. No count>=3,masksize or coordinatefiniteguards. Returnloopartifactedgeend,not area/pixelswritten.
// Does not clearinitialmask; callers initializevisibilitycoverage beforehand.
float *__cdecl rf_lightmap_shadow_mask_subtract_polygon_scanlines(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        char a7)
{
  float *result; // eax
  float v8; // [esp+8h] [ebp-ACh]
  float v9; // [esp+Ch] [ebp-A8h]
  float v10; // [esp+10h] [ebp-A4h]
  float value; // [esp+14h] [ebp-A0h]
  float v12; // [esp+18h] [ebp-9Ch]
  _BYTE *v13; // [esp+24h] [ebp-90h]
  float *v14; // [esp+2Ch] [ebp-88h]
  float *v15; // [esp+30h] [ebp-84h]
  int v16; // [esp+34h] [ebp-80h]
  int v17; // [esp+38h] [ebp-7Ch]
  float v18; // [esp+3Ch] [ebp-78h]
  float v19; // [esp+40h] [ebp-74h]
  float v20; // [esp+44h] [ebp-70h]
  float v21; // [esp+48h] [ebp-6Ch]
  float v22; // [esp+4Ch] [ebp-68h]
  float v23; // [esp+50h] [ebp-64h]
  int v24; // [esp+54h] [ebp-60h]
  int v25; // [esp+58h] [ebp-5Ch]
  int v26; // [esp+5Ch] [ebp-58h]
  float v27[2]; // [esp+68h] [ebp-4Ch] BYREF
  int v28; // [esp+70h] [ebp-44h]
  float v29[2]; // [esp+74h] [ebp-40h] BYREF
  float v30[2]; // [esp+7Ch] [ebp-38h] BYREF
  int v31; // [esp+84h] [ebp-30h]
  int v32; // [esp+88h] [ebp-2Ch]
  int v33; // [esp+8Ch] [ebp-28h]
  float v34[2]; // [esp+90h] [ebp-24h] BYREF
  float v35; // [esp+98h] [ebp-1Ch]
  int v36; // [esp+9Ch] [ebp-18h]
  float *v37; // [esp+A0h] [ebp-14h]
  int v38; // [esp+A4h] [ebp-10h]
  int i; // [esp+A8h] [ebp-Ch]
  int j; // [esp+ACh] [ebp-8h]
  int v41; // [esp+B0h] [ebp-4h]

  v32 = 0;
  v38 = a5;
  v35 = *(float *)(a3 + 4);
  v31 = 0;
  for ( i = 1; i < a2; ++i )
  {
    if ( v35 > (double)*(float *)(a3 + 8 * i + 4) )
    {
      v35 = *(float *)(a3 + 8 * i + 4);
      v31 = i;
    }
  }
  v33 = v31;
  v28 = v31;
  v36 = a2;
  v12 = v35 - 0.5;
  j = (int)rf_math_ceil_float(v12);
  v26 = j - 1;
  v41 = j - 1;
  rf_vector2_assign_components(v29, 0.0, 0.0);
  rf_vector2_assign_components(v34, 0.0, 0.0);
  rf_vector2_assign_components(v27, 0.0, 0.0);
  result = rf_vector2_assign_components(v30, 0.0, 0.0);
  while ( v36 > 0 )
  {
    while ( v41 <= j && v36 > 0 )
    {
      --v36;
      i = v28 - 1;
      if ( v28 - 1 < 0 )
        i = a2 - 1;
      value = *(float *)(a3 + 8 * i + 4) + 0.5;
      v41 = (int)rf_floor_float(value);
      v22 = *(float *)(a3 + 8 * i + 4) - *(float *)(a3 + 8 * v28 + 4);
      if ( v22 == 0.0 )
        v22 = 1.0;
      v21 = (double)j + 0.5 - *(float *)(a3 + 8 * v28 + 4);
      v23 = 1.0 / v22;
      v34[0] = (*(float *)(a3 + 8 * i) - *(float *)(a3 + 8 * v28)) * v23;
      v29[0] = v34[0] * v21 + *(float *)(a3 + 8 * v28);
      v28 = i;
    }
    while ( v26 <= j && v36 > 0 )
    {
      --v36;
      i = v33 + 1;
      if ( v33 + 1 >= a2 )
        i = 0;
      v10 = *(float *)(a3 + 8 * i + 4) + 0.5;
      v26 = (int)rf_floor_float(v10);
      v19 = *(float *)(a3 + 8 * i + 4) - *(float *)(a3 + 8 * v33 + 4);
      if ( v19 == 0.0 )
        v19 = 1.0;
      v18 = (double)j + 0.5 - *(float *)(a3 + 8 * v33 + 4);
      v20 = 1.0 / v19;
      v30[0] = (*(float *)(a3 + 8 * i) - *(float *)(a3 + 8 * v33)) * v20;
      v27[0] = v30[0] * v18 + *(float *)(a3 + 8 * v33);
      v33 = i;
    }
    v37 = (float *)rf_int_min_signed(v41, v26);
    v24 = rf_int_max(v32, j);
    v25 = rf_int_min_signed(a6 + 1, (int)v37);
    for ( j = v24; j < v25; ++j )
    {
      if ( v27[0] <= (double)v29[0] )
      {
        v15 = v27;
        v14 = v29;
      }
      else
      {
        v15 = v29;
        v14 = v27;
      }
      v9 = *v15 - 0.5;
      v16 = (int)rf_math_ceil_float(v9);
      v8 = *v14 - 0.5;
      v17 = (int)rf_floor_float(v8);
      if ( v16 < 0 )
        v16 = 0;
      if ( v17 > v38 )
        v17 = v38;
      if ( v16 <= v17 )
      {
        v13 = (_BYTE *)(a4 + v16 + j * a5);
        for ( i = 0; i < v17 - v16 + 1; ++i )
          *v13++ -= a7;
      }
      v29[0] = v29[0] + v34[0];
      v27[0] = v27[0] + v30[0];
    }
    result = v37;
    j = (int)v37;
  }
  return result;
}

