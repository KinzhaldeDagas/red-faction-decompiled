// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00430150 rf_entity_build_sequential_interface_node_relations
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity), void. Construct RFString prefix interface_, local counter0; form decimal(counter+1), concatenate, lookup node on entity
// model128. WHILE node result SIGNED>=0 (all negative values terminate, not only-1), allocate RAW8-byte record via scalar operator new and append pointer to entity array2252 BEFORE
// initialization. Ignore append returned old index; instead access array[counter] twice and write node DWORD0 then full handle DWORD1=-1, increment local counter, lookup next
// interface_(counter+1), stop first missing/negative node. No count reset, starting-index capture, gap scan, explicit item cap or duplicate detection. Assumes array was empty:
// preexisting entries at local zero-based indices are overwritten while newly appended records can remain uninitialized. No allocation-null check, record constructor, model validity
// check or rollback. If allocation/append/later string/lookup fails after prior publications, partial records/count persist; raw allocation is not protected by a per-record unwind
// owner. Normal temporary cleanup destroys concat then decimal strings each round and prefix last. Native SEH five-state map6587C0 cleans ONLY string temporaries/prefix
// through622D04/0C/14/1C/24, not entity array or appended records. No entity relation reciprocal update, target resolution or success count returned.
void __cdecl rf_entity_build_sequential_interface_node_relations(int a1)
{
  char *v1; // eax
  int **v2; // eax
  char *v3; // eax
  std::exception *v4; // [esp+4h] [ebp-60h]
  _DWORD *v5; // [esp+Ch] [ebp-58h]
  std::exception *v6; // [esp+14h] [ebp-50h]
  _DWORD *v7; // [esp+1Ch] [ebp-48h]
  _BYTE v8[8]; // [esp+24h] [ebp-40h] BYREF
  _DWORD v9[2]; // [esp+2Ch] [ebp-38h] BYREF
  void *v10; // [esp+34h] [ebp-30h]
  _BYTE v11[8]; // [esp+38h] [ebp-2Ch] BYREF
  _DWORD v12[2]; // [esp+40h] [ebp-24h] BYREF
  int v13[2]; // [esp+48h] [ebp-1Ch] BYREF
  int v14; // [esp+50h] [ebp-14h]
  int node_adapter; // [esp+54h] [ebp-10h]
  int v16; // [esp+60h] [ebp-4h]

  rf_string_construct_from_cstr(v13, "interface_");
  v16 = 0;
  v14 = 0;
  v7 = rf_string_format_int32_decimal(v12, 1);
  LOBYTE(v16) = 1;
  v6 = (std::exception *)rf_string_concat_two_objects(v11, v13, (int)v7);
  LOBYTE(v16) = 2;
  v1 = (char *)rf_string_object_c_str_or_empty(v6);
  node_adapter = rf_model_handle_find_node_adapter(*(_DWORD *)(a1 + 128), v1);
  LOBYTE(v16) = 1;
  rf_string_destroy_buffer(v11);
  LOBYTE(v16) = 0;
  rf_string_destroy_buffer(v12);
  while ( node_adapter >= 0 )
  {
    v10 = operator new(8u);
    rf_pointer_array_append_dword((_DWORD *)(a1 + 2252), (int)v10);
    v2 = (int **)sub_552200((_DWORD *)(a1 + 2252), v14);
    **v2 = node_adapter;
    *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 2252), v14++) + 4) = -1;
    v5 = rf_string_format_int32_decimal(v9, v14 + 1);
    LOBYTE(v16) = 3;
    v4 = (std::exception *)rf_string_concat_two_objects(v8, v13, (int)v5);
    LOBYTE(v16) = 4;
    v3 = (char *)rf_string_object_c_str_or_empty(v4);
    node_adapter = rf_model_handle_find_node_adapter(*(_DWORD *)(a1 + 128), v3);
    LOBYTE(v16) = 3;
    rf_string_destroy_buffer(v8);
    LOBYTE(v16) = 0;
    rf_string_destroy_buffer(v9);
  }
  v16 = -1;
  rf_string_destroy_buffer(v13);
}

