// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605620 rf_jpeg_fdct_float
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jfdctflt.c:jpeg_fdct_float matched): Voidcdecl(floatdata64),in-place2D8x8Arai-Agui-NakajimafloatingforwardDCT. First8contiguousrows(stride8),then8columns(stride8betweenvalues),butterflyeven/odddecomposition. Exactfloatmultipliersobservedapproximately.7071067690849304,.3826834261417389,.5411961078643799,1.306563019752502;intermediatesroundthroughfloatstores. LeavesAANscalingandfactor8forquantizationdivisors(0x602690);no finalnormalization,levelshift,quantization,zigzagreorderorallocationhere. ReturnsincidentalcolumnpointerinmachineEAXbutvoidsourceAPI;prototypecorrectedfrominferredfloat-pointerreturn.
void __cdecl rf_jpeg_fdct_float(float *data)
{
  float v1; // [esp+0h] [ebp-54h]
  float v2; // [esp+0h] [ebp-54h]
  float v3; // [esp+4h] [ebp-50h]
  float v4; // [esp+4h] [ebp-50h]
  float v5; // [esp+8h] [ebp-4Ch]
  float v6; // [esp+8h] [ebp-4Ch]
  float v7; // [esp+Ch] [ebp-48h]
  float v8; // [esp+Ch] [ebp-48h]
  float v9; // [esp+10h] [ebp-44h]
  float v10; // [esp+10h] [ebp-44h]
  float v11; // [esp+14h] [ebp-40h]
  float v12; // [esp+14h] [ebp-40h]
  float v13; // [esp+18h] [ebp-3Ch]
  float v14; // [esp+18h] [ebp-3Ch]
  float v15; // [esp+1Ch] [ebp-38h]
  float v16; // [esp+1Ch] [ebp-38h]
  float v17; // [esp+20h] [ebp-34h]
  float v18; // [esp+20h] [ebp-34h]
  float v19; // [esp+24h] [ebp-30h]
  float v20; // [esp+24h] [ebp-30h]
  float v21; // [esp+28h] [ebp-2Ch]
  float v22; // [esp+28h] [ebp-2Ch]
  float v23; // [esp+2Ch] [ebp-28h]
  float v24; // [esp+2Ch] [ebp-28h]
  int i; // [esp+30h] [ebp-24h]
  int j; // [esp+30h] [ebp-24h]
  float v27; // [esp+34h] [ebp-20h]
  float v28; // [esp+34h] [ebp-20h]
  float v29; // [esp+34h] [ebp-20h]
  float v30; // [esp+34h] [ebp-20h]
  float v31; // [esp+38h] [ebp-1Ch]
  float v32; // [esp+38h] [ebp-1Ch]
  float v33; // [esp+3Ch] [ebp-18h]
  float v34; // [esp+3Ch] [ebp-18h]
  float v35; // [esp+3Ch] [ebp-18h]
  float v36; // [esp+3Ch] [ebp-18h]
  float v37; // [esp+40h] [ebp-14h]
  float v38; // [esp+40h] [ebp-14h]
  float v39; // [esp+40h] [ebp-14h]
  float v40; // [esp+40h] [ebp-14h]
  float v41; // [esp+44h] [ebp-10h]
  float v42; // [esp+44h] [ebp-10h]
  float v43; // [esp+48h] [ebp-Ch]
  float v44; // [esp+48h] [ebp-Ch]
  float v45; // [esp+4Ch] [ebp-8h]
  float v46; // [esp+4Ch] [ebp-8h]
  float *v47; // [esp+50h] [ebp-4h]
  float *v48; // [esp+50h] [ebp-4h]

  v47 = data;
  for ( i = 7; i >= 0; --i )
  {
    v1 = *v47 + v47[7];
    v43 = *v47 - v47[7];
    v11 = v47[1] + v47[6];
    v21 = v47[1] - v47[6];
    v19 = v47[2] + v47[5];
    v13 = v47[2] - v47[5];
    v41 = v47[3] + v47[4];
    v3 = v47[3] - v47[4];
    v33 = v1 + v41;
    v23 = v1 - v41;
    v37 = v11 + v19;
    v27 = v11 - v19;
    *v47 = v33 + v37;
    v47[4] = v33 - v37;
    v5 = (v27 + v23) * 0.7071067690849304;
    v47[2] = v23 + v5;
    v47[6] = v23 - v5;
    v34 = v3 + v13;
    v38 = v13 + v21;
    v28 = v21 + v43;
    v7 = (v34 - v28) * 0.3826834261417389;
    v17 = v34 * 0.5411961078643799 + v7;
    v9 = v28 * 1.306563019752502 + v7;
    v31 = v38 * 0.7071067690849304;
    v15 = v43 + v31;
    v45 = v43 - v31;
    v47[5] = v45 + v17;
    v47[3] = v45 - v17;
    v47[1] = v15 + v9;
    v47[7] = v15 - v9;
    v47 += 8;
  }
  v48 = data;
  for ( j = 7; j >= 0; --j )
  {
    v2 = *v48 + v48[56];
    v44 = *v48 - v48[56];
    v12 = v48[8] + v48[48];
    v22 = v48[8] - v48[48];
    v20 = v48[16] + v48[40];
    v14 = v48[16] - v48[40];
    v42 = v48[24] + v48[32];
    v4 = v48[24] - v48[32];
    v35 = v2 + v42;
    v24 = v2 - v42;
    v39 = v12 + v20;
    v29 = v12 - v20;
    *v48 = v35 + v39;
    v48[32] = v35 - v39;
    v6 = (v29 + v24) * 0.7071067690849304;
    v48[16] = v24 + v6;
    v48[48] = v24 - v6;
    v36 = v4 + v14;
    v40 = v14 + v22;
    v30 = v22 + v44;
    v8 = (v36 - v30) * 0.3826834261417389;
    v18 = v36 * 0.5411961078643799 + v8;
    v10 = v30 * 1.306563019752502 + v8;
    v32 = v40 * 0.7071067690849304;
    v16 = v44 + v32;
    v46 = v44 - v32;
    v48[40] = v46 + v18;
    v48[24] = v46 - v18;
    v48[8] = v16 + v10;
    v48[56] = v16 - v10;
    ++v48;
  }
}

