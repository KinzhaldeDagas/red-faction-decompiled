// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049CB30 rf_geomod_apply_pregame_glass_bitset_payload18
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores):
// Original descriptor row18 at662A20 is pregame_glass. Cdecl payload; unused source argument from dispatcher; no length. Arm shared timer7B25EC8000ms first. Construct borrowed128-bit
// bitset over16-byte UNINITIALIZED stack storage, then copy signed (glassCount822714+7)/8 bytes from payload using compiler truncation-toward-zero division. Re-evaluates global count
// in loops, no <=128 clamp, no payload bound; excessive count can overwrite stack, negative count can skip loops, padding remains incoming/uninitialized. For signed index0..<global
// count, LSB-first bit1 leaves group intact; bit0 selects group pointer822510[index], dereferences group+40 firstDWORD head (generic486DE0 getter), follows Face+92 room-next links
// and stages ALL face pointers into temporary array BEFORE deletion. Then for each staged pointer, call world_solid51A090(face,flag0), clear temporary count retaining storage,
// continue. This avoids traversing mutated room links during removal. No group/world/face NULL guard beyond terminating next link, no runtime/authority gate. Destroys array backing
// then borrowed bitset normally with SEH cleanup; no geometry operation loop or final network poll. 486DE0 is generic first-DWORD getter: here head for group list and count for
// temporary array, not cached-room semantics.
int __cdecl rf_geomod_apply_pregame_glass_bitset_payload18(int a1)
{
  _DWORD **v1; // eax
  int m; // [esp+4h] [ebp-50h]
  int k; // [esp+Ch] [ebp-48h]
  int i; // [esp+10h] [ebp-44h]
  _BYTE v6[16]; // [esp+14h] [ebp-40h] BYREF
  int v7; // [esp+28h] [ebp-2Ch]
  int j; // [esp+2Ch] [ebp-28h]
  _DWORD v9[3]; // [esp+30h] [ebp-24h] BYREF
  void *v10[3]; // [esp+3Ch] [ebp-18h] BYREF
  int v11; // [esp+50h] [ebp-4h]

  v7 = 0;
  rf_replication_timer7B25EC_arm_8s();
  rf_bitset_construct_borrowed_storage(v9, (int)v6, 128);
  v11 = 0;
  for ( i = 0; i < (dword_822714 + 7) / 8; ++i )
  {
    v6[i] = *(_BYTE *)(v7 + a1);
    ++v7;
  }
  rf_dword_array_construct_capacity(v10, 0);
  LOBYTE(v11) = 1;
  for ( j = 0; j < dword_822714; ++j )
  {
    if ( !rf_bitset_get_bit_unchecked(v9, j) )
    {
      for ( k = rf_receiver_get_first_dword((void *)(unk_822510[j] + 40)); k; k = rf_face_next_room_link(k) )
        rf_pointer_array_append_dword(v10, k);
      for ( m = 0; m < rf_receiver_get_first_dword(v10); ++m )
      {
        v1 = (_DWORD **)sub_552200(v10, m);
        rf_solid_face_remove_destroy((int *)rf_world_solid, *v1, 0);
      }
      rf_pointer_array_clear_count_keep_storage(v10);
    }
  }
  LOBYTE(v11) = 0;
  rf_pointer_array_destroy_backing_storage(v10);
  v11 = -1;
  return rf_bitset_destroy(v9);
}

