// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00585C50 rf_character_instance_resolve_node_transform
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Thiscall output48-byte affine and signed node index. Negative index gives identity. Primary bone index<count+72: cached epochWORD at instance+5012+48*i compared to instance+7416; matching epoch copies matrix instance+48*i. Otherwise builds byte ancestor chain in local52-byte regions, reverses it and calls pose evaluator before copying. Auxiliary tier subtracts bone count, uses binding source parent DWORD at base+4848+56*i, recursively resolves parent and composes binding affine+4800+56*i. Geometry tier subtracts binding count, follows selected-mesh->LOD table->descriptor, takes100-byte record quaternion+68/position+84/parent+96, recursively composes. Out-of-range final tier yields identity. Returns output. No cycle,
// chain-length, index truncation or pointer-chain validation; forward recursion can fail on malformed parents.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Character node resolver: negative node index returns identity affine (zero model position); nonnegative primary indices read current instance pose affine, not a camera anchor/nearest bone/bind-pose heuristic.43FBF0 ignores43ECF0 replacement binding failure, so missing replacement indices are not the strict43E970 allocation gate. Host unsupported model tags/invalid positive indices require explicit boundary, not a fabricated bind fallback.
void *__thiscall rf_character_instance_resolve_node_transform(int this, void *a2, int a3)
{
  float *v3; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // [esp+Ch] [ebp-188h]
  float *v9; // [esp+Ch] [ebp-188h]
  float *v10; // [esp+10h] [ebp-184h]
  float *v11; // [esp+10h] [ebp-184h]
  float *v12; // [esp+14h] [ebp-180h]
  float *v13; // [esp+14h] [ebp-180h]
  char v15[48]; // [esp+24h] [ebp-170h] BYREF
  char v16[48]; // [esp+54h] [ebp-140h] BYREF
  float v17[3]; // [esp+84h] [ebp-110h] BYREF
  float v18[3]; // [esp+90h] [ebp-104h] BYREF
  float v19[3]; // [esp+9Ch] [ebp-F8h] BYREF
  float v20[3]; // [esp+A8h] [ebp-ECh] BYREF
  float v21[3]; // [esp+B4h] [ebp-E0h] BYREF
  float v22[3]; // [esp+C0h] [ebp-D4h] BYREF
  float v23[3]; // [esp+CCh] [ebp-C8h] BYREF
  float v24[3]; // [esp+D8h] [ebp-BCh] BYREF
  char v25[48]; // [esp+E4h] [ebp-B0h] BYREF
  int v26; // [esp+114h] [ebp-80h]
  int v27; // [esp+118h] [ebp-7Ch]
  int v28; // [esp+11Ch] [ebp-78h]
  int i; // [esp+120h] [ebp-74h]
  _BYTE v30[104]; // [esp+124h] [ebp-70h] BYREF
  int j; // [esp+190h] [ebp-4h]
  int v32; // [esp+1A0h] [ebp+Ch]
  int v33; // [esp+1A0h] [ebp+Ch]

  if ( a3 >= 0 )
  {
    if ( a3 < *(_DWORD *)(*(_DWORD *)(this + 7504) + 72) )
    {
      if ( *(unsigned __int16 *)(this + 48 * a3 + 5012) == *(unsigned __int16 *)(this + 7416) )
      {
        qmemcpy(a2, (const void *)(this + 48 * a3), 0x30u);
        return a2;
      }
      else
      {
        v28 = 0;
        for ( i = a3; i > -1; i = *(_DWORD *)(*(_DWORD *)(this + 7504) + 76 * i + 148) )
          v30[v28++ + 52] = i;
        for ( j = 0; j < v28; ++j )
          v30[j] = v30[v28 - 1 - j + 52];
        rf_character_instance_evaluate_pose(v28, (int)v30, this);
        qmemcpy(a2, (const void *)(this + 48 * a3), 0x30u);
        return a2;
      }
    }
    else
    {
      v32 = a3 - *(_DWORD *)(*(_DWORD *)(this + 7504) + 72);
      if ( v32 < *(_DWORD *)(*(_DWORD *)(this + 7504) + 4792) )
      {
        v7 = (float *)rf_character_instance_resolve_node_transform(
                        this,
                        v15,
                        *(_DWORD *)(*(_DWORD *)(this + 7504) + 56 * v32 + 4848));
        rf_matrix43_compose_parent_local((float *)(*(_DWORD *)(this + 7504) + 56 * v32 + 4800), (float *)a2, v7);
        return a2;
      }
      else
      {
        v33 = v32 - *(_DWORD *)(*(_DWORD *)(this + 7504) + 4792);
        v27 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 7504) + 6736) + 140) + 4);
        if ( v33 < *(_DWORD *)(v27 + 20) )
        {
          v26 = *(_DWORD *)(v27 + 16) + 100 * v33;
          rf_affine3x4_default_construct_noop(v25);
          rf_affine3x4_set_quaternion_translation((float *)v25, (float *)(v26 + 68), (float *)(v26 + 84));
          v6 = (float *)rf_character_instance_resolve_node_transform(this, v16, *(_DWORD *)(v26 + 96));
          rf_matrix43_compose_parent_local((float *)v25, (float *)a2, v6);
        }
        else
        {
          v13 = rf_vector3_set_components_return_destination(v20, 0.0, 0.0, 0.0);
          v11 = rf_vector3_set_components_return_destination(v19, 0.0, 0.0, 1.0);
          v9 = rf_vector3_set_components_return_destination(v18, 0.0, 1.0, 0.0);
          v5 = rf_vector3_set_components_return_destination(v17, 1.0, 0.0, 0.0);
          rf_affine3x4_set_rows_translation((float *)a2, v5, v9, v11, v13);
        }
        return a2;
      }
    }
  }
  else
  {
    v12 = rf_vector3_set_components_return_destination(v24, 0.0, 0.0, 0.0);
    v10 = rf_vector3_set_components_return_destination(v23, 0.0, 0.0, 1.0);
    v8 = rf_vector3_set_components_return_destination(v22, 0.0, 1.0, 0.0);
    v3 = rf_vector3_set_components_return_destination(v21, 1.0, 0.0, 0.0);
    rf_affine3x4_set_rows_translation((float *)a2, v3, v8, v10, v12);
    return a2;
  }
}

