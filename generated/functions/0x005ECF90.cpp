// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ECF90 rf_renderer_flush_world_face_packets
// UNREALRED VERIFIED [face-batch-20261028]: Unlocks current GPU vertex buffer via vtable+48. For priority5 down to0,iterates all20-byte packets at0x1F66920 with matching priority+16 and nonzero index count+12; binds textures/state through rf_d3d8_bind_textures_and_apply_state(state+8,texture0+0,texture1+4). Rewinds GPU index cursor0x18CCFC0 if cursor+packetindices>=10000. Locks/copies packet16-bit indices from0x1E419A0+12000*packet,unlocks,and submits triangle-list indexed draw with primitive count=indexcount/3,vertex count=current0x18CCFBC. Advances index cursor. Does NOT clear packet count/index counts or vertex cursor; caller resets before reusing. Calling twice without reset can redraw same packets. Return loop artifact,not drawcount.
int rf_renderer_flush_world_face_packets()
{
  int result; // eax
  void *v1; // [esp+0h] [ebp-18h]
  void *v2[2]; // [esp+4h] [ebp-14h] BYREF
  int *v3; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int j; // [esp+14h] [ebp-4h]

  result = (*(int (__stdcall **)(_DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0);
  for ( i = 5; i >= 0; --i )
  {
    for ( j = 0; ; ++j )
    {
      result = j;
      if ( j >= unk_1E41998 )
        break;
      v3 = (int *)((char *)&unk_1F66920 + 20 * j);
      if ( v3[4] == i && v3[3] )
      {
        rf_d3d8_bind_textures_and_apply_state(v3[2], *v3, v3[1]);
        if ( v3[3] + unk_18CCFC0 >= 10000 )
          unk_18CCFC0 = 0;
        if ( unk_18CCFC0 )
          v1 = (void *)unk_1DAEE08;
        else
          v1 = (void *)unk_1DAEE04;
        v2[1] = v1;
        v2[0] = nullptr;
        (*(void (__stdcall **)(_DWORD *, int, int, void **, void *))(*dword_1DAEDB4 + 44))(
          dword_1DAEDB4,
          2 * unk_18CCFC0,
          2 * v3[3],
          v2,
          v1);
        memcpy(v2[0], (char *)&unk_1E419A0 + 12000 * j, 2 * v3[3]);
        (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4, dword_1DAEDB4);
        (*(void (__stdcall **)(int, int, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
          dword_1DAEDC4,
          4,
          0,
          dword_18CCFBC,
          unk_18CCFC0,
          v3[3] / 3);
        unk_18CCFC0 += v3[3];
      }
    }
  }
  return result;
}

