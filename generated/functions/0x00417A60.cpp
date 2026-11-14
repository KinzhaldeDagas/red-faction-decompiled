// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417A60 rf_monitor_create_record
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Allocate0x3C-byte record and construct vector+0x18/deadline+0x24. Require monitor clutter id to resolve or delete allocation and fail. Store monitor id+0xC, initial selected id+0x10, dimensions+0x30/+0x34, flags=1, and mode0 iff input byte==1 else1. Allocate bitmap via0x5732A0/0x5782B0; install bitmap into every case-insensitive screen.tga material record+0x10, additionally writing0.7f through optional pointer at material+0xBC. Arm interval timer0ms, interval8.0f, OR flag2, and append to circular list0x6807E4/0x6807E8. Does not reject bitmap handle-1 or populate entity vector in this body.
char __cdecl rf_monitor_create_record(int a1, int a2, int a3, int a4, char a5)
{
  _DWORD *v6; // [esp+8h] [ebp-38h]
  void *v7; // [esp+14h] [ebp-2Ch]
  int backbuffer_rectangle_dispatch; // [esp+1Ch] [ebp-24h]
  int v9; // [esp+20h] [ebp-20h] BYREF
  _DWORD *v10; // [esp+24h] [ebp-1Ch]
  int i; // [esp+28h] [ebp-18h]
  int v12; // [esp+2Ch] [ebp-14h]
  int v13; // [esp+30h] [ebp-10h] BYREF
  int v14; // [esp+3Ch] [ebp-4h]

  v7 = operator new(0x3Cu);
  v14 = 0;
  if ( v7 )
    v6 = (_DWORD *)rf_monitor_construct_record((int)v7);
  else
    v6 = nullptr;
  v14 = -1;
  v10 = v6;
  if ( !v6 )
    return 0;
  v12 = rf_clutter_find_by_uid(a1);
  if ( v12 )
  {
    v10[3] = a1;
    v10[4] = a2;
    v10[14] = 1;
    v10[12] = a3;
    v10[13] = a4;
    v10[2] = a5 != 1;
    backbuffer_rectangle_dispatch = rf_renderer_read_backbuffer_rectangle_dispatch(0, 0, 0, 0, 0);
    v10[5] = rf_bitmap_create_user_bitmap(backbuffer_rectangle_dispatch, v10[12], v10[13]);
    rf_model_handle_enable_private_materials_get_table(*(_DWORD *)(v12 + 128), &v13, &v9);
    for ( i = 0; i < v13; ++i )
    {
      if ( !_stricmp((const char *)(v9 + 200 * i + 20), "screen.tga") )
      {
        if ( *(_DWORD *)(v9 + 200 * i + 188) )
          **(float **)(v9 + 200 * i + 188) = 0.69999999;
        *(_DWORD *)(v9 + 200 * i + 16) = v10[5];
      }
    }
    rf_replicator_arm_milliseconds(v10 + 9, 0);
    *((float *)v10 + 10) = 8.0;
    v10[14] |= 2u;
    v10[1] = unk_6807E8;
    *v10 = &dword_6807E4;
    *unk_6807E8 = v10;
    unk_6807E8 = v10;
    return 1;
  }
  else
  {
    if ( v10 )
      rf_monitor_record_scalar_deleting_destructor(v10, 1);
    return 0;
  }
}

