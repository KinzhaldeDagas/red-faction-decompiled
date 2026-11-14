// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BA8F0 rf_world_muzzle_effect_ring_render_callback
// UNREALRED VERIFIED [impact-callbacks-20261028]: Caller supplies slot index into16-slot effect ring at0x7D0F10,stride56. Calls0x41A790(effect ID+0,position+4,matrix+16,dword+52). No local range check or slot copy, so callback reads current ring contents when invoked; submitter can overwrite slot after wrapping.
char __cdecl rf_world_muzzle_effect_ring_render_callback(int a1)
{
  return rf_glare_render_definition_beam_and_corona(
           unk_7D0F10[14 * a1],
           (float *)&unk_7D0F10[14 * a1 + 1],
           (int)&unk_7D0F10[14 * a1 + 4],
           unk_7D0F10[14 * a1 + 13]);
}

