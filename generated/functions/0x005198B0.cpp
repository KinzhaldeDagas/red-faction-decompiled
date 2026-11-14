// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005198B0 rf_solid_bounding_sphere_rebuild
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall solid,no stack args. If vertex count120<1,writes radius96=0 and center100=(0,0,0). Otherwise initializes six FULL extreme-point vectors from first vertex,strictly updates Xmin/Xmax,Ymin/Ymax,Zmin/Zmax points over remaining vertices. Computes full3D squared separation for each axis-extreme pair,chooses X initially,Y if greater,Z if greater than current max(ties retain earlier axis). Z branch assigns dead temporary max=Y span instead of Z span,but temporary is never used afterward;selected Z endpoints and recomputed radius are unaffected. Initial center is float-stored midpoint of chosen pair,radius from selected endpoint-center. Expands in ORIGINAL vertex order:if
// dSquared>radiusSquared,d=sqrt(dSquared),newR=float((oldR+d)/2),rSquared=float(newR*newR),gap=float(d-newR),then each center component=float((newR*oldCenter+gap*point)/d). Final radius96 and center100 written. All extrema/pair/expansion comparisons skip updates on unordered;NaN initial seeds can persist. Order-dependent Ritter-style expansion,no minimum enclosing-sphere optimization,extra epsilon,finite/overflow/pointer validation or bounds72/84 update. Existing float* return is incidental:empty branch returns center pointer,nonempty final vector-assignment returns local stack result object,not a stable usable center pointer. Earlier repeatable seed/expansion note retained.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Type9 pickup outer-bounds consumer uses this stored raw solid sphere via48A2B0. Extrema are FULL points selected strictly in original vertex-array order; initial pair greatest XYZ full3D span, ties keep earlier axis. Midpoint/radius and Ritter expansions preserve native binary32 stores; never replace with AABBhalfDiagonal, renderedboundingbox or exactminimumenclosing sphere. Empty directcall writes sphere0, though519E60 itself only invokes on nonempty vertices.
float *__thiscall rf_solid_bounding_sphere_rebuild(float *this)
{
  int first_dword; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  int v8; // eax
  float *v9; // eax
  float v11[3]; // [esp+8h] [ebp-220h] BYREF
  float v12[3]; // [esp+14h] [ebp-214h] BYREF
  float v13[3]; // [esp+20h] [ebp-208h] BYREF
  float v14[3]; // [esp+2Ch] [ebp-1FCh] BYREF
  float v15[3]; // [esp+38h] [ebp-1F0h] BYREF
  float v16[3]; // [esp+44h] [ebp-1E4h] BYREF
  float sum_result[3]; // [esp+50h] [ebp-1D8h] BYREF
  float v18[3]; // [esp+5Ch] [ebp-1CCh] BYREF
  float v19[3]; // [esp+68h] [ebp-1C0h] BYREF
  float v20[3]; // [esp+74h] [ebp-1B4h] BYREF
  float v21[3]; // [esp+80h] [ebp-1A8h] BYREF
  float v22[3]; // [esp+8Ch] [ebp-19Ch] BYREF
  float v23[3]; // [esp+98h] [ebp-190h] BYREF
  float v24[3]; // [esp+A4h] [ebp-184h] BYREF
  float v25[3]; // [esp+B0h] [ebp-178h] BYREF
  float v26[3]; // [esp+BCh] [ebp-16Ch] BYREF
  float v27[3]; // [esp+C8h] [ebp-160h] BYREF
  float v28[3]; // [esp+D4h] [ebp-154h] BYREF
  float out_vector[3]; // [esp+E0h] [ebp-148h] BYREF
  float v30[3]; // [esp+ECh] [ebp-13Ch] BYREF
  float v31[3]; // [esp+F8h] [ebp-130h] BYREF
  float v32[3]; // [esp+104h] [ebp-124h] BYREF
  float v33[3]; // [esp+110h] [ebp-118h] BYREF
  float v34[3]; // [esp+11Ch] [ebp-10Ch] BYREF
  float v35[3]; // [esp+128h] [ebp-100h] BYREF
  float v36[3]; // [esp+134h] [ebp-F4h] BYREF
  float v37[3]; // [esp+140h] [ebp-E8h] BYREF
  float v38[3]; // [esp+14Ch] [ebp-DCh] BYREF
  float v39[3]; // [esp+158h] [ebp-D0h] BYREF
  float v40[3]; // [esp+164h] [ebp-C4h] BYREF
  float copy_result[3]; // [esp+170h] [ebp-B8h] BYREF
  float *v42; // [esp+17Ch] [ebp-ACh]
  float v43[3]; // [esp+180h] [ebp-A8h] BYREF
  float v44[3]; // [esp+18Ch] [ebp-9Ch] BYREF
  float v45; // [esp+198h] [ebp-90h]
  float v46; // [esp+19Ch] [ebp-8Ch]
  float v47; // [esp+1A0h] [ebp-88h]
  float v48; // [esp+1A4h] [ebp-84h]
  float v49; // [esp+1A8h] [ebp-80h]
  float v50[3]; // [esp+1ACh] [ebp-7Ch] BYREF
  float v51[3]; // [esp+1B8h] [ebp-70h] BYREF
  float v52; // [esp+1C4h] [ebp-64h]
  float rhs[3]; // [esp+1C8h] [ebp-60h] BYREF
  float v54; // [esp+1D4h] [ebp-54h]
  float lhs[3]; // [esp+1D8h] [ebp-50h] BYREF
  float v56; // [esp+1E4h] [ebp-44h]
  float destination[3]; // [esp+1E8h] [ebp-40h] BYREF
  float v58[3]; // [esp+1F4h] [ebp-34h] BYREF
  float v59[3]; // [esp+200h] [ebp-28h] BYREF
  int i; // [esp+20Ch] [ebp-1Ch]
  float v61; // [esp+210h] [ebp-18h]
  float *source; // [esp+214h] [ebp-14h]
  float *v63; // [esp+218h] [ebp-10h]
  float v64; // [esp+21Ch] [ebp-Ch] BYREF
  float v65; // [esp+220h] [ebp-8h]
  float v66; // [esp+224h] [ebp-4h]

  rf_vector3_default_construct_noop(v43);
  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(lhs);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v50);
  rf_vector3_default_construct_noop(v59);
  rf_vector3_default_construct_noop(v58);
  rf_vector3_default_construct_noop(v44);
  rf_vector3_default_construct_noop(v51);
  rf_vector3_default_construct_noop(&v64);
  if ( rf_receiver_get_first_dword(this + 30) >= 1 )
  {
    source = *(float **)sub_552200((_DWORD *)this + 30, 0);
    rf_vector_copy(rhs, copy_result, source);
    rf_vector_copy(lhs, v40, source);
    rf_vector_copy(destination, v39, source);
    rf_vector_copy(v50, v38, source);
    rf_vector_copy(v59, v37, source);
    rf_vector_copy(v58, v36, source);
    for ( i = 1; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword(this + 30);
      if ( i >= first_dword )
        break;
      source = *(float **)sub_552200((_DWORD *)this + 30, i);
      v42 = source;
      if ( rhs[0] > (double)*source )
        rf_vector_copy(rhs, v35, v42);
      if ( lhs[0] < (double)*v42 )
        rf_vector_copy(lhs, v34, v42);
      if ( destination[1] > (double)v42[1] )
        rf_vector_copy(destination, v33, v42);
      if ( v50[1] < (double)v42[1] )
        rf_vector_copy(v50, v32, v42);
      if ( v59[2] > (double)v42[2] )
        rf_vector_copy(v59, v31, v42);
      if ( v58[2] < (double)v42[2] )
        rf_vector_copy(v58, v30, v42);
    }
    v3 = rf_vector_subtract(lhs, out_vector, rhs);
    rf_vector_copy(v43, v28, v3);
    v52 = rf_vector_length_squared(v43);
    v4 = rf_vector_subtract(v50, v27, destination);
    rf_vector_copy(v43, v26, v4);
    v45 = rf_vector_length_squared(v43);
    v5 = rf_vector_subtract(v58, v25, v59);
    rf_vector_copy(v43, v24, v5);
    v61 = rf_vector_length_squared(v43);
    rf_vector_copy(v44, v23, rhs);
    rf_vector_copy(v51, v22, lhs);
    v49 = v52;
    if ( v52 < (double)v45 )
    {
      v49 = v45;
      rf_vector_copy(v44, v21, destination);
      rf_vector_copy(v51, v20, v50);
    }
    if ( v49 < (double)v61 )
    {
      v49 = v45;
      rf_vector_copy(v44, v19, v59);
      rf_vector_copy(v51, v18, v58);
    }
    v6 = rf_vector_add(v44, sum_result, v51);
    rf_vector_copy(&v64, v16, v6);
    rf_vector3_scale_in_place_return_self(&v64, 0.5);
    v7 = rf_vector_subtract(v51, v15, &v64);
    rf_vector_copy(v43, v14, v7);
    v54 = rf_vector_length_squared(v43);
    v48 = rf_sqrt_float(v54);
    for ( i = 0; ; ++i )
    {
      v8 = rf_receiver_get_first_dword(this + 30);
      if ( i >= v8 )
        break;
      v63 = *(float **)sub_552200((_DWORD *)this + 30, i);
      v9 = rf_vector_subtract(v63, v13, &v64);
      rf_vector_copy(v43, v12, v9);
      v47 = rf_vector_length_squared(v43);
      if ( v54 < (double)v47 )
      {
        v46 = rf_sqrt_float(v47);
        v48 = (v48 + v46) / 2.0;
        v54 = v48 * v48;
        v56 = v46 - v48;
        v64 = (v48 * v64 + v56 * *v63) / v46;
        v65 = (v48 * v65 + v56 * v63[1]) / v46;
        v66 = (v48 * v66 + v56 * v63[2]) / v46;
      }
    }
    *(this + 24) = v48;
    return rf_vector_copy(this + 25, v11, &v64);
  }
  else
  {
    *(this + 24) = 0.0;
    return rf_vector3_zero_return_destination(this + 25);
  }
}

