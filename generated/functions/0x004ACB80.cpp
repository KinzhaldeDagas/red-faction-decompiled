// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACB80 rf_powerup_nodes_atexit_destroy_all
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Noarg atexit callback. Walk circular list root7B2548 with next12/prev16, saving next BEFORE unlink/delete, treating next==currentroot as termination. For
// head/singleton update root or zero it, otherwise relink neighbors; clear removed next/prev then operator delete. After loop explicitly root=0 again. Frees all nodes, no entity flag
// clearing, player resolution, bitmap release or deadline callback. Uses no runtime/authority guard. Distinct from4ACD20 only redundant final root clear.
void __cdecl rf_powerup_nodes_atexit_destroy_all()
{
  _DWORD *v0; // [esp+0h] [ebp-10h]
  _DWORD *i; // [esp+Ch] [ebp-4h]

  for ( i = (_DWORD *)unk_7B2548; i; i = v0 )
  {
    if ( i[3] == unk_7B2548 )
      v0 = nullptr;
    else
      v0 = (_DWORD *)i[3];
    if ( (_DWORD *)unk_7B2548 == i )
    {
      if ( (_DWORD *)i[3] == i )
      {
        i[3] = 0;
        i[4] = 0;
        unk_7B2548 = 0;
        goto LABEL_11;
      }
      unk_7B2548 = i[3];
    }
    *(_DWORD *)(i[4] + 12) = i[3];
    *(_DWORD *)(i[3] + 16) = i[4];
    i[3] = 0;
    i[4] = 0;
LABEL_11:
    operator delete(i);
  }
  unk_7B2548 = 0;
}

