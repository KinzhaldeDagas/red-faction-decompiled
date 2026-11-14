// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419A70 rf_glare_create_at_position_direction
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl(position pointer,direction pointer,definitionIndex). Signed index outside[0,globalCount) returns0. Constructs partially initialized152-byte object setup: mass+20=1, radius+132=0.1, model+0=0,flags+148=0, position+60 copied, orientation+72 built from direction (helper preserves raw nonvertical forward length). Creates type10 with UID/context -1, common creation flags0x30000, final arg0; destroys local setup on success/failure. Success stores definition pointer+684/index+688, DWORD+656=-1,+660/+664=0, clears floats+668/+672/+676/+680, +716/+692=0, sets BOTH bytes+652/+653=1, appends to glare intrusive tail using links+696/+700, writes vector+704=(-1000,-1000,-1000) and zeroes endpoints+724/+736. Does
// not explicitly initialize byte+720 or fields+512/+516. No null direction/position, index<=63, finite or allocation rollback beyond local cleanup; no blanket setup memset.
int __cdecl rf_glare_create_at_position_direction(float *source, int a2, int a3)
{
  float *v4; // eax
  int v5; // [esp+10h] [ebp-D8h]
  float v6[3]; // [esp+14h] [ebp-D4h] BYREF
  float v7[3]; // [esp+20h] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-B8h] BYREF
  void *v9[15]; // [esp+3Ch] [ebp-ACh] BYREF
  float destination[3]; // [esp+78h] [ebp-70h] BYREF
  float v11[20]; // [esp+84h] [ebp-64h] BYREF
  int i; // [esp+D4h] [ebp-14h]
  int v13; // [esp+D8h] [ebp-10h]
  int v14; // [esp+E4h] [ebp-4h]

  if ( a3 < 0 || a3 >= dword_680AE0 )
    return 0;
  rf_object_setup152_construct_members((char *)v9);
  v14 = 0;
  *(float *)&v9[5] = 1.0;
  v11[15] = 0.1;
  rf_vector_copy(destination, copy_result, source);
  rf_orientation_matrix_from_direction(v11, a2);
  v11[19] = 0.0;
  v9[0] = nullptr;
  v13 = rf_object_create(10, -1, -1, (int)v9, 196608, 0);
  if ( v13 )
  {
    *(_DWORD *)(v13 + 688) = a3;
    *(_DWORD *)(v13 + 684) = &byte_680DD8[52 * a3];
    *(_DWORD *)(v13 + 656) = -1;
    *(_DWORD *)(v13 + 660) = 0;
    *(_DWORD *)(v13 + 664) = 0;
    for ( i = 0; i < 2; ++i )
    {
      *(float *)(v13 + 4 * i + 668) = 0.0;
      *(float *)(v13 + 4 * i + 676) = 0.0;
    }
    *(_DWORD *)(v13 + 716) = 0;
    *(_DWORD *)(v13 + 692) = 0;
    *(_BYTE *)(v13 + 652) = 1;
    *(_BYTE *)(v13 + 653) = 1;
    *(_DWORD *)(v13 + 700) = unk_680DA4;
    *(_DWORD *)(v13 + 696) = &unk_680AE8;
    *(_DWORD *)(unk_680DA4 + 696) = v13;
    unk_680DA4 = v13;
    v4 = rf_vector3_set_components_return_destination(v7, -1000.0, -1000.0, -1000.0);
    rf_vector_copy((float *)(v13 + 704), v6, v4);
    rf_vector3_zero_return_destination((float *)(v13 + 724));
    rf_vector3_zero_return_destination((float *)(v13 + 736));
    v5 = v13;
    v14 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return v5;
  }
  else
  {
    v14 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return 0;
  }
}

