// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562EB0 rf_model_handle_set_node_transform_by_value
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Corrected false fastcall/byte-fragment declaration:ECX handle plus16stack words=index,positionXYZ BY VALUE,9float matrix BY VALUE,ancestorCount,falloff,propagateByte; RET64. Tag2 ignores position/propagate and forwards index,matrix,ancestorCount,falloff to587A60 bone override. Tag3 decodes index and unchecked-copies definition node name to local76byte buffer. Kind0 writes runtime mesh override position32/matrix44,sets flag28 bit40000000 and RETURNS EARLY even if propagation requested. Kinds2/3/4 replace runtime point/dummy/effect position(12/12/92),convert orientation to legacy quaternion for3/4, set dirty bits20000000/40000000/20000000, and compute old-minus-new displacement. Only propagateByte EXACTLY1
// scans other flat objects for case-sensitive parent-name==edited name. Reads each child transform; nonmesh child gets childPosition-displacement, mesh child gets NEGATED displacement instead of retrieved position; recurses with same orientation/ancestor/falloff and propagation1. Unsupported kind1/default can enter propagation with UNINITIALIZED local name. No cycle/name-length/index/instance checks or rollback; raw EAX pointer/flag/delegate bits, not success.
unsigned int __thiscall rf_model_handle_set_node_transform_by_value(
        void *this,
        int a2,
        float rhs,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12,
        float a13,
        float a14,
        int a15,
        float a16,
        unsigned __int8 a17)
{
  unsigned int result; // eax
  float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  float *v21; // eax
  float *v22; // eax
  bool v23; // cf
  float v24; // [esp-30h] [ebp-1FCh] BYREF
  float v25; // [esp-2Ch] [ebp-1F8h]
  float v26; // [esp-28h] [ebp-1F4h]
  float v27; // [esp-24h] [ebp-1F0h] BYREF
  float v28; // [esp-20h] [ebp-1ECh] BYREF
  float v29; // [esp-1Ch] [ebp-1E8h]
  float v30; // [esp-18h] [ebp-1E4h]
  float v31; // [esp-14h] [ebp-1E0h]
  float v32; // [esp-10h] [ebp-1DCh]
  float v33; // [esp-Ch] [ebp-1D8h]
  float v34; // [esp-8h] [ebp-1D4h]
  float v35; // [esp-4h] [ebp-1D0h]
  int v36; // [esp+0h] [ebp-1CCh]
  int v37; // [esp+4h] [ebp-1C8h]
  int v38; // [esp+8h] [ebp-1C4h]
  int v39; // [esp+Ch] [ebp-1C0h]
  int v40; // [esp+10h] [ebp-1BCh]
  unsigned __int8 v41; // [esp+16h] [ebp-1B6h]
  unsigned __int8 v42; // [esp+17h] [ebp-1B5h]
  unsigned __int8 *v43; // [esp+18h] [ebp-1B4h]
  const char *parent_name; // [esp+1Ch] [ebp-1B0h]
  char v45; // [esp+23h] [ebp-1A9h]
  _BYTE *v46; // [esp+24h] [ebp-1A8h]
  _BYTE *v47; // [esp+28h] [ebp-1A4h]
  char *v48; // [esp+2Ch] [ebp-1A0h]
  char v49; // [esp+33h] [ebp-199h]
  _BYTE *v50; // [esp+34h] [ebp-198h]
  _BYTE *v51; // [esp+38h] [ebp-194h]
  char *v52; // [esp+3Ch] [ebp-190h]
  char v53; // [esp+43h] [ebp-189h]
  _BYTE *v54; // [esp+44h] [ebp-188h]
  _BYTE *v55; // [esp+48h] [ebp-184h]
  char *v56; // [esp+4Ch] [ebp-180h]
  char v57; // [esp+53h] [ebp-179h]
  _BYTE *v58; // [esp+54h] [ebp-178h]
  _BYTE *v59; // [esp+58h] [ebp-174h]
  char *v60; // [esp+5Ch] [ebp-170h]
  int v61; // [esp+60h] [ebp-16Ch]
  void *v62; // [esp+64h] [ebp-168h]
  float v63[4]; // [esp+78h] [ebp-154h] BYREF
  float v64[3]; // [esp+88h] [ebp-144h] BYREF
  float v65[3]; // [esp+94h] [ebp-138h] BYREF
  float v66[3]; // [esp+A0h] [ebp-12Ch] BYREF
  float v67[4]; // [esp+ACh] [ebp-120h] BYREF
  float v68[3]; // [esp+BCh] [ebp-110h] BYREF
  float v69[3]; // [esp+C8h] [ebp-104h] BYREF
  float v70[3]; // [esp+D4h] [ebp-F8h] BYREF
  float v71[3]; // [esp+E0h] [ebp-ECh] BYREF
  float v72[3]; // [esp+ECh] [ebp-E0h] BYREF
  float out_vector[3]; // [esp+F8h] [ebp-D4h] BYREF
  float v74[3]; // [esp+104h] [ebp-C8h] BYREF
  float copy_result[4]; // [esp+110h] [ebp-BCh] BYREF
  int v76; // [esp+120h] [ebp-ACh] BYREF
  float v77[9]; // [esp+124h] [ebp-A8h] BYREF
  int v78; // [esp+148h] [ebp-84h] BYREF
  int v79; // [esp+14Ch] [ebp-80h] BYREF
  float v80[3]; // [esp+150h] [ebp-7Ch] BYREF
  int v81; // [esp+15Ch] [ebp-70h]
  int v82; // [esp+160h] [ebp-6Ch]
  float destination[3]; // [esp+164h] [ebp-68h] BYREF
  int v84; // [esp+170h] [ebp-5Ch] BYREF
  _BYTE v85[76]; // [esp+174h] [ebp-58h] BYREF
  int v86; // [esp+1C4h] [ebp-8h] BYREF
  int v87; // [esp+1C8h] [ebp-4h] BYREF

  v62 = this;
  result = (unsigned int)this;
  if ( *(_DWORD *)this == 2 )
  {
    *(float *)&v38 = a16;
    v37 = a15;
    rf_matrix3_copy_construct((int)&v28, &a6);
    return rf_character_instance_set_bone_orientation_override(
             *((void **)v62 + 1),
             a2,
             v28,
             v29,
             v30,
             v31,
             v32,
             v33,
             v34,
             v35,
             *(float *)&v36,
             v37,
             *(float *)&v38);
  }
  else if ( *(_DWORD *)v62 == 3 )
  {
    rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
    result = (unsigned int)rf_scene_definition_decode_flat_object_index(*((_DWORD **)v62 + 2), a2, &v87, &v86, &v84);
    v61 = v87;
    switch ( v87 )
    {
      case 0:
        v60 = (char *)(*(_DWORD *)(*((_DWORD *)v62 + 2) + 72) + 292 * v86);
        v59 = v85;
        v58 = v85;
        do
        {
          v57 = *v60;
          *v59 = v57;
          ++v60;
          ++v59;
        }
        while ( v57 );
        rf_vector_copy(
          destination,
          copy_result,
          (const float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 20) + 152 * v86 + 32));
        rf_vector_copy((float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 20) + 152 * v86 + 32), v74, &rhs);
        rf_matrix3_copy((float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 20) + 152 * v86 + 44), &a6);
        result = *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 20) + 152 * v86 + 28) | 0x40000000;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 20) + 152 * v86 + 28) = result;
        return result;
      case 2:
        v56 = (char *)(*(_DWORD *)(*((_DWORD *)v62 + 2) + 80) + 180 * v86);
        v55 = v85;
        v54 = v85;
        do
        {
          v53 = *v56;
          *v55 = v53;
          ++v56;
          ++v55;
        }
        while ( v53 );
        v18 = rf_vector_subtract(
                (const float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 24) + 60 * v86 + 12),
                out_vector,
                &rhs);
        rf_vector_copy(destination, v72, v18);
        rf_vector_copy((float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 24) + 60 * v86 + 12), v71, &rhs);
        result = *(_DWORD *)(*((_DWORD *)v62 + 1) + 24);
        *(_DWORD *)(result + 60 * v86 + 8) |= 0x20000000u;
        goto LABEL_17;
      case 3:
        v48 = (char *)(*(_DWORD *)(*((_DWORD *)v62 + 2) + 96) + 172 * v86);
        v47 = v85;
        v46 = v85;
        do
        {
          v45 = *v48;
          *v47 = v45;
          ++v48;
          ++v47;
        }
        while ( v45 );
        v21 = rf_vector_subtract((const float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 32) + 40 * v86 + 12), v66, &rhs);
        rf_vector_copy(destination, v65, v21);
        rf_vector_copy((float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 32) + 40 * v86 + 12), v64, &rhs);
        v22 = rf_quaternion_set_from_matrix3_normalized_legacy(v63, &a6);
        rf_float4_copy_return_destination((float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 32) + 40 * v86 + 24), v22);
        result = *(_DWORD *)(*((_DWORD *)v62 + 1) + 32);
        *(_DWORD *)(result + 40 * v86 + 8) |= 0x40000000u;
        goto LABEL_17;
      case 4:
        v52 = (char *)(*(_DWORD *)(*((_DWORD *)v62 + 2) + 88) + 220 * v86);
        v51 = v85;
        v50 = v85;
        do
        {
          v49 = *v52;
          *v51 = v49;
          ++v52;
          ++v51;
        }
        while ( v49 );
        v19 = rf_vector_subtract((const float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 28) + 164 * v86 + 92), v70, &rhs);
        rf_vector_copy(destination, v69, v19);
        rf_vector_copy((float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 28) + 164 * v86 + 92), v68, &rhs);
        v20 = rf_quaternion_set_from_matrix3_normalized_legacy(v67, &a6);
        rf_float4_copy_return_destination((float *)(*(_DWORD *)(*((_DWORD *)v62 + 1) + 28) + 164 * v86 + 104), v20);
        result = *(_DWORD *)(*((_DWORD *)v62 + 1) + 28);
        *(_DWORD *)(result + 164 * v86 + 20) |= 0x20000000u;
        goto LABEL_17;
      default:
