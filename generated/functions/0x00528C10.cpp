// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528C10 rf_light_get_active_list_context_byte
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Returns rawbyte0xD035FC. Lightmap updater0x54D990 uses nonzero to reuse currentactive-lightlist ratherthan build/clear its own; accessor itself does not alter lists.
char rf_light_get_active_list_context_byte()
{
  return unk_D035FC;
}

