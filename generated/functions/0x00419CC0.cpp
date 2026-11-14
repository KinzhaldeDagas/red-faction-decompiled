// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419CC0 rf_glare_create_attached_to_model_prop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl(ownerHandle,propIndex,definitionIndex,lowByteFlag). Signed definition range check only. Builds partially initialized152-byte setup with mass1, radius=max(definition Height+40,Length+44),flags0,model0; resolves owner WITHOUT null check and composes prop world matrix/position from owner model+128/common transform. Creates type10 with owner context and flags0x30000. Success performs shared glare field initialization (definition+684/index+688, -1 at+656, zeros+660/+664 and four per-player floats+668..680, +716/+692=0, byte+652=1), stores owner/prop at this TYPE10 layout+512/+516, ORs runtime flags+692 mask2 for nonzero fourth argument BYTE, appends links+696/+700, sentinel vector+704=-1000, byte+720=0,
// zero endpoints+724/+736. Does not explicitly set byte+653. Local setup is destroyed on all normal exits. These type-specific+512/+516 writes do not establish entity-owner layout semantics elsewhere.
int __cdecl rf_glare_create_attached_to_model_prop(int a1, int a2, int a3, char a4)
{
  float *v5; // eax
  int v6; // [esp+10h] [ebp-D4h]
  float copy_result[3]; // [esp+14h] [ebp-D0h] BYREF
  float v8[3]; // [esp+20h] [ebp-C4h] BYREF
  char *v9; // [esp+30h] [ebp-B4h]
  int v10; // [esp+34h] [ebp-B0h]
  void *v11[15]; // [esp+38h] [ebp-ACh] BYREF
  float v12[3]; // [esp+74h] [ebp-70h] BYREF
  char v13[60]; // [esp+80h] [ebp-64h] BYREF
  float v14; // [esp+BCh] [ebp-28h]
  int v15; // [esp+CCh] [ebp-18h]
  int i; // [esp+D0h] [ebp-14h]
  int v17; // [esp+D4h] [ebp-10h]
  int v18; // [esp+E0h] [ebp-4h]

  if ( a3 < 0 || a3 >= dword_680AE0 )
    return 0;
  v9 = &byte_680DD8[52 * a3];
  rf_object_setup152_construct_members((char *)v11);
  v18 = 0;
  *(float *)&v11[5] = 1.0;
  v14 = rf_float_maximum_two_values(*((float *)v9 + 10), *((float *)v9 + 11));
  v15 = 0;
  v11[0] = nullptr;
  v10 = rf_object_resolve_handle(a1);
  rf_vmesh_compose_prop_world_transform(*(_DWORD *)(v10 + 128), a2, (float *)(v10 + 72), v10 + 60, (int)v13, v12);
  v17 = rf_object_create(10, -1, a1, (int)v11, 196608, 0);
  if ( v17 )
  {
    *(_DWORD *)(v17 + 688) = a3;
    *(_DWORD *)(v17 + 684) = v9;
    *(_DWORD *)(v17 + 656) = -1;
    *(_DWORD *)(v17 + 660) = 0;
    *(_DWORD *)(v17 + 664) = 0;
    for ( i = 0; i < 2; ++i )
    {
      *(float *)(v17 + 4 * i + 668) = 0.0;
      *(float *)(v17 + 4 * i + 676) = 0.0;
    }
    *(_DWORD *)(v17 + 716) = 0;
    *(_DWORD *)(v17 + 512) = a1;
    *(_DWORD *)(v17 + 516) = a2;
    *(_DWORD *)(v17 + 692) = 0;
    *(_BYTE *)(v17 + 652) = 1;
    if ( a4 )
      *(_DWORD *)(v17 + 692) |= 2u;
    *(_DWORD *)(v17 + 700) = unk_680DA4;
    *(_DWORD *)(v17 + 696) = &unk_680AE8;
    *(_DWORD *)(unk_680DA4 + 696) = v17;
    unk_680DA4 = v17;
    v5 = rf_vector3_set_components_return_destination(v8, -1000.0, -1000.0, -1000.0);
    rf_vector_copy((float *)(v17 + 704), copy_result, v5);
    *(_BYTE *)(v17 + 720) = 0;
    rf_vector3_zero_return_destination((float *)(v17 + 724));
    rf_vector3_zero_return_destination((float *)(v17 + 736));
    v6 = v17;
    v18 = -1;
    rf_object_setup152_destroy_array_backing(v11);
    return v6;
  }
  else
  {
    v18 = -1;
    rf_object_setup152_destroy_array_backing(v11);
    return 0;
  }
}

