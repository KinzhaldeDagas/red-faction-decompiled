// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580D60 rf_segment_clip_aabb_axis_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Cdecl endpointA3f,endpointB3f,boundsMin3f,boundsMax3f,axis,other1,other2. If A[axis]>B[axis],swaps ENTIRE vectors first. Returns1 when min[axis]>B[axis] or max[axis]<A[axis]. Otherwise if A below min,interpolates all3 selected components toward B with t=(min-A)/(B-A);then if B above max,interpolates B from already-clipped A with t=(max-A)/(B-A). Returns0 accepted,mutating endpoints;boundary equality accepted,zero-length segments inside accepted. No explicit parallel/finite/index/min<=max guard;strict outside tests avoid denominator0 for ordinary finite valid boxes. Reject may still have swapped endpoints. Sequential component writes assume three distinct valid axis indices as callers provide.
char __cdecl rf_segment_clip_aabb_axis_in_place(
        float *destination,
        float *source,
        char *a3,
        char *a4,
        int a5,
        int a6,
        int a7)
{
  char *v7; // esi
  char *v8; // esi
  char *v10; // esi
  char *v11; // esi
  char *v12; // esi
  char *v13; // esi
  char *v14; // esi
  char *v15; // edi
  char *v16; // eax
  char *v17; // esi
  char *v18; // edi
  char *v19; // eax
  char *v20; // esi
  char *v21; // edi
  char *v22; // eax
  double v23; // st7
  char *v24; // esi
  char *v25; // esi
  char *v26; // esi
  char *v27; // esi
  char *v28; // edi
  char *v29; // eax
  char *v30; // esi
  char *v31; // edi
  char *v32; // eax
  char *v33; // esi
  char *v34; // edi
  char *v35; // eax
  double v36; // st7
  double v37; // [esp+10h] [ebp-64h]
  double v38; // [esp+18h] [ebp-5Ch]
  double v39; // [esp+20h] [ebp-54h]
  double v40; // [esp+30h] [ebp-44h]
  double v41; // [esp+38h] [ebp-3Ch]
  double v42; // [esp+40h] [ebp-34h]
  float v43[3]; // [esp+48h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+54h] [ebp-20h] BYREF
  float v45; // [esp+60h] [ebp-14h]
  float v46; // [esp+64h] [ebp-10h]
  float v47[3]; // [esp+68h] [ebp-Ch] BYREF

  v7 = rf_vector_component_address_unchecked((char *)source, a5);
  if ( *(float *)rf_vector_component_address_unchecked((char *)destination, a5) > (double)*(float *)v7 )
  {
    rf_vector3_copy_return_destination(v47, destination);
    rf_vector_copy(destination, copy_result, source);
    rf_vector_copy(source, v43, v47);
  }
  v8 = rf_vector_component_address_unchecked((char *)source, a5);
  if ( *(float *)rf_vector_component_address_unchecked(a3, a5) > (double)*(float *)v8 )
    return 1;
  v10 = rf_vector_component_address_unchecked((char *)destination, a5);
  if ( *(float *)rf_vector_component_address_unchecked(a4, a5) < (double)*(float *)v10 )
    return 1;
  v11 = rf_vector_component_address_unchecked((char *)destination, a5);
  if ( *(float *)rf_vector_component_address_unchecked(a3, a5) > (double)*(float *)v11 )
  {
    v12 = rf_vector_component_address_unchecked(a3, a5);
    v42 = *(float *)v12 - *(float *)rf_vector_component_address_unchecked((char *)destination, a5);
    v13 = rf_vector_component_address_unchecked((char *)source, a5);
    v46 = v42 / (*(float *)v13 - *(float *)rf_vector_component_address_unchecked((char *)destination, a5));
    v14 = rf_vector_component_address_unchecked((char *)destination, a5);
    v15 = rf_vector_component_address_unchecked((char *)source, a5);
    v16 = rf_vector_component_address_unchecked((char *)destination, a5);
    v41 = (*(float *)v15 - *(float *)v16) * v46 + *(float *)v14;
    *(float *)rf_vector_component_address_unchecked((char *)destination, a5) = v41;
    v17 = rf_vector_component_address_unchecked((char *)destination, a6);
    v18 = rf_vector_component_address_unchecked((char *)source, a6);
    v19 = rf_vector_component_address_unchecked((char *)destination, a6);
    v40 = (*(float *)v18 - *(float *)v19) * v46 + *(float *)v17;
    *(float *)rf_vector_component_address_unchecked((char *)destination, a6) = v40;
    v20 = rf_vector_component_address_unchecked((char *)destination, a7);
    v21 = rf_vector_component_address_unchecked((char *)source, a7);
    v22 = rf_vector_component_address_unchecked((char *)destination, a7);
    v23 = (*(float *)v21 - *(float *)v22) * v46 + *(float *)v20;
    *(float *)rf_vector_component_address_unchecked((char *)destination, a7) = v23;
  }
  v24 = rf_vector_component_address_unchecked((char *)source, a5);
  if ( *(float *)rf_vector_component_address_unchecked(a4, a5) < (double)*(float *)v24 )
  {
    v25 = rf_vector_component_address_unchecked(a4, a5);
    v39 = *(float *)v25 - *(float *)rf_vector_component_address_unchecked((char *)destination, a5);
    v26 = rf_vector_component_address_unchecked((char *)source, a5);
    v45 = v39 / (*(float *)v26 - *(float *)rf_vector_component_address_unchecked((char *)destination, a5));
    v27 = rf_vector_component_address_unchecked((char *)destination, a5);
    v28 = rf_vector_component_address_unchecked((char *)source, a5);
    v29 = rf_vector_component_address_unchecked((char *)destination, a5);
    v38 = (*(float *)v28 - *(float *)v29) * v45 + *(float *)v27;
    *(float *)rf_vector_component_address_unchecked((char *)source, a5) = v38;
    v30 = rf_vector_component_address_unchecked((char *)destination, a6);
    v31 = rf_vector_component_address_unchecked((char *)source, a6);
    v32 = rf_vector_component_address_unchecked((char *)destination, a6);
    v37 = (*(float *)v31 - *(float *)v32) * v45 + *(float *)v30;
    *(float *)rf_vector_component_address_unchecked((char *)source, a6) = v37;
    v33 = rf_vector_component_address_unchecked((char *)destination, a7);
    v34 = rf_vector_component_address_unchecked((char *)source, a7);
    v35 = rf_vector_component_address_unchecked((char *)destination, a7);
    v36 = (*(float *)v34 - *(float *)v35) * v45 + *(float *)v33;
    *(float *)rf_vector_component_address_unchecked((char *)source, a7) = v36;
  }
  return 0;
}

