// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6CE0 rf_scene_key_tracks_evaluate_vector2_bezier
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall track pointer;stream pointer16. Arguments destination,fromIndex,toIndex,t;each40-byte key has time0,value vector4,incoming control vector16,outgoing control vector28. If fromIndex<0,just copies toIndex value. Otherwise computes valueFrom*(1-t)^3+outgoingFrom*3*t*(1-t)^2+incomingTo*3*t*t*(1-t)+valueTo*t^3 through existing vector operations and float temporaries. No index/count/time/parameter clamp or tangent conversion;control points are used as absolute Bezier controls. Returns incidental vector-copy helper result.
float *__thiscall rf_scene_key_tracks_evaluate_vector2_bezier(
        _DWORD *this,
        float *destination,
        int a3,
        int a4,
        float a5)
{
  float *v5; // eax
  float *vector2_value; // eax
  float *v8; // eax
  float *v9; // eax
  float *vector2_incoming_control; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *vector2_outgoing_control; // eax
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
  float v25; // [esp+0h] [ebp-154h]
  float v26; // [esp+8h] [ebp-14Ch]
  float v27; // [esp+10h] [ebp-144h]
  float v28; // [esp+10h] [ebp-144h]
  float scalar; // [esp+18h] [ebp-13Ch]
  float *scalara; // [esp+18h] [ebp-13Ch]
  float v31; // [esp+20h] [ebp-134h]
  float *v32; // [esp+20h] [ebp-134h]
  float *v33; // [esp+28h] [ebp-12Ch]
  float v35[3]; // [esp+30h] [ebp-124h] BYREF
  float v36[3]; // [esp+3Ch] [ebp-118h] BYREF
  float v37[3]; // [esp+48h] [ebp-10Ch] BYREF
  float v38[3]; // [esp+54h] [ebp-100h] BYREF
  float scaled_result[3]; // [esp+60h] [ebp-F4h] BYREF
  float v40[3]; // [esp+6Ch] [ebp-E8h] BYREF
  float v41[3]; // [esp+78h] [ebp-DCh] BYREF
  float v42[3]; // [esp+84h] [ebp-D0h] BYREF
  float v43[3]; // [esp+90h] [ebp-C4h] BYREF
  float v44[3]; // [esp+9Ch] [ebp-B8h] BYREF
  float v45[3]; // [esp+A8h] [ebp-ACh] BYREF
  float v46[3]; // [esp+B4h] [ebp-A0h] BYREF
  float sum_result[3]; // [esp+C0h] [ebp-94h] BYREF
  float v48[3]; // [esp+CCh] [ebp-88h] BYREF
  float v49[3]; // [esp+D8h] [ebp-7Ch] BYREF
  float v50[3]; // [esp+E4h] [ebp-70h] BYREF
  float v51[3]; // [esp+F0h] [ebp-64h] BYREF
  float v52[3]; // [esp+FCh] [ebp-58h] BYREF
  float v53[3]; // [esp+108h] [ebp-4Ch] BYREF
  float v54[3]; // [esp+114h] [ebp-40h] BYREF
  float v55[3]; // [esp+120h] [ebp-34h] BYREF
  float v56[3]; // [esp+12Ch] [ebp-28h] BYREF
  float copy_result[3]; // [esp+138h] [ebp-1Ch] BYREF
  float v58[3]; // [esp+144h] [ebp-10h] BYREF
  float v59; // [esp+150h] [ebp-4h]

  if ( a3 >= 0 )
  {
    v59 = 1.0 - a5;
    vector2_value = rf_scene_key_tracks_get_vector2_value(this, v40, a4);
    v8 = rf_vector_multiply_scalar(vector2_value, scaled_result, a5);
    v9 = rf_vector_multiply_scalar(v8, v38, a5);
    v33 = rf_vector_multiply_scalar(v9, v37, a5);
    v31 = v59;
    vector2_incoming_control = rf_scene_key_tracks_get_vector2_incoming_control(this, v46, a4);
    v11 = rf_vector_multiply_scalar(vector2_incoming_control, v45, 3.0);
    v12 = rf_vector_multiply_scalar(v11, v44, a5);
    v13 = rf_vector_multiply_scalar(v12, v43, a5);
    v32 = rf_vector_multiply_scalar(v13, v42, v31);
    scalar = v59;
    v27 = v59;
    vector2_outgoing_control = rf_scene_key_tracks_get_vector2_outgoing_control(this, v52, a3);
    v15 = rf_vector_multiply_scalar(vector2_outgoing_control, v51, 3.0);
    v16 = rf_vector_multiply_scalar(v15, v50, a5);
    v17 = rf_vector_multiply_scalar(v16, v49, v27);
    scalara = rf_vector_multiply_scalar(v17, v48, scalar);
    v28 = v59;
    v26 = v59;
    v25 = v59;
    v18 = rf_scene_key_tracks_get_vector2_value(this, v56, a3);
    v19 = rf_vector_multiply_scalar(v18, v55, v25);
    v20 = rf_vector_multiply_scalar(v19, v54, v26);
    v21 = rf_vector_multiply_scalar(v20, v53, v28);
    v22 = rf_vector_add(v21, sum_result, scalara);
    v23 = rf_vector_add(v22, v41, v32);
    v24 = rf_vector_add(v23, v36, v33);
    return rf_vector_copy(destination, v35, v24);
  }
  else
  {
    v5 = rf_scene_key_tracks_get_vector2_value(this, v58, a4);
    return rf_vector_copy(destination, copy_result, v5);
  }
}

