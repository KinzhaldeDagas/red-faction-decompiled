// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F70E0 rf_scene_key_tracks_evaluate_vector0_bezier
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl explicit track pointer,then destination,fromIndex,toIndex,t;stream pointer8. Arguments destination,fromIndex,toIndex,t;each40-byte key has time0,value vector4,incoming control vector16,outgoing control vector28. If fromIndex<0,just copies toIndex value. Otherwise computes valueFrom*(1-t)^3+outgoingFrom*3*t*(1-t)^2+incomingTo*3*t*t*(1-t)+valueTo*t^3 through existing vector operations and float temporaries. No index/count/time/parameter clamp or tangent conversion;control points are used as absolute Bezier controls. Returns incidental vector-copy helper result.
float *__cdecl rf_scene_key_tracks_evaluate_vector0_bezier(_DWORD *a1, float *destination, int a3, int a4, float a5)
{
  float *v5; // eax
  float *vector0_value; // eax
  float *v8; // eax
  float *v9; // eax
  float *vector0_incoming_control; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *vector0_outgoing_control; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  float *v21; // eax
  float *v22; // eax
  float *v23; // eax
  float *v24; // eax
  float v25; // [esp+0h] [ebp-150h]
  float v26; // [esp+8h] [ebp-148h]
  float v27; // [esp+10h] [ebp-140h]
  float v28; // [esp+10h] [ebp-140h]
  float scalar; // [esp+18h] [ebp-138h]
  float *scalara; // [esp+18h] [ebp-138h]
  float v31; // [esp+20h] [ebp-130h]
  float *v32; // [esp+20h] [ebp-130h]
  float *v33; // [esp+28h] [ebp-128h]
  float v34[3]; // [esp+2Ch] [ebp-124h] BYREF
  float v35[3]; // [esp+38h] [ebp-118h] BYREF
  float v36[3]; // [esp+44h] [ebp-10Ch] BYREF
  float v37[3]; // [esp+50h] [ebp-100h] BYREF
  float scaled_result[3]; // [esp+5Ch] [ebp-F4h] BYREF
  float v39[3]; // [esp+68h] [ebp-E8h] BYREF
  float v40[3]; // [esp+74h] [ebp-DCh] BYREF
  float v41[3]; // [esp+80h] [ebp-D0h] BYREF
  float v42[3]; // [esp+8Ch] [ebp-C4h] BYREF
  float v43[3]; // [esp+98h] [ebp-B8h] BYREF
  float v44[3]; // [esp+A4h] [ebp-ACh] BYREF
  float v45[3]; // [esp+B0h] [ebp-A0h] BYREF
  float sum_result[3]; // [esp+BCh] [ebp-94h] BYREF
  float v47[3]; // [esp+C8h] [ebp-88h] BYREF
  float v48[3]; // [esp+D4h] [ebp-7Ch] BYREF
  float v49[3]; // [esp+E0h] [ebp-70h] BYREF
  float v50[3]; // [esp+ECh] [ebp-64h] BYREF
  float v51[3]; // [esp+F8h] [ebp-58h] BYREF
  float v52[3]; // [esp+104h] [ebp-4Ch] BYREF
  float v53[3]; // [esp+110h] [ebp-40h] BYREF
  float v54[3]; // [esp+11Ch] [ebp-34h] BYREF
  float v55[3]; // [esp+128h] [ebp-28h] BYREF
  float copy_result[3]; // [esp+134h] [ebp-1Ch] BYREF
  float v57[3]; // [esp+140h] [ebp-10h] BYREF
  float v58; // [esp+14Ch] [ebp-4h]

  if ( a3 >= 0 )
  {
    v58 = 1.0 - a5;
    vector0_value = rf_scene_key_tracks_get_vector0_value(a1, v39, a4);
    v8 = rf_vector_multiply_scalar(vector0_value, scaled_result, a5);
    v9 = rf_vector_multiply_scalar(v8, v37, a5);
    v33 = rf_vector_multiply_scalar(v9, v36, a5);
    v31 = v58;
    vector0_incoming_control = rf_scene_key_tracks_get_vector0_incoming_control(a1, v45, a4);
    v11 = rf_vector_multiply_scalar(vector0_incoming_control, v44, 3.0);
    v12 = rf_vector_multiply_scalar(v11, v43, a5);
    v13 = rf_vector_multiply_scalar(v12, v42, a5);
    v32 = rf_vector_multiply_scalar(v13, v41, v31);
    scalar = v58;
    v27 = v58;
    vector0_outgoing_control = rf_scene_key_tracks_get_vector0_outgoing_control(a1, v51, a3);
    v15 = rf_vector_multiply_scalar(vector0_outgoing_control, v50, 3.0);
    v16 = rf_vector_multiply_scalar(v15, v49, a5);
    v17 = rf_vector_multiply_scalar(v16, v48, v27);
    scalara = rf_vector_multiply_scalar(v17, v47, scalar);
    v28 = v58;
    v26 = v58;
    v25 = v58;
    v18 = rf_scene_key_tracks_get_vector0_value(a1, v55, a3);
    v19 = rf_vector_multiply_scalar(v18, v54, v25);
    v20 = rf_vector_multiply_scalar(v19, v53, v26);
    v21 = rf_vector_multiply_scalar(v20, v52, v28);
    v22 = rf_vector_add(v21, sum_result, scalara);
    v23 = rf_vector_add(v22, v40, v32);
    v24 = rf_vector_add(v23, v35, v33);
    return rf_vector_copy(destination, v34, v24);
  }
  else
  {
    v5 = rf_scene_key_tracks_get_vector0_value(a1, v57, a4);
    return rf_vector_copy(destination, copy_result, v5);
  }
}

