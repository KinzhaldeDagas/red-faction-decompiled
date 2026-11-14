// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A4C0 rf_world_packet_sort_collected_face_indices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Sorts global WORD face-index list1482008[0..143E97C) ascending using Shell gaps count/2 repeatedly halved. Does NOT remove duplicates or change count. Return incidental:count for0/1 entries,0 after multi-entry gap loop;not unique-count or status. In-place/global scratch,no allocation.
int rf_world_packet_sort_collected_face_indices()
{
  int result; // eax
  __int16 v1; // [esp+0h] [ebp-14h]
  int j; // [esp+4h] [ebp-10h]
  int k; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v5; // [esp+10h] [ebp-4h]

  result = dword_143E97C;
  v5 = dword_143E97C;
  if ( dword_143E97C > 1 )
  {
    result = dword_143E97C / 2;
    for ( i = dword_143E97C / 2; i > 0; i /= 2 )
    {
      for ( j = i; j < v5; ++j )
      {
        for ( k = j - i; k >= 0 && unk_1482008[k] > unk_1482008[i + k]; k -= i )
        {
          v1 = unk_1482008[k];
          unk_1482008[k] = unk_1482008[i + k];
          unk_1482008[i + k] = v1;
        }
      }
      result = i / 2;
    }
  }
  return result;
}

