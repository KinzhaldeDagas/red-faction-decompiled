// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005389B0 rf_lightmap_blend_tile_seam_along_segment
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Cdecl tilePointerA*,tilePointerB*,worldEndpointA*,unusedDWORD,worldEndpointB*. Dereferences tile pointers and endpoint pointers;copies endpoints locally. Allocates FOUR separate dynamic stack buffers:RGB snapshots3*wA*hA,3*wB*hB,and zeroed visited byteswA*hA,wB*hB. Original __alloca_probe_16/ESP saves prove buffers distinct despite decompiler showing reused &local addresses. Copies both tile rectangles from tightly packed RGB24 pages before writes. Maps endpoints through clampedUV helper,scales by PAGE dimensions. Steps N=20*max(1,abs(trunc(dxA)),abs(trunc(dxB)),abs(trunc(dyA)),abs(trunc(dyB))) along world segment with inclusive samples0..N. Per sample maps current point again,scales page
// dimensions,adds0.5,truncates,subtracts tile origin,then lower-clamps to1 and upper-clamps to tileDimension-2 IN THAT ORDER. Requires sensible dimensions>=3 for intended interior bounds;no validation,small/negative dimensions can produce invalid offsets. Reads colors from ORIGINAL snapshots. First visit to A texel writes floor((9*A+7*B)/16);first visit to B writes floor((7*A+9*B)/16),per-channel independently. Later visits do not rewrite already-marked destination texel,so correspondence/path order matters;not an iterative blur or simple mean. Returns N+1 ordinary loop-exit count,not byte count/status. Does not update/upload bitmap or mark descriptor flags. Fourth argument unused;32-bit size/step overflow,large stack allocation,point/tile/NULL cases unchecked.
int __cdecl rf_lightmap_blend_tile_seam_along_segment(_DWORD **a1, _DWORD **a2, float **a3, int a4, float **a5)
{
  void *v5; // esp
  void *v6; // esp
  void *v7; // esp
  void *v8; // esp
  __int64 v9; // rax
  __int64 v10; // rax
  __int64 v11; // rax
  int result; // eax
  int v13; // [esp+0h] [ebp-104h] BYREF
  int v14; // [esp+4h] [ebp-100h]
  int v15; // [esp+8h] [ebp-FCh]
  signed int v16; // [esp+Ch] [ebp-F8h]
  signed int v17; // [esp+10h] [ebp-F4h]
  int *v18; // [esp+14h] [ebp-F0h]
  int *v19; // [esp+18h] [ebp-ECh]
  int *v20; // [esp+1Ch] [ebp-E8h]
  int *v21; // [esp+20h] [ebp-E4h]
  int v22; // [esp+28h] [ebp-DCh]
  int v23; // [esp+2Ch] [ebp-D8h]
  int v24; // [esp+30h] [ebp-D4h]
  int v25; // [esp+34h] [ebp-D0h]
  int v26; // [esp+38h] [ebp-CCh]
  int v27; // [esp+3Ch] [ebp-C8h]
  int v28; // [esp+40h] [ebp-C4h]
  int v29; // [esp+44h] [ebp-C0h]
  int v30; // [esp+48h] [ebp-BCh]
  int v31; // [esp+4Ch] [ebp-B8h]
  int v32; // [esp+50h] [ebp-B4h]
  int v33; // [esp+54h] [ebp-B0h]
  int v34; // [esp+58h] [ebp-ACh]
  float v35; // [esp+5Ch] [ebp-A8h] BYREF
  float v36; // [esp+60h] [ebp-A4h] BYREF
  int v37; // [esp+64h] [ebp-A0h]
  float v38; // [esp+68h] [ebp-9Ch] BYREF
  float v39; // [esp+6Ch] [ebp-98h] BYREF
  int v40; // [esp+70h] [ebp-94h]
  int v41; // [esp+74h] [ebp-90h]
  int v42; // [esp+78h] [ebp-8Ch]
  int v43; // [esp+7Ch] [ebp-88h]
  int v44; // [esp+80h] [ebp-84h]
  int v45; // [esp+84h] [ebp-80h]
  int j; // [esp+88h] [ebp-7Ch]
  size_t Size; // [esp+8Ch] [ebp-78h]
  float v48; // [esp+90h] [ebp-74h] BYREF
  float v49; // [esp+94h] [ebp-70h] BYREF
  float v50; // [esp+98h] [ebp-6Ch]
  float v51; // [esp+9Ch] [ebp-68h]
  _DWORD *v52; // [esp+A0h] [ebp-64h]
  _DWORD *v53; // [esp+A4h] [ebp-60h]
  size_t v54; // [esp+A8h] [ebp-5Ch]
  int v55; // [esp+ACh] [ebp-58h]
  float v56; // [esp+B0h] [ebp-54h]
  float v57; // [esp+B4h] [ebp-50h] BYREF
  float v58; // [esp+B8h] [ebp-4Ch] BYREF
  int *v59; // [esp+BCh] [ebp-48h]
  float v60[3]; // [esp+C0h] [ebp-44h] BYREF
  float v61; // [esp+CCh] [ebp-38h] BYREF
  float v62; // [esp+D0h] [ebp-34h] BYREF
  _DWORD *v63; // [esp+D4h] [ebp-30h]
  float v64; // [esp+D8h] [ebp-2Ch] BYREF
  float v65; // [esp+DCh] [ebp-28h] BYREF
  int v66; // [esp+E0h] [ebp-24h]
  _DWORD *v67; // [esp+E4h] [ebp-20h]
  int *v68; // [esp+E8h] [ebp-1Ch]
  int i; // [esp+ECh] [ebp-18h]
  void *v70; // [esp+F0h] [ebp-14h]
  void *v71; // [esp+F4h] [ebp-10h]
  float v72; // [esp+F8h] [ebp-Ch] BYREF
  float v73; // [esp+FCh] [ebp-8h]
  float v74; // [esp+100h] [ebp-4h]

  v52 = *a1;
  v63 = *a2;
  v53 = (_DWORD *)v52[3];
  v67 = (_DWORD *)v63[3];
  Size = v52[7] * v52[6];
  v54 = v63[7] * v63[6];
  v5 = alloca(3 * Size);
  v21 = &v13;
  v68 = &v13;
  v6 = alloca(3 * v54);
  v20 = &v13;
  v59 = &v13;
  v7 = alloca(Size);
  v19 = &v13;
  v70 = &v13;
  v8 = alloca(v54);
  v18 = &v13;
  v71 = &v13;
  memset(&v13, 0, Size);
  memset(v71, 0, v54);
  v55 = 3 * v52[4] + 3 * v53[1] * v52[5];
  for ( i = 0; i < v52[7]; ++i )
  {
    memcpy((char *)v68 + 3 * v52[6] * i, (const void *)(v55 + v53[3]), 3 * v52[6]);
    v55 += 3 * v53[1];
  }
  v55 = 3 * v63[4] + 3 * v67[1] * v63[5];
  for ( i = 0; i < v63[7]; ++i )
  {
    memcpy((char *)v59 + 3 * v63[6] * i, (const void *)(v55 + v67[3]), 3 * v63[6]);
    v55 += 3 * v67[1];
  }
  rf_vector3_copy_return_destination(&v72, *a3);
  rf_vector3_copy_return_destination(v60, *a5);
  rf_vector3_default_construct_noop(&v57);
  rf_vector3_default_construct_noop(&v64);
  rf_vector3_default_construct_noop(&v48);
  rf_vector3_default_construct_noop(&v61);
  rf_lightmap_point_to_clamped_uv((int)v52, (char *)&v72, &v57, &v58);
  rf_lightmap_point_to_clamped_uv((int)v52, (char *)v60, &v48, &v49);
  rf_lightmap_point_to_clamped_uv((int)v63, (char *)&v72, &v64, &v65);
  rf_lightmap_point_to_clamped_uv((int)v63, (char *)v60, &v61, &v62);
  v57 = (double)(int)v53[1] * v57;
  v58 = (double)(int)v53[2] * v58;
  v64 = (double)(int)v67[1] * v64;
  v65 = (double)(int)v67[2] * v65;
  v48 = (double)(int)v53[1] * v48;
  v49 = (double)(int)v53[2] * v49;
  v61 = (double)(int)v67[1] * v61;
  v62 = (double)(int)v67[2] * v62;
  if ( (int)abs32((int)(v48 - v57)) <= (int)abs32((int)(v61 - v64)) )
    v9 = (int)(v61 - v64);
  else
    v9 = (int)(v48 - v57);
  v17 = (((int)v9 >> 31) ^ v9) - HIDWORD(v9);
  v66 = v17;
  if ( v17 <= (int)abs32((int)(v49 - v58)) )
  {
    v10 = (int)(v49 - v58);
    v16 = (((int)v10 >> 31) ^ v10) - HIDWORD(v10);
  }
  else
  {
    v16 = v66;
  }
  v66 = v16;
  if ( v16 <= (int)abs32((int)(v62 - v65)) )
  {
    v11 = (int)(v62 - v65);
    v15 = (((int)v11 >> 31) ^ v11) - HIDWORD(v11);
  }
  else
  {
    v15 = v66;
  }
  v66 = v15;
  if ( v15 >= 1 )
    v14 = v66;
  else
    v14 = 1;
  v66 = 20 * v14;
  v50 = (v60[0] - v72) / (double)(20 * v14);
  v51 = (v60[1] - v73) / (double)(20 * v14);
  v56 = (v60[2] - v74) / (double)(20 * v14);
  for ( j = 0; ; ++j )
  {
    result = j;
    if ( j > v66 )
      break;
    rf_vector3_default_construct_noop(&v35);
    rf_vector3_default_construct_noop(&v38);
    rf_lightmap_point_to_clamped_uv((int)v52, (char *)&v72, &v35, &v36);
    rf_lightmap_point_to_clamped_uv((int)v63, (char *)&v72, &v38, &v39);
    v35 = (double)(int)v53[1] * v35;
    v36 = (double)(int)v53[2] * v36;
    v38 = (double)(int)v67[1] * v38;
    v39 = (double)(int)v67[2] * v39;
    v35 = v35 + 0.5;
    v36 = v36 + 0.5;
    v38 = v38 + 0.5;
    v39 = v39 + 0.5;
    v32 = (int)v35 - v52[4];
    v41 = (int)v36 - v52[5];
    v43 = (int)v38 - v63[4];
    v44 = (int)v39 - v63[5];
    if ( v32 < 1 )
      v32 = 1;
    if ( v43 < 1 )
      v43 = 1;
    if ( v32 > v52[6] - 2 )
      v32 = v52[6] - 2;
    if ( v43 > v63[6] - 2 )
      v43 = v63[6] - 2;
    if ( v41 < 1 )
      v41 = 1;
    if ( v44 < 1 )
      v44 = 1;
    if ( v41 > v52[7] - 2 )
      v41 = v52[7] - 2;
    if ( v44 > v63[7] - 2 )
      v44 = v63[7] - 2;
    v33 = 3 * (v32 + v52[6] * v41);
    v31 = 3 * (v43 + v63[6] * v44);
    v42 = *((unsigned __int8 *)v68 + v33);
    v34 = *((unsigned __int8 *)v68 + v33 + 1);
    v30 = *((unsigned __int8 *)v68 + v33 + 2);
    v37 = *((unsigned __int8 *)v59 + v31);
    v45 = *((unsigned __int8 *)v59 + v31 + 1);
    v40 = *((unsigned __int8 *)v59 + v31 + 2);
    if ( !*((_BYTE *)v70 + v33 / 3) )
    {
      v26 = (7 * v37 + 9 * v42) >> 4;
      v28 = (7 * v45 + 9 * v34) >> 4;
      v29 = (7 * v40 + 9 * v30) >> 4;
      v27 = 3 * (v52[4] + v32 + v53[1] * (v52[5] + v41));
      *(_BYTE *)(v53[3] + v27) = v26;
      *(_BYTE *)(v27 + v53[3] + 1) = v28;
      *(_BYTE *)(v27 + v53[3] + 2) = v29;
      *((_BYTE *)v70 + v33 / 3) = 1;
    }
    if ( !*((_BYTE *)v71 + v31 / 3) )
    {
      v22 = (7 * v42 + 9 * v37) >> 4;
      v24 = (7 * v34 + 9 * v45) >> 4;
      v25 = (7 * v30 + 9 * v40) >> 4;
      v23 = 3 * (v63[4] + v43 + v67[1] * (v63[5] + v44));
      *(_BYTE *)(v67[3] + v23) = v22;
      *(_BYTE *)(v23 + v67[3] + 1) = v24;
      *(_BYTE *)(v23 + v67[3] + 2) = v25;
      *((_BYTE *)v71 + v31 / 3) = 1;
    }
    v72 = v72 + v50;
    v73 = v73 + v51;
    v74 = v74 + v56;
  }
  return result;
}

