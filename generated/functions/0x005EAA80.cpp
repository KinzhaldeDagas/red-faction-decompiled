// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EAA80 rf_renderer_append_world_face_packet
// UNREALRED VERIFIED [face-batch-20261028]: Arguments cached packet-index pointer,source40-byte vertices,count,texture0,texture1,packed state,priority. If cached indexnegative OR cached packet indices+3*(count-2)>=6000,invalidates cache and searches existing packets for matching textures,state exact0x5A4120,priority and indexcapacity<6000. Creates packet ifnone and packetcount<100; otherwise returns cached pointer with-1 and writes no vertices. Valid cached index is TRUSTED without rechecking its textures/state/priority,so callers must invalidate on change. Copies40*count bytes into locked vertex buffer at local write cursor0x1E014E8,adds16-bit triangle-fan indices(base vertex0x18CCFBC,base+i+1,base+i+2) into packet slice. Advances packet index count and both vertex cursors. No source/count>=3,cached-index upper or globalVBO capacity guards. Return EAX is incidental pointer/cursor
// value,not success boolean.
int *__cdecl rf_renderer_append_world_face_packet(int *a1, void *Src, int a3, int a4, int a5, int a6, int a7)
{
  int *result; // eax
  __int16 v8; // [esp+0h] [ebp-18h]
  _WORD *v9; // [esp+4h] [ebp-14h]
  int i; // [esp+8h] [ebp-10h]
  int j; // [esp+8h] [ebp-10h]
  _DWORD *v12; // [esp+Ch] [ebp-Ch]
  __int16 v13; // [esp+14h] [ebp-4h]

  v12 = (_DWORD *)((char *)&unk_1F66920 + 20 * *a1);
  if ( *a1 < 0 || v12[3] + 3 * (a3 - 2) >= 6000 )
  {
    *a1 = -1;
    for ( i = 0; i < unk_1E41998; ++i )
    {
      v12 = (_DWORD *)((char *)&unk_1F66920 + 20 * i);
      if ( *v12 == a4
        && v12[1] == a5
        && rf_packed_state_word_equal(v12 + 2, &a6)
        && v12[4] == a7
        && v12[3] + 3 * (a3 - 2) < 6000 )
      {
        *a1 = i;
        break;
      }
    }
    result = a1;
    if ( *a1 == -1 )
    {
      if ( unk_1E41998 >= 100 )
        return result;
      *a1 = unk_1E41998++;
      v12 = (_DWORD *)((char *)&unk_1F66920 + 20 * *a1);
      *v12 = a4;
      v12[1] = a5;
      v12[2] = a6;
      v12[3] = 0;
      v12[4] = a7;
    }
  }
  v8 = dword_18CCFBC;
  memcpy((void *)(unk_1DAEDB8 + 40 * unk_1E014E8), Src, 40 * a3);
  v9 = (_WORD *)((char *)&unk_1E419A0 + 12000 * *a1 + 2 * v12[3]);
  v13 = v8 + 1;
  for ( j = 0; j < a3 - 2; ++j )
  {
    *v9 = v8;
    v9[1] = v13;
    v9[2] = ++v13;
    v9 += 3;
  }
  v12[3] += 3 * (a3 - 2);
  result = (int *)(a3 + unk_1E014E8);
  unk_1E014E8 += a3;
  dword_18CCFBC += a3;
  return result;
}

