// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FFC90 rf_event_spawn_object_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_spawn_object forward, vtable0x63E168 slot+4. Runtime type field+0x2B8 selects only4(clutter),0(entity),1(item), using definition+0x2BC and event position+0x40/orientation+0x4C; other types do nothing. Successful clutter with byte+0x2C0==1 constructs physical-debris config from spawned position/context, random orientation and lifetime -1 for finite duration+0x2C4<=0, otherwise trunc(seconds*1000+0.5). Calls physical debris creation from spawned model/scale, then sets original clutter common flags+0x7C bit2 without checking returned debris success. This is separate from item/entity create paths; no target traversal or saved-result-id publication here.
int __thiscall rf_event_spawn_object_forward(int this)
{
  char *v1; // eax
  int result; // eax
  void *v3; // [esp+0h] [ebp-90h]
  float copy_result[3]; // [esp+14h] [ebp-7Ch] BYREF
  float destination[3]; // [esp+20h] [ebp-70h] BYREF
  float v7[9]; // [esp+2Ch] [ebp-64h] BYREF
  float v8[6]; // [esp+50h] [ebp-40h] BYREF
  int v9; // [esp+68h] [ebp-28h]
  int v10; // [esp+6Ch] [ebp-24h]
  int v11; // [esp+70h] [ebp-20h]
  int v12; // [esp+74h] [ebp-1Ch]
  int v13; // [esp+78h] [ebp-18h]
  const float *v14; // [esp+8Ch] [ebp-4h]

  if ( *(_DWORD *)(this + 696) == 4 )
  {
    v14 = (const float *)rf_clutter_runtime_create(
                           *(_DWORD *)(this + 700),
                           (char *)&byte_63D9A7,
                           -1,
                           (float *)(this + 64),
                           (float *)(this + 76),
                           0);
    if ( *(_BYTE *)(this + 704) == 1 )
    {
      if ( v14 )
      {
        rf_geomod_debris_spawn_config_init((int)destination);
        rf_vector_copy(destination, copy_result, v14 + 15);
        v10 = *((_DWORD *)v14 + 127);
        v11 = -1;
        v12 = 8;
        v13 = 0;
        if ( *(float *)(this + 708) <= 0.0 )
          v9 = -1;
        else
          v9 = (int)(*(float *)(this + 708) * 1000.0 + 0.5);
        rf_vector3_zero_return_destination(v8);
        rf_random_orientation_matrix(v7);
        v3 = *((void **)v14 + 38);
        v1 = (char *)rf_string_object_c_str_or_empty((const void *)(*((_DWORD *)v14 + 165) + 8));
        rf_physical_debris_piece_create(-1, v1, v3, destination, 0, COERCE_VOID_(-1.0));
        *((_DWORD *)v14 + 31) |= 2u;
      }
    }
  }
  if ( !*(_DWORD *)(this + 696) )
    rf_entity_create_runtime(
      *(_DWORD *)(this + 700),
      (char *)&byte_63D9B1,
      -1,
      (float *)(this + 64),
      (float *)(this + 76),
      0,
      -1);
  result = this;
  if ( *(_DWORD *)(this + 696) == 1 )
    return rf_item_instance_spawn(
             *(_DWORD *)(this + 700),
             (char *)byte_63D9B2,
             1,
             -1,
             (float *)(this + 64),
             (float *)(this + 76),
             -1,
             0,
             0);
  return result;
}

