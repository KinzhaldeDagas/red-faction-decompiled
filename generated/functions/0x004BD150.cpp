// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD150 rf_object_copy_node_or_common_world_position
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl(object,outPosition), AL bool identifies branch, not guaranteed backend success. Node index620==-1 copies common position60 and returns0. ANY other index invokes model node-transform adapter(model128,outPosition,temporaryMatrix,index), ignores returned result, then rotates/translates outPosition by common matrix72/position60 and returns1. Temporary matrix constructor is NO-WRITE and destination is not preinitialized for delegate; a model kind whose adapter leaves outputs untouched can therefore transform prior destination data. No model/null/index range/finite guard, output clearing or physics pose update.
char __cdecl rf_object_copy_node_or_common_world_position(int a1, float *destination)
{
  float copy_result[3]; // [esp+0h] [ebp-30h] BYREF
  char v4[36]; // [esp+Ch] [ebp-24h] BYREF

  if ( *(_DWORD *)(a1 + 620) == -1 )
  {
    rf_vector_copy(destination, copy_result, (const float *)(a1 + 60));
    return 0;
  }
  else
  {
    rf_matrix3_construct(v4);
    rf_model_handle_get_node_transform_adapter(*(_DWORD *)(a1 + 128), (int)destination, (int)v4, *(_DWORD *)(a1 + 620));
    rf_vector_rotate_translate_in_place(destination, a1 + 60, a1 + 72);
    return 1;
  }
}

