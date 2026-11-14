// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050BD40 rf_weapon_create_impact_decal
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Corrected first argument to integer weapon index; return is an untyped pointer/EAX residue, not float-vector ownership. All five native calls across3callers push seven DWORD arguments and ADD ESP28; no local caller tests returned pointer. One presenter path immediately returns, forwarding incidental AL, so a void-result claim is not established. Arguments(index,position,incomingDirection,normal,object UID,ricochet BYTE,glass BYTE). Requires signed0<=index<global911C68. Any nonzero ricochet byte has precedence: bitmap+644/dimensions+648; else nonzero glass uses1172/1176; else ordinary1156/1160. Negative selected bitmap exits. Constructs descriptor525110
// (position0,basis12,dimensions48,bitmap60,owner64,alpha68=255,flags72,extra76,context80). Resolved object type+36 EXACT9 first attempts projection on object context+660: point=position+normal*F32(0.001), subtract object position and inverse-rotate; copy/inverse-rotate/unchecked-normalize supplied normal to build basis; dimensions/bitmap selected, owner64=0,flags4,extra=object UID+44, scalar1. Calls523FE0 with alpha BYTE as UNUSED sixth argument (callee forces255), clears global face candidates via callee. Then ALWAYS sets context80=world solid and flags72=100h. Successful first projection copies returned record position/basis directly and ORs2; failed/no-object projection uses offset contact point: ricochet normalizes incoming direction, rejects normal component, builds basis from -normal/up hint and ORs2; ordinary/glass basis from normal and ORs4. Resolves room against WORLD solid using
// zero vector and final point, assigns descriptor owner64, selected dimensions/bitmap, submits521910 once. Existing projected record is not freed here; success does not skip second submit. Descriptor scalar+84 is NEVER initialized by525110 or this function before521910 reads/forwards it; do not assume1 or zero. No source-vector mutation, normal-length/finite/NULL guards, bitmap load or reliable return pointer on skipped paths.
void *__cdecl rf_weapon_create_impact_decal(
        int weapon_index,
        const float *position,
        const float *incoming_direction,
        const float *normal,
        int object_uid,
        char ricochet,
        char glass)
{
  void *result; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float v15[3]; // [esp+14h] [ebp-150h] BYREF
  float v16[3]; // [esp+20h] [ebp-144h] BYREF
  float v17[3]; // [esp+2Ch] [ebp-138h] BYREF
  float v18[3]; // [esp+38h] [ebp-12Ch] BYREF
  float v19[3]; // [esp+44h] [ebp-120h] BYREF
  float v20[3]; // [esp+50h] [ebp-114h] BYREF
  float v21[3]; // [esp+5Ch] [ebp-108h] BYREF
  float v22[3]; // [esp+68h] [ebp-FCh] BYREF
  float v23[3]; // [esp+74h] [ebp-F0h] BYREF
  float v24[3]; // [esp+80h] [ebp-E4h] BYREF
  float sum_result[3]; // [esp+8Ch] [ebp-D8h] BYREF
  float scaled_result[3]; // [esp+98h] [ebp-CCh] BYREF
  float v27[3]; // [esp+A4h] [ebp-C0h] BYREF
  float v28[3]; // [esp+B0h] [ebp-B4h] BYREF
  float copy_result[3]; // [esp+BCh] [ebp-A8h] BYREF
  float v30[3]; // [esp+C8h] [ebp-9Ch] BYREF
  float v31[3]; // [esp+D4h] [ebp-90h] BYREF
  float v32[3]; // [esp+E0h] [ebp-84h] BYREF
  int v33; // [esp+ECh] [ebp-78h]
  float destination[3]; // [esp+F0h] [ebp-74h] BYREF
  int v35; // [esp+FCh] [ebp-68h]
  char *v36; // [esp+100h] [ebp-64h]
  float v37[3]; // [esp+104h] [ebp-60h] BYREF
  float v38[9]; // [esp+110h] [ebp-54h] BYREF
  float v39[3]; // [esp+134h] [ebp-30h] BYREF
  int v40; // [esp+140h] [ebp-24h]
  void *v41; // [esp+144h] [ebp-20h]
  unsigned __int8 v42; // [esp+148h] [ebp-1Ch]
  int v43; // [esp+14Ch] [ebp-18h]
  int v44; // [esp+150h] [ebp-14h]
  int v45; // [esp+154h] [ebp-10h]
  int v46; // [esp+15Ch] [ebp-8h]
  float *source; // [esp+160h] [ebp-4h]

  rf_decal_parameter_record_construct((int)v37);
  result = rf_vector3_default_construct_noop(destination);
  if ( weapon_index >= 0 )
  {
    result = (void *)weapon_index;
    if ( weapon_index < dword_911C68 )
    {
      v36 = (char *)&rf_weapon_records + 1360 * weapon_index;
      if ( ricochet )
      {
        v46 = *((_DWORD *)v36 + 161);
        result = rf_vector_copy(destination, copy_result, (const float *)v36 + 162);
      }
      else if ( glass )
      {
        v46 = *((_DWORD *)v36 + 293);
        result = rf_vector_copy(destination, v28, (const float *)v36 + 294);
      }
      else
      {
        v46 = *((_DWORD *)v36 + 289);
        result = rf_vector_copy(destination, v27, (const float *)v36 + 290);
      }
      if ( v46 >= 0 )
      {
        v35 = rf_object_resolve_handle(object_uid);
        source = nullptr;
        if ( v35 && *(_DWORD *)(v35 + 36) == 9 )
        {
          v33 = v35;
          v45 = *(_DWORD *)(v35 + 660);
          v8 = rf_vector_multiply_scalar(normal, scaled_result, 0.001);
          v9 = rf_vector_add(position, sum_result, v8);
          rf_vector_copy(v37, v24, v9);
          v41 = nullptr;
          v10 = rf_vector_negate((float *)normal, v23);
          rf_orientation_matrix_from_direction(v38, (int)v10);
          rf_vector_copy(v39, v22, destination);
          v40 = v46;
          v44 = *(_DWORD *)(v33 + 44);
          v43 = 4;
          rf_vector_subtract_in_place(v37, (float *)(v33 + 60));
          rf_matrix3_inverse_rotate_vector(v37, (float *)(v33 + 72));
          rf_vector3_copy_return_destination(v32, (float *)normal);
          rf_matrix3_inverse_rotate_vector(v32, (float *)(v33 + 72));
          rf_vector_normalize_reciprocal_sqrt(v32);
          rf_orientation_matrix_from_direction(v38, (int)v32);
          source = (float *)rf_decal_project_unowned_and_clear_face_candidates(
                              v45,
                              (int)v37,
                              (int)v38,
                              v39,
                              v40,
                              v42,
                              v43,
                              v44,
                              1.0);
        }
        v45 = rf_world_solid;
        v43 = 256;
        if ( source )
        {
          rf_vector_copy(v37, v21, source);
          rf_matrix3_copy(v38, source + 3);
          v43 |= 2u;
        }
        else
        {
          v11 = rf_vector_multiply_scalar(normal, v20, 0.001);
          v12 = rf_vector_add(position, v19, v11);
          rf_vector_copy(v37, v18, v12);
          if ( ricochet )
          {
            rf_vector3_default_construct_noop(v30);
            rf_vector3_copy_return_destination(v31, (float *)incoming_direction);
            rf_vector_normalize_reciprocal_sqrt(v31);
            rf_vector_reject_component_along_normal(v30, (int)v31, (int)normal);
            v13 = rf_vector_negate((float *)normal, v17);
            rf_orientation_from_forward_and_up_hint(v38, v13, v30);
            v43 |= 2u;
          }
          else
          {
            rf_orientation_matrix_from_direction(v38, (int)normal);
            v43 |= 4u;
          }
        }
        v14 = rf_vector3_set_components_return_destination(v16, 0.0, 0.0, 0.0);
        v41 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v14, v37, 0);
        rf_vector_copy(v39, v15, destination);
        v40 = v46;
        return rf_impact_decal_world_submit((int)v37);
      }
    }
  }
  return result;
}

