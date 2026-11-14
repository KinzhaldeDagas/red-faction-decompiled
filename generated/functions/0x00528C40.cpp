// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528C40 rf_light_sync_active_receiver_space_if_enabled
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Only if global0x663B0C==0,rf_renderer_lights_enabled nonzero,and receiver-space global0x18CD388 nonzero,walks rf_light_active_world_count records and calls rf_light_sync_receiver_space_transform. Does not build,clear or filter active list. Return incidental loopvalue,undefined/uninitialized on some no-workpaths; not success/count contract.
int rf_light_sync_active_receiver_space_if_enabled()
{
  int result; // eax
  signed int i; // [esp+4h] [ebp-4h]

  if ( !dword_663B0C && rf_renderer_lights_enabled && unk_18CD388 )
  {
    for ( i = 0; i < (int)rf_light_active_world_count; ++i )
    {
      rf_light_sync_receiver_space_transform(rf_light_active_world_records[i]);
      result = i + 1;
    }
  }
  return result;
}