LABEL_17:
        if ( a17 != 1 )
          return result;
        result = rf_scene_definition_get_flat_object_count(*((_DWORD **)v62 + 2));
        v82 = result;
        v81 = 0;
        break;
    }
    while ( v81 < v82 )
    {
      if ( v81 != a2 )
      {
        parent_name = rf_model_handle_get_parent_name(v62, v81);
        v43 = v85;
        while ( 1 )
        {
          v42 = *v43;
          v23 = v42 < (unsigned int)*parent_name;
          if ( v42 != *parent_name )
            break;
          if ( !v42 )
            goto LABEL_27;
          v41 = v43[1];
          v23 = v41 < (unsigned int)parent_name[1];
          if ( v41 != parent_name[1] )
            break;
          v43 += 2;
          parent_name += 2;
          if ( !v41 )
          {
LABEL_27:
            v40 = 0;
            goto LABEL_29;
          }
        }
        v40 = -v23 - (v23 - 1);
LABEL_29:
        v39 = v40;
        if ( !v40 )
        {
          rf_vector3_default_construct_noop(v80);
          rf_matrix3_construct((char *)v77);
          rf_model_handle_get_node_transform(v62, v80, v77, v81);
          rf_scene_definition_decode_flat_object_index(*((_DWORD **)v62 + 2), v81, &v78, &v76, &v79);
          if ( v78 )
          {
            rf_vector_subtract_in_place(v80, destination);
            v38 = 1;
            *(float *)&v37 = a16;
            v36 = a15;
            rf_matrix3_copy_construct((int)&v27, v77);
            rf_vector3_copy_return_destination(&v24, v80);
            rf_model_handle_set_node_transform_by_value(
              v62,
              v81,
              v24,
              v25,
              v26,
              v27,
              v28,
              v29,
              v30,
              v31,
              v32,
              v33,
              v34,
              v35,
              v36,
              *(float *)&v37,
              v38);
          }
          else
          {
            v38 = 1;
            *(float *)&v37 = a16;
            v36 = a15;
            rf_matrix3_copy_construct((int)&v27, v77);
            rf_vector_negate(destination, &v24);
            rf_model_handle_set_node_transform_by_value(
              v62,
              v81,
              v24,
              v25,
              v26,
              v27,
              v28,
              v29,
              v30,
              v31,
              v32,
              v33,
              v34,
              v35,
              v36,
              *(float *)&v37,
              v38);
          }
        }
      }
      result = ++v81;
    }
  }
  return result;
}

