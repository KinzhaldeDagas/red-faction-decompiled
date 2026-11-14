// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419FA0 rf_glare_create_between_model_props
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl(ownerHandle,definitionIndex,firstProp,secondProp), signed definition range check. Resolves owner without null guard; composes both prop transforms, retaining SECOND prop orientation in setup and both endpoint positions. Setup position is first+0.5*(second-first), with native float-vector stores, mass1,radius=max(defHeight,defLength),model0,flags0; no whole-setup initialization. Creates type10 with context -1 and flags0x30000. Success copies endpoints to+724/+736; shared glare fields are initialized as in attached factory, but writes owner handle to common+48 and prop+516=-1 (no explicit+512 store), byte+652=1,+720=1; byte+653 is not written. Appends intrusive list and sentinel vector+704=-1000.
// Destroys local setup on failure/success. No prop/owner validity, finite-value or endpoint-distance guard; backend transform results are not checked.
int __cdecl rf_glare_create_between_model_props(int a1, int a2, int a3, int a4)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  int v9; // [esp+10h] [ebp-134h]
  float v10[3]; // [esp+14h] [ebp-130h] BYREF
  float v11[3]; // [esp+20h] [ebp-124h] BYREF
  float v12[3]; // [esp+2Ch] [ebp-118h] BYREF
  float v13[3]; // [esp+38h] [ebp-10Ch] BYREF
  float copy_result[3]; // [esp+48h] [ebp-FCh] BYREF
  float sum_result[3]; // [esp+54h] [ebp-F0h] BYREF
  float scaled_result[3]; // [esp+60h] [ebp-E4h] BYREF
  float out_vector[3]; // [esp+6Ch] [ebp-D8h] BYREF
  int v18; // [esp+78h] [ebp-CCh]
  char *v19; // [esp+7Ch] [ebp-C8h]
  void *v20[15]; // [esp+80h] [ebp-C4h] BYREF
  float destination[3]; // [esp+BCh] [ebp-88h] BYREF
  _BYTE v22[60]; // [esp+C8h] [ebp-7Ch] BYREF
  float v23; // [esp+104h] [ebp-40h]
  int v24; // [esp+114h] [ebp-30h]
  float rhs[3]; // [esp+118h] [ebp-2Ch] BYREF
  int i; // [esp+124h] [ebp-20h]
  int v27; // [esp+128h] [ebp-1Ch]
  float lhs[3]; // [esp+12Ch] [ebp-18h] BYREF
  int v29; // [esp+140h] [ebp-4h]

  if ( a2 < 0 || a2 >= dword_680AE0 )
    return 0;
  v19 = &byte_680DD8[52 * a2];
  rf_object_setup152_construct_members((char *)v20);
  v29 = 0;
  *(float *)&v20[5] = 1.0;
  v23 = rf_float_maximum_two_values(*((float *)v19 + 10), *((float *)v19 + 11));
  v24 = 0;
  v20[0] = nullptr;
  v18 = rf_object_resolve_handle(a1);
  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(lhs);
  rf_vmesh_compose_prop_world_transform(*(_DWORD *)(v18 + 128), a3, (float *)(v18 + 72), v18 + 60, (int)v22, rhs);
  rf_vmesh_compose_prop_world_transform(*(_DWORD *)(v18 + 128), a4, (float *)(v18 + 72), v18 + 60, (int)v22, lhs);
  v5 = rf_vector_subtract(lhs, out_vector, rhs);
  v6 = rf_vector_multiply_scalar(v5, scaled_result, 0.5);
  v7 = rf_vector_add(rhs, sum_result, v6);
  rf_vector_copy(destination, copy_result, v7);
  v27 = rf_object_create(10, -1, -1, (int)v20, 196608, 0);
  if ( v27 )
  {
    rf_vector_copy((float *)(v27 + 724), v13, rhs);
    rf_vector_copy((float *)(v27 + 736), v12, lhs);
    *(_DWORD *)(v27 + 656) = -1;
    *(_DWORD *)(v27 + 660) = 0;
    *(_DWORD *)(v27 + 664) = 0;
    *(_DWORD *)(v27 + 688) = a2;
    *(_DWORD *)(v27 + 684) = v19;
    for ( i = 0; i < 2; ++i )
    {
      *(float *)(v27 + 4 * i + 668) = 0.0;
      *(float *)(v27 + 4 * i + 676) = 0.0;
    }
    *(_DWORD *)(v27 + 48) = a1;
    *(_DWORD *)(v27 + 516) = -1;
    *(_DWORD *)(v27 + 692) = 0;
    *(_BYTE *)(v27 + 652) = 1;
    *(_DWORD *)(v27 + 700) = unk_680DA4;
    *(_DWORD *)(v27 + 696) = &unk_680AE8;
    *(_DWORD *)(unk_680DA4 + 696) = v27;
    unk_680DA4 = v27;
    v8 = rf_vector3_set_components_return_destination(v11, -1000.0, -1000.0, -1000.0);
    rf_vector_copy((float *)(v27 + 704), v10, v8);
    *(_BYTE *)(v27 + 720) = 1;
    v9 = v27;
    v29 = -1;
    rf_object_setup152_destroy_array_backing(v20);
    return v9;
  }
  else
  {
    v29 = -1;
    rf_object_setup152_destroy_array_backing(v20);
    return 0;
  }
}

