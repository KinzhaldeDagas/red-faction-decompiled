// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5140 rf_geomod_fragment_count_from_fourteen_rays
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl(source,radius,FULL32bitRoom), three DWORD stack args; old char room prototype incorrect. Native MOV DWORD[EBP+16] then PUSH at each of14 calls preserves entire room pointer
// into4C55F0; caller4C488B also supplies full pointer, not sign-extended byte. Starts F32score=radius*DOUBLE14. Probes six axial endpoints source +/-radius in X,Y,Z order; then eight
// diagonal endpoints with F32d=radius*DOUBLE0.5773500204086304 in sign order +++, -++, +-+, --+, ++-, -+-, +--, ---. Each endpoint operation copies source and stores binary32
// components.
// Each calls4C55F0(source,end,room,radius,&score), subtracting SOLID HIT FRACTION (face nonnull,metadata flag8 clear) or radius for miss/liquid/flag8. No conversion from fraction to
// world distance: mixed-unit scoring is original. All14 calls executed, return AL ignored. At end F32doubled=score+score, floor_float(doubled), __ftol2_sse truncation, returns signed
// min(result,16). No LOWER clamp, radius/finite/roomNULL validation, random draws, allocation or count<=0 rejection. Negative return can make spawn report success with zero new
// allocations.
int __cdecl rf_geomod_fragment_count_from_fourteen_rays(float *source, float radius, int room)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  double v19; // st7
  float v21; // [esp+0h] [ebp-180h]
  float value; // [esp+4h] [ebp-17Ch]
  float valuea; // [esp+4h] [ebp-17Ch]
  float v24; // [esp+8h] [ebp-178h]
  float v25; // [esp+8h] [ebp-178h]
  float v26; // [esp+8h] [ebp-178h]
  float v27; // [esp+8h] [ebp-178h]
  float v28; // [esp+Ch] [ebp-174h]
  float v29[3]; // [esp+10h] [ebp-170h] BYREF
  float v30[3]; // [esp+1Ch] [ebp-164h] BYREF
  float v31[3]; // [esp+28h] [ebp-158h] BYREF
  float v32[3]; // [esp+34h] [ebp-14Ch] BYREF
  float v33[3]; // [esp+40h] [ebp-140h] BYREF
  float v34[3]; // [esp+4Ch] [ebp-134h] BYREF
  float v35[3]; // [esp+58h] [ebp-128h] BYREF
  float v36[3]; // [esp+64h] [ebp-11Ch] BYREF
  float v37[3]; // [esp+70h] [ebp-110h] BYREF
  float v38[3]; // [esp+7Ch] [ebp-104h] BYREF
  float v39[3]; // [esp+88h] [ebp-F8h] BYREF
  float v40[3]; // [esp+94h] [ebp-ECh] BYREF
  float v41[3]; // [esp+A0h] [ebp-E0h] BYREF
  float v42[3]; // [esp+ACh] [ebp-D4h] BYREF
  float v43[3]; // [esp+B8h] [ebp-C8h] BYREF
  float v44[3]; // [esp+C4h] [ebp-BCh] BYREF
  float v45[3]; // [esp+D0h] [ebp-B0h] BYREF
  float v46[3]; // [esp+DCh] [ebp-A4h] BYREF
  float v47[3]; // [esp+E8h] [ebp-98h] BYREF
  float v48[3]; // [esp+F4h] [ebp-8Ch] BYREF
  float v49[3]; // [esp+100h] [ebp-80h] BYREF
  float v50[3]; // [esp+10Ch] [ebp-74h] BYREF
  float sum_result[3]; // [esp+118h] [ebp-68h] BYREF
  float v52[3]; // [esp+124h] [ebp-5Ch] BYREF
  float v53[3]; // [esp+130h] [ebp-50h] BYREF
  float v54[3]; // [esp+13Ch] [ebp-44h] BYREF
  float v55[3]; // [esp+148h] [ebp-38h] BYREF
  float v56[3]; // [esp+154h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+160h] [ebp-20h] BYREF
  int v58; // [esp+16Ch] [ebp-14h] BYREF
  float destination; // [esp+170h] [ebp-10h] BYREF
  float v60; // [esp+174h] [ebp-Ch]
  float v61; // [esp+178h] [ebp-8h]
  float v62; // [esp+17Ch] [ebp-4h]

  *(float *)&v58 = radius * 14.0;
  rf_vector3_copy_return_destination(&destination, source);
  destination = destination + radius;
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  rf_vector_copy(&destination, copy_result, source);
  destination = destination - radius;
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  rf_vector_copy(&destination, v56, source);
  v60 = v60 + radius;
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  rf_vector_copy(&destination, v55, source);
  v60 = v60 - radius;
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  rf_vector_copy(&destination, v54, source);
  v61 = v61 + radius;
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  rf_vector_copy(&destination, v53, source);
  v61 = v61 - radius;
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  v62 = radius * 0.5773500204086304;
  v3 = rf_vector3_set_components_return_destination(v52, v62, v62, v62);
  v4 = rf_vector_add(source, sum_result, v3);
  rf_vector_copy(&destination, v50, v4);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  v21 = -v62;
  v5 = rf_vector3_set_components_return_destination(v49, v21, v62, v62);
  v6 = rf_vector_add(source, v48, v5);
  rf_vector_copy(&destination, v47, v6);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  value = -v62;
  v7 = rf_vector3_set_components_return_destination(v46, v62, value, v62);
  v8 = rf_vector_add(source, v45, v7);
  rf_vector_copy(&destination, v44, v8);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  valuea = -v62;
  v9 = rf_vector3_set_components_return_destination(v43, valuea, valuea, v62);
  v10 = rf_vector_add(source, v42, v9);
  rf_vector_copy(&destination, v41, v10);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  v24 = -v62;
  v11 = rf_vector3_set_components_return_destination(v40, v62, v62, v24);
  v12 = rf_vector_add(source, v39, v11);
  rf_vector_copy(&destination, v38, v12);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  v25 = -v62;
  v13 = rf_vector3_set_components_return_destination(v37, v25, v62, v25);
  v14 = rf_vector_add(source, v36, v13);
  rf_vector_copy(&destination, v35, v14);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  v26 = -v62;
  v15 = rf_vector3_set_components_return_destination(v34, v62, v26, v26);
  v16 = rf_vector_add(source, v33, v15);
  rf_vector_copy(&destination, v32, v16);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  v27 = -v62;
  v17 = rf_vector3_set_components_return_destination(v31, v27, v27, v27);
  v18 = rf_vector_add(source, v30, v17);
  rf_vector_copy(&destination, v29, v18);
  rf_geomod_segment_subtract_hit_fraction_or_fallback(source, &destination, room, radius, (float *)&v58);
  v28 = *(float *)&v58 + *(float *)&v58;
  v19 = rf_floor_float(v28);
  return rf_int_min_signed((int)v19, 16);
}

