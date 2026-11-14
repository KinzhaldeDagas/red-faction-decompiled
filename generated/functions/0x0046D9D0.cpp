// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046D9D0 rf_sound_channel_group_gain_get_unchecked
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl raw channel index. FLD DWORD at rf_sound_channel_group_gains+4*index,return x87ST0. No signed/unsigned range check,clamp,normalization,side
// effect or runtime admission. Stored double prototype retained;native source element is binary32 and x87 load exactly represents it. Audio builder calls0/1/2. EAX is address/index
// residue,not gain return.
double __cdecl rf_sound_channel_group_gain_get_unchecked(int a1)
{
  return rf_sound_channel_group_gains[a1];
}

