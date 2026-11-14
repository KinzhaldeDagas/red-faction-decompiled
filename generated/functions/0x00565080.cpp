// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565080 rf_model_handle_set_node_transform_adapter_by_value
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl17stack words:handle,index,positionXYZ3floats,matrix9floats,ancestorCount,falloff,propagateByte. Copies by-value position/matrix through locals then forwards corrected thiscall562EB0 with identical payload. No pointer-to-matrix ABI, phantom EDX, or scene hierarchy validation; return raw delegate bits.
unsigned int __cdecl rf_model_handle_set_node_transform_adapter_by_value(
        void *a1,
        int a2,
        float a3,
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
  float v18[3]; // [esp-34h] [ebp-48h] BYREF
  float v19[9]; // [esp-28h] [ebp-3Ch] BYREF
  int v20; // [esp-4h] [ebp-18h]
  float v21; // [esp+0h] [ebp-14h]
  int v22; // [esp+4h] [ebp-10h]
  void *v23; // [esp+10h] [ebp-4h]

  v23 = a1;
  v22 = a17;
  v21 = a16;
  v20 = a15;
  rf_matrix3_copy_construct((int)v19, &a6);
  rf_vector3_copy_return_destination(v18, &a3);
  return rf_model_handle_set_node_transform_by_value(
           v23,
           a2,
           v18[0],
           v18[1],
           v18[2],
           v19[0],
           v19[1],
           v19[2],
           v19[3],
           v19[4],
           v19[5],
           v19[6],
           v19[7],
           v19[8],
           v20,
           v21,
           v22);
}

