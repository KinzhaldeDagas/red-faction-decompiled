// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574C90 rf_bitmap_animation_frame_index_from_clock
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Arguments source bitmap slot index, start clock, float rate, loop mode. Calculates signed frame=int(unsigned(global clock 0x18092E4-start)*rate); frame count is source record byte+67. If frame<count, returns base+frame+1, including possible negative frame values. At/after count, mode0 returns-1; otherwise modulo count. Mode2 reverses modulo frame when that FRAME INDEX is odd, not when animation cycle is odd. Returns base+selected+1. No zero count, finite/rate or wraparound guard. This is the actual parity rule, not conventional ping-pong.
int __cdecl rf_bitmap_animation_frame_index_from_clock(int a1, int a2, float a3, int a4)
{
  int v5; // [esp+8h] [ebp-Ch]
  int v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  v6 = (int)((double)(unsigned int)(unk_18092E4 - a2) * a3);
  v5 = *(unsigned __int8 *)(dword_1897344 + 108 * a1 + 67);
  if ( v6 < v5 )
    return a1 + v6 + 1;
  if ( !a4 )
    return -1;
  v7 = v6 % v5;
  if ( a4 == 2 && (v7 & 1) != 0 )
    v7 = v5 - 1 - v7;
  return a1 + v7 + 1;
}

