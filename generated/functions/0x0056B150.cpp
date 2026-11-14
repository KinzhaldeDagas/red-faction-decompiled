// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056B150 rf_obb_separation_axis_code_stride4_retail
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(rotationStride4,translation3,halfA3,halfB3),returns32bit axis code. R[i,j]=input[4*i+j] for i,j0..2,unused fourth entries ignored; Q=abs(R)+float1e-6. Tests 15 separating-axis bounds in order A0,B0,A1,A2,B1,B2,A0xB0,A0xB1,A0xB2,A1xB0,A1xB1,A1xB2,A2xB0,A2xB1,A2xB2. Returns first failed stage1..15,or0 if every ordered <= comparison passes (unordered fails its stage); not a boolean overlap result. Uses float-stored abs/projection intermediates. Preserve THREE retail extent coefficients:stage3 |ty|<=halfB.z*Q10+halfA.y+halfB.y*Q11+halfB.z*Q12;stage5 |t dot Rcolumn1|<=halfA.z*Q01+halfB.y+halfA.y*Q11+halfA.z*Q21;stage8 |tz*R11-ty*R21|<=halfA.y*Q21+halfA.z*Q11+halfB.z*Q02+halfB.z*Q00. These repeatZ terms where textbook
// SAT usesX; verified raw loads at56B355,56B449,56B615. Other stages follow the listed SAT axes with padded rotation indexing. Assumes caller-provided relative rotation/translation and nonnegative extents; no matrix orthogonality,finite,extent or pointer validation. All scratch local; executable unmodified.
int __cdecl rf_obb_separation_axis_code_stride4_retail(
        const float *rotation_stride4,
        const float *translation,
        const float *half_a,
        const float *half_b)
{
  float v5; // [esp+4h] [ebp-CCh]
  float v6; // [esp+Ch] [ebp-C4h]
  float v7; // [esp+14h] [ebp-BCh]
  float v8; // [esp+1Ch] [ebp-B4h]
  float v9; // [esp+24h] [ebp-ACh]
  float v10; // [esp+2Ch] [ebp-A4h]
  float v11; // [esp+34h] [ebp-9Ch]
  float v12; // [esp+3Ch] [ebp-94h]
  float v13; // [esp+44h] [ebp-8Ch]
  float v14; // [esp+4Ch] [ebp-84h]
  float v15; // [esp+54h] [ebp-7Ch]
  float v16; // [esp+5Ch] [ebp-74h]
  float v17; // [esp+64h] [ebp-6Ch]
  float v18; // [esp+6Ch] [ebp-64h]
  float v19; // [esp+74h] [ebp-5Ch]
  float v20; // [esp+78h] [ebp-58h]
  float v21; // [esp+7Ch] [ebp-54h]
  float v22; // [esp+80h] [ebp-50h]
  float v23; // [esp+84h] [ebp-4Ch]
  float v24; // [esp+88h] [ebp-48h]
  float v25; // [esp+8Ch] [ebp-44h]
  float v26; // [esp+90h] [ebp-40h]
  float v27; // [esp+94h] [ebp-3Ch]
  float v28; // [esp+98h] [ebp-38h]
  bool v29; // [esp+A0h] [ebp-30h]
  int v30; // [esp+A0h] [ebp-30h]
  int v31; // [esp+A0h] [ebp-30h]
  int v32; // [esp+A0h] [ebp-30h]
  int v33; // [esp+A0h] [ebp-30h]
  int v34; // [esp+A0h] [ebp-30h]
  int v35; // [esp+A0h] [ebp-30h]
  int v36; // [esp+A0h] [ebp-30h]
  int v37; // [esp+A0h] [ebp-30h]
  int v38; // [esp+A0h] [ebp-30h]
  float v39; // [esp+A4h] [ebp-2Ch]
  float v40; // [esp+A8h] [ebp-28h]
  float v41; // [esp+ACh] [ebp-24h]
  float v42; // [esp+B0h] [ebp-20h]
  float v43; // [esp+B4h] [ebp-1Ch]
  float v44; // [esp+B8h] [ebp-18h]
  float v45; // [esp+BCh] [ebp-14h]
  float v46; // [esp+C0h] [ebp-10h]
  float v47; // [esp+C4h] [ebp-Ch]
  float v48; // [esp+CCh] [ebp-4h]
  float v49; // [esp+CCh] [ebp-4h]
  float v50; // [esp+CCh] [ebp-4h]
  float v51; // [esp+CCh] [ebp-4h]
  float v52; // [esp+CCh] [ebp-4h]
  float v53; // [esp+CCh] [ebp-4h]
  float v54; // [esp+CCh] [ebp-4h]
  float v55; // [esp+CCh] [ebp-4h]
  float v56; // [esp+CCh] [ebp-4h]
  float v57; // [esp+CCh] [ebp-4h]
  float v58; // [esp+CCh] [ebp-4h]
  float v59; // [esp+CCh] [ebp-4h]

  v28 = fabs(*rotation_stride4);
  v39 = v28 + (float)0.000001;
  v27 = fabs(rotation_stride4[1]);
  v40 = v27 + (float)0.000001;
  v26 = fabs(rotation_stride4[2]);
  v41 = v26 + (float)0.000001;
  v25 = fabs(rotation_stride4[4]);
  v42 = v25 + (float)0.000001;
  v24 = fabs(rotation_stride4[5]);
  v43 = v24 + (float)0.000001;
  v23 = fabs(rotation_stride4[6]);
  v44 = v23 + (float)0.000001;
  v22 = fabs(rotation_stride4[8]);
  v45 = v22 + (float)0.000001;
  v21 = fabs(rotation_stride4[9]);
  v46 = v21 + (float)0.000001;
  v20 = fabs(rotation_stride4[10]);
  v47 = v20 + (float)0.000001;
  v19 = fabs(*translation);
  if ( v19 > *half_b * v39 + *half_a + half_b[1] * v40 + half_b[2] * v41 )
    return 1;
  v48 = *translation * *rotation_stride4 + translation[1] * rotation_stride4[4] + translation[2] * rotation_stride4[8];
  v18 = fabs(v48);
  if ( v18 > *half_a * v39 + *half_b + half_a[1] * v42 + half_a[2] * v45
    || v19 > *half_b * v39 + *half_a + half_b[1] * v40 + half_b[2] * v41 )
  {
    return 2;
  }
  v17 = fabs(translation[1]);
  if ( v17 > half_b[2] * v42 + half_a[1] + half_b[1] * v43 + half_b[2] * v44
    || v18 > *half_a * v39 + *half_b + half_a[1] * v42 + half_a[2] * v45
    || v19 > *half_b * v39 + *half_a + half_b[1] * v40 + half_b[2] * v41 )
  {
    return 3;
  }
  v16 = fabs(translation[2]);
  if ( v16 > *half_b * v45 + half_a[2] + half_b[1] * v46 + half_b[2] * v47
    || v17 > half_b[2] * v42 + half_a[1] + half_b[1] * v43 + half_b[2] * v44
    || v18 > *half_a * v39 + *half_b + half_a[1] * v42 + half_a[2] * v45
    || v19 > *half_b * v39 + *half_a + half_b[1] * v40 + half_b[2] * v41 )
  {
    return 4;
  }
  v49 = *translation * rotation_stride4[1] + translation[1] * rotation_stride4[5] + translation[2] * rotation_stride4[9];
  v15 = fabs(v49);
  if ( v15 > half_a[2] * v40 + half_b[1] + half_a[1] * v43 + half_a[2] * v46
    || v16 > *half_b * v45 + half_a[2] + half_b[1] * v46 + half_b[2] * v47
    || v17 > half_b[2] * v42 + half_a[1] + half_b[1] * v43 + half_b[2] * v44
    || v18 > *half_a * v39 + *half_b + half_a[1] * v42 + half_a[2] * v45
    || v19 > *half_b * v39 + *half_a + half_b[1] * v40 + half_b[2] * v41 )
  {
    return 5;
  }
  v50 = *translation * rotation_stride4[2]
      + translation[1] * rotation_stride4[6]
      + translation[2] * rotation_stride4[10];
  v14 = fabs(v50);
  v29 = v15 <= half_a[2] * v40 + half_b[1] + half_a[1] * v43 + half_a[2] * v46
     && v16 <= *half_b * v45 + half_a[2] + half_b[1] * v46 + half_b[2] * v47
     && v17 <= half_b[2] * v42 + half_a[1] + half_b[1] * v43 + half_b[2] * v44
     && v18 <= *half_a * v39 + *half_b + half_a[1] * v42 + half_a[2] * v45
     && v19 <= *half_b * v39 + *half_a + half_b[1] * v40 + half_b[2] * v41;
  v30 = v14 <= *half_a * v41 + half_b[2] + half_a[1] * v44 + half_a[2] * v47 && v29;
  if ( !v30 )
    return 6;
  v51 = translation[2] * rotation_stride4[4] - translation[1] * rotation_stride4[8];
  v13 = fabs(v51);
  v31 = (v13 <= half_a[1] * v45 + half_a[2] * v42 + half_b[1] * v41 + half_b[2] * v40) & (unsigned __int8)v30;
  if ( !v31 )
    return 7;
  v52 = translation[2] * rotation_stride4[5] - translation[1] * rotation_stride4[9];
  v12 = fabs(v52);
  v32 = (v12 <= half_a[1] * v46 + half_a[2] * v43 + half_b[2] * v41 + half_b[2] * v39) & (unsigned __int8)v31;
  if ( !v32 )
    return 8;
  v53 = translation[2] * rotation_stride4[6] - translation[1] * rotation_stride4[10];
  v11 = fabs(v53);
  v33 = (v11 <= half_a[1] * v47 + half_a[2] * v44 + half_b[2] * v40 + half_b[1] * v39) & (unsigned __int8)v32;
  if ( !v33 )
    return 9;
  v54 = *translation * rotation_stride4[8] - translation[2] * *rotation_stride4;
  v10 = fabs(v54);
  v34 = (v10 <= *half_a * v45 + half_a[2] * v39 + half_b[1] * v44 + half_b[2] * v43) & (unsigned __int8)v33;
  if ( !v34 )
    return 10;
  v55 = *translation * rotation_stride4[9] - translation[2] * rotation_stride4[1];
  v9 = fabs(v55);
  v35 = (v9 <= *half_a * v46 + half_a[2] * v40 + *half_b * v44 + half_b[2] * v42) & (unsigned __int8)v34;
  if ( !v35 )
    return 11;
  v56 = *translation * rotation_stride4[10] - translation[2] * rotation_stride4[2];
  v8 = fabs(v56);
  v36 = (v8 <= *half_a * v47 + half_a[2] * v41 + *half_b * v43 + half_b[1] * v42) & (unsigned __int8)v35;
  if ( !v36 )
    return 12;
  v57 = translation[1] * *rotation_stride4 - *translation * rotation_stride4[4];
  v7 = fabs(v57);
  v37 = (v7 <= *half_a * v42 + half_a[1] * v39 + half_b[1] * v47 + half_b[2] * v46) & (unsigned __int8)v36;
  if ( !v37 )
    return 13;
  v58 = translation[1] * rotation_stride4[1] - *translation * rotation_stride4[5];
  v6 = fabs(v58);
  v38 = (v6 <= *half_a * v43 + half_a[1] * v40 + *half_b * v47 + half_b[2] * v45) & (unsigned __int8)v37;
  if ( !v38 )
    return 14;
  v59 = translation[1] * rotation_stride4[2] - *translation * rotation_stride4[6];
  v5 = fabs(v59);
  if ( ((v5 <= *half_a * v44 + half_a[1] * v41 + *half_b * v46 + half_b[1] * v45) & (unsigned __int8)v38) != 0 )
    return 0;
  else
    return 15;
}

