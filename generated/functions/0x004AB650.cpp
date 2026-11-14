// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AB650 rf_multiplayer_apply_clutter_active_bitset_payload29
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(payload pointer consumed; registry dispatch supplies ignored source). Arms shared8-second replication timer BEFORE reading count/admission.
// Read signed countDWORD; mismatch current666B74 returns without changes beyond timer. Equal count constructs borrowed3200-bit set over UNINITIALIZED stack storage, then signed
// count>3200 destroys wrapper/returns. Negative equal count not rejected; loops may skip. Copies signed-trunc((count+7)/8) bytes from payload, leaves remaining bits/padding
// uninitialized. For outer i0..<count RESTARTS entire live clutter list each pass (not direct index i). First object whose SIGNED WORD724>=0 AND <=count INCLUSIVE AND received bit0:
// if replacement typeDWORD668!=-1 creates runtime clutter(type,empty original63B0D0,oldHandle44,position60,orientation72,0); marks old object deferred-delete, sets local bit1 for its
// index, BREAKS inner scan. Thus at most one zero-bit object per pass; bit mutation prevents duplicate action for same index. Equality index==count is accepted although beyond
// logical count, reading padding/uninitialized/outside3200 when count3200. Does not clear/rebuild global666B88, perform immediate unlink or transmit anything. No payload-length,
// runtime/authority, replacement-result or object-lifetime guard; borrowed bitset destroyed normally/SEH without freeing stack backing.
int __cdecl rf_multiplayer_apply_clutter_active_bitset_payload29(int *a1)
{
  int result; // eax
  int k; // [esp+4h] [ebp-1C4h]
  int i; // [esp+8h] [ebp-1C0h]
  _BYTE v4[404]; // [esp+Ch] [ebp-1BCh] BYREF
  int v5; // [esp+1A4h] [ebp-24h]
  _DWORD v6[3]; // [esp+1A8h] [ebp-20h] BYREF
  int v7; // [esp+1B4h] [ebp-14h]
  int j; // [esp+1B8h] [ebp-10h]
  int v9; // [esp+1C4h] [ebp-4h]

  v7 = 0;
  rf_replication_timer7B25EC_arm_8s();
  v5 = *a1;
  result = 4;
  v7 = 4;
  if ( v5 == dword_666B74 )
  {
    rf_bitset_construct_borrowed_storage(v6, (int)v4, 3200);
    v9 = 0;
    if ( v5 <= 3200 )
    {
      for ( i = 0; i < (v5 + 7) / 8; ++i )
        v4[i] = *((_BYTE *)a1 + v7++);
      for ( j = 0; j < v5; ++j )
      {
        for ( k = rf_clutter_list_head; (_UNKNOWN *)k != &unk_666D18; k = *(_DWORD *)(k + 652) )
        {
          if ( *(__int16 *)(k + 724) > -1
            && *(__int16 *)(k + 724) <= v5
            && !rf_bitset_get_bit_unchecked(v6, *(__int16 *)(k + 724)) )
          {
            if ( *(_DWORD *)(k + 668) != -1 )
              rf_clutter_runtime_create(
                *(_DWORD *)(k + 668),
                (char *)&byte_63B0D0,
                *(_DWORD *)(k + 44),
                (float *)(k + 60),
                (float *)(k + 72),
                0);
            rf_object_mark_for_deferred_delete(k);
            rf_bitset_set_bit_unchecked(v6, *(__int16 *)(k + 724), 1);
            break;
          }
        }
      }
    }
    v9 = -1;
    return rf_bitset_destroy(v6);
  }
  return result;
}

