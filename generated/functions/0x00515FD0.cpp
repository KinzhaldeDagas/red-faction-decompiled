// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515FD0 sub_515FD0
// UNREALRED VERIFIED [trigger-airlock-20261022] Initial room pressure+68 defaults to !outside+66. For room UID!=-1 with exactly two portals whose opposite rooms have portal degrees1 and2, use the degree2 bridge, choose its portal not containing the original room, and set pressure=!far-room outside. No requirement that authored airlock byte+67 be set.
// UNREALRED VERIFIED [combat-native-query-20261104]:477370 calls this after each initial517470 liquid rebuild, but this body initializes room pressure only; no geometry tree/bounds/publication work occurs. It does not rebuild trees to include newly generated liquid faces.
char __thiscall sub_515FD0(int this)
{
  int first_dword; // eax
  int v3; // [esp+0h] [ebp-24h]
  int *v5; // [esp+8h] [ebp-1Ch]
  int v6; // [esp+Ch] [ebp-18h]
  _DWORD *v7; // [esp+14h] [ebp-10h]
  _DWORD *v8; // [esp+18h] [ebp-Ch]
  int v9; // [esp+1Ch] [ebp-8h]
  int v10; // [esp+20h] [ebp-4h]

  LOBYTE(first_dword) = this;
  if ( *(_BYTE *)(this + 66) )
  {
    *(_BYTE *)(this + 68) = 0;
  }
  else
  {
    LOBYTE(first_dword) = this;
    *(_BYTE *)(this + 68) = 1;
  }
  if ( *(_DWORD *)(this + 36) != -1 )
  {
    first_dword = rf_receiver_get_first_dword((void *)(this + 48));
    if ( first_dword == 2 )
    {
      v8 = *(_DWORD **)sub_552200((_DWORD *)(this + 48), 0);
      v7 = *(_DWORD **)sub_552200((_DWORD *)(this + 48), 1);
      v10 = *v8 == this ? v8[1] : *v8;
      v9 = *v7 == this ? v7[1] : *v7;
      if ( rf_receiver_get_first_dword((void *)(v10 + 48)) == 1 && rf_receiver_get_first_dword((void *)(v9 + 48)) == 2
        || (first_dword = rf_receiver_get_first_dword((void *)(v10 + 48)), first_dword == 2)
        && (first_dword = rf_receiver_get_first_dword((void *)(v9 + 48)), first_dword == 1) )
      {
        if ( rf_receiver_get_first_dword((void *)(v10 + 48)) == 2 )
          v3 = v10;
        else
          v3 = v9;
        if ( **(_DWORD **)sub_552200((_DWORD *)(v3 + 48), 0) == this
          || *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(v3 + 48), 0) + 4) == this )
        {
          v5 = *(int **)sub_552200((_DWORD *)(v3 + 48), 1);
        }
        else
        {
          v5 = *(int **)sub_552200((_DWORD *)(v3 + 48), 0);
        }
        if ( *v5 == v3 )
          v6 = v5[1];
        else
          v6 = *v5;
        LOBYTE(first_dword) = *(_BYTE *)(v6 + 66) == 0;
        *(_BYTE *)(this + 68) = first_dword;
      }
    }
  }
  return first_dword;
}

