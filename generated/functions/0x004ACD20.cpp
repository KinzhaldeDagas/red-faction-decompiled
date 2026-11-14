// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACD20 rf_powerup_nodes_destroy_all
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Noarg list clear. Iterate circular root7B2548 saving next before deleting. Maintain head/singleton and neighbor next12/prev16, zero removed links then operator
// delete. Terminates at saved root wrap and singleton clear. No final explicit root write after loop (unlike atexit4ACB80), no entity flag cleanup, bitmap/timer callbacks or runtime
// guard. Valid list ends root0 through unlink operations; empty list stays0.
void rf_powerup_nodes_destroy_all()
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
}

