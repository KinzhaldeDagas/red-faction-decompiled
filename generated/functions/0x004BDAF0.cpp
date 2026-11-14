// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDAF0 rf_world_free_model_instance_render_data
// UNREALRED VERIFIED [resource-pools-20261028]: Operator-deletes global0x7B8E14 ifnonnull then clears pointer. Does not clear object+636 pointers into former block or traverse model instances.
void rf_world_free_model_instance_render_data()
{
  if ( unk_7B8E14 )
    operator delete(unk_7B8E14);
  unk_7B8E14 = nullptr;
}

