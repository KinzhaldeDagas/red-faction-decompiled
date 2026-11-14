// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1290 rf_multiplayer_set_team_rgb_opaque
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl(teamIndex,RlowBYTE,GlowBYTE,BlowBYTE). Signed bounds0<=index<2 else AL0. Construct four bytes R,G,B,255 in localDWORD through5719A0, copy DWORD
// to7B25F8+12*index, return AL1. No floating conversion/clamp, team-name mutation, network broadcast or runtime gate; each supplied color truncated to lowBYTE. PUSH ECX allocates
// local color scratch, not incoming receiver.
char __cdecl rf_multiplayer_set_team_rgb_opaque(unsigned int a1, char a2, char a3, char a4)
{
  int v4; // ecx
  int v6; // [esp+0h] [ebp-4h] BYREF

  v6 = v4;
  if ( a1 >= 2 )
    return 0;
  dword_7B25F8[3 * a1] = *(_DWORD *)rf_rgba8_construct_components_return_self(&v6, a2, a3, a4, 255);
  return 1;
}

