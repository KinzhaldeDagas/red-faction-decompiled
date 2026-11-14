// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CC70 rf_world_face_copy_prefix96
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Thiscall destination/source face. Copies plane0..15,vector3 at16,vector3 at28,DWORDs40..79,WORD80..81,DWORDs84/88/92;returns destination. Padding82..83 and bytes96+ untouched. All linked-list/material/source pointers copied shallowly,no vertex duplication. Derived-face builder separately initializes association at96 and replaces corner-ring64;not a complete100-byte memcpy.
int __thiscall rf_world_face_copy_prefix96(int this, int a2)
{
  float v4[3]; // [esp+8h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+14h] [ebp-10h] BYREF
  unsigned int i; // [esp+20h] [ebp-4h]

  rf_plane_copy((float *)this, (float *)a2);
  rf_vector_copy((float *)(this + 16), copy_result, (const float *)(a2 + 16));
  rf_vector_copy((float *)(this + 28), v4, (const float *)(a2 + 28));
  *(_DWORD *)(this + 40) = *(_DWORD *)(a2 + 40);
  *(_DWORD *)(this + 44) = *(_DWORD *)(a2 + 44);
  *(_DWORD *)(this + 48) = *(_DWORD *)(a2 + 48);
  *(_DWORD *)(this + 52) = *(_DWORD *)(a2 + 52);
  *(_DWORD *)(this + 56) = *(_DWORD *)(a2 + 56);
  *(_DWORD *)(this + 60) = *(_DWORD *)(a2 + 60);
  *(_DWORD *)(this + 64) = *(_DWORD *)(a2 + 64);
  *(_DWORD *)(this + 68) = *(_DWORD *)(a2 + 68);
  *(_DWORD *)(this + 72) = *(_DWORD *)(a2 + 72);
  *(_DWORD *)(this + 76) = *(_DWORD *)(a2 + 76);
  *(_WORD *)(this + 80) = *(_WORD *)(a2 + 80);
  for ( i = 0; i < 3; ++i )
    *(_DWORD *)(this + 4 * i + 84) = *(_DWORD *)(a2 + 4 * i + 84);
  return this;
}

