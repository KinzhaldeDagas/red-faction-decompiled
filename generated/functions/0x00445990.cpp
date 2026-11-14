// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445990 rf_entity_filter_vector_by_descriptor_axis_modes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Explicit cdecl(outVector3f,required entity,inputVector3f), full EAX=original out pointer. Initialize local accumulator to
// FLOAT32 zeros. For axes0,1,2 in order RE-READ descriptor pointer entity2136 and its DWORD20/24/28 selector. EXACT2 computes F32 dot(entity basis row252/264/276,input), scales that
// same row with FLOAT32 component stores, then accumulates into all three local coordinates with sequential F32 stores. EXACT3 adds only input coordinateX/Y/Z to the matching
// accumulator coordinate, rounding toF32. Every other selector contributes nothing. Finally5590A0 transforms accumulated vector by dotting with all THREE basis rows at entity252;
// computes outputZ,Y,X into F32 temporaries before final vector setter and returns output pointer. No normalization, orthogonality, mode range, NULL, finite, speed or magnitude
// guard; zero accumulation does not bypass the final basis arithmetic (zero*NaN/Inf can produceNaN). Caller output is not written until all input/descriptor/basis processing
// completes, so source/output overlap is not an early write hazard. No entity mutation except through caller output alias. Corrected false integer output/return type to explicit
// float-pointer ABI without changing3 stack words.
float *__cdecl rf_entity_filter_vector_by_descriptor_axis_modes(float *out_vector, int entity, float *input_vector)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v7; // [esp+4h] [ebp-44h]
  float v8; // [esp+4h] [ebp-44h]
  float v9; // [esp+4h] [ebp-44h]
  int v10; // [esp+Ch] [ebp-3Ch]
  int v11; // [esp+10h] [ebp-38h]
  int v12; // [esp+14h] [ebp-34h]
  int v13[3]; // [esp+18h] [ebp-30h] BYREF
  int v14[3]; // [esp+24h] [ebp-24h] BYREF
  int v15[3]; // [esp+30h] [ebp-18h] BYREF
  float v16; // [esp+3Ch] [ebp-Ch] BYREF
  float v17; // [esp+40h] [ebp-8h]
  float v18; // [esp+44h] [ebp-4h]

  rf_vector3_set_components_return_destination(&v16, 0.0, 0.0, 0.0);
  v12 = *(_DWORD *)(*(_DWORD *)(entity + 2136) + 20);
  if ( v12 == 2 )
  {
    v7 = rf_vector_dot((float *)(entity + 252), input_vector);
    v3 = rf_vector_scale((float *)v15, v7, (float *)(entity + 252));
    rf_vector_accumulate(&v16, v3);
  }
  else if ( v12 == 3 )
  {
    v16 = v16 + *input_vector;
  }
  v11 = *(_DWORD *)(*(_DWORD *)(entity + 2136) + 24);
  if ( v11 == 2 )
  {
    v8 = rf_vector_dot((float *)(entity + 264), input_vector);
    v4 = rf_vector_scale((float *)v14, v8, (float *)(entity + 264));
    rf_vector_accumulate(&v16, v4);
  }
  else if ( v11 == 3 )
  {
    v17 = v17 + input_vector[1];
  }
  v10 = *(_DWORD *)(*(_DWORD *)(entity + 2136) + 28);
  if ( v10 == 2 )
  {
    v9 = rf_vector_dot((float *)(entity + 276), input_vector);
    v5 = rf_vector_scale((float *)v13, v9, (float *)(entity + 276));
    rf_vector_accumulate(&v16, v5);
  }
  else if ( v10 == 3 )
  {
    v18 = v18 + input_vector[2];
  }
  rf_vector3_transform_by_matrix_rows(&v16, out_vector, (float *)(entity + 252));
  return out_vector;
}

