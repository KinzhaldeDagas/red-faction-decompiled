// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052FF30 rf_solid_sweep_query_in_selected_room
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall solid,query,result,room RET12 void. Increment global query serial FIRST, clear result DWORD0,32,36 even on early exits. Continue only when solid face-list count116!=0 and squared length of original delta query64 is nonzero or unorderedNaN; exact zero exits. Query flags80&4: copy original start52/delta64 to internal84/96 directly. Otherwise internal start=Mrows16*(start52-origin4); compute transformed end=Mrows16*(start52+delta64-origin4), then internal delta=end-internalStart, with F32 vector stores at each step. Call52EF90(room.root60,query,result), ignore nominal return. No roomNULL guard, room-bound/visibility filter, cache build or bounds update; empty solid count
// suppresses even a nonempty supplied room tree. Does not clear every result field or normalize matrix/radius.
void __thiscall rf_solid_sweep_query_in_selected_room(char *this, int a2, _DWORD *a3, int a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v9[3]; // [esp+4h] [ebp-A0h] BYREF
  float v10[3]; // [esp+10h] [ebp-94h] BYREF
  float v11[3]; // [esp+1Ch] [ebp-88h] BYREF
  float v12[3]; // [esp+28h] [ebp-7Ch] BYREF
  float sum_result[3]; // [esp+34h] [ebp-70h] BYREF
  float v14[3]; // [esp+40h] [ebp-64h] BYREF
  float v15[3]; // [esp+4Ch] [ebp-58h] BYREF
  float v16[3]; // [esp+58h] [ebp-4Ch] BYREF
  float out_vector[3]; // [esp+64h] [ebp-40h] BYREF
  float v18[3]; // [esp+70h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+7Ch] [ebp-28h] BYREF
  float lhs[3]; // [esp+88h] [ebp-1Ch] BYREF
  float destination[3]; // [esp+94h] [ebp-10h] BYREF
  float v22; // [esp+A0h] [ebp-4h]

  ++rf_collision_query_serial;
  *a3 = 0;
  a3[8] = 0;
  a3[9] = 0;
  if ( rf_shared_second_dword_getter_518050((_DWORD *)this + 28) )
  {
    v22 = rf_vector_length_squared((float *)(a2 + 64));
    if ( v22 != 0.0 )
    {
      if ( (*(_DWORD *)(a2 + 80) & 4) != 0 )
      {
        rf_vector_copy((float *)(a2 + 84), copy_result, (const float *)(a2 + 52));
        rf_vector_copy((float *)(a2 + 96), v18, (const float *)(a2 + 64));
      }
      else
      {
        rf_vector3_default_construct_noop(destination);
        v4 = rf_vector_subtract((const float *)(a2 + 52), out_vector, (const float *)(a2 + 4));
        rf_vector_copy(destination, v16, v4);
        v5 = rf_vector3_transform_by_matrix_rows(destination, v15, (float *)(a2 + 16));
        rf_vector_copy((float *)(a2 + 84), v14, v5);
        v6 = rf_vector_add((const float *)(a2 + 52), sum_result, (const float *)(a2 + 64));
        v7 = rf_vector_subtract(v6, v12, (const float *)(a2 + 4));
        rf_vector_copy(destination, v11, v7);
        rf_vector3_transform_by_matrix_rows(destination, lhs, (float *)(a2 + 16));
        v8 = rf_vector_subtract(lhs, v10, (const float *)(a2 + 84));
        rf_vector_copy((float *)(a2 + 96), v9, v8);
      }
      rf_collision_spatial_tree_sweep_faces(*(void **)(a4 + 60), a2, (int)a3);
    }
  }
}

